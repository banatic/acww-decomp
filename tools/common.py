"""Shared code for the tools: paths, the symbol table, source headers, mwccarm, ELF."""

from __future__ import annotations

import dataclasses
import hashlib
import json
import os
import pathlib
import re
import shlex
import shutil
import struct
import subprocess
import threading

ROOT = pathlib.Path(__file__).resolve().parents[1]
CONFIG = ROOT / "config" / "adm-kr" / "arm9"
SRC = ROOT / "src"
# Library code (NitroSDK, NitroSystem, ...) is kept out of the game tree, under
# libs/<Package>/<module>/. Both trees hold sources in the same format.
LIBS = ROOT / "libs"
SOURCE_ROOTS = (SRC, LIBS)
INCLUDE = ROOT / "include"
BUILD = ROOT / "build" / "adm-kr"
ROM_DIR = BUILD / "rom"
OBJ_DIR = BUILD / "obj"
WORK_DIR = BUILD / "mwcc-cwd"


def main_checkout() -> pathlib.Path:
    """The main checkout: a git worktree's .git file names <main>/.git/worktrees/<name>."""
    git = ROOT / ".git"
    if git.is_file() and (m := re.match(r"gitdir:\s*(.+)", git.read_text())):
        gitdir = pathlib.Path(m.group(1).strip())
        if gitdir.parent.name == "worktrees":
            return gitdir.parent.parent.parent
    return ROOT


# Objects shared by every checkout and worktree, by a key that names no checkout's own path
# (ACWW_CACHE moves it): a new worktree copies what another already compiled.
CACHE_DIR = pathlib.Path(os.environ.get("ACWW_CACHE", main_checkout() / "build" / "cache"))


def tree_free(text: str) -> str:
    """`text` with this checkout's own path in place of `<root>`, for a shared cache key."""
    for root in (str(ROOT), ROOT.as_posix()):
        text = text.replace(root, "<root>")
    return text


def cache_get(kind: str, key: str, dest: pathlib.Path) -> bool:
    """Copy the shared cache's `kind` object for `key` to `dest`; False when it has none."""
    try:
        shutil.copyfile(CACHE_DIR / kind / key[:2] / key, dest)
        return True
    except OSError:
        return False


def cache_put(kind: str, key: str, src: pathlib.Path) -> None:
    """Keep a copy of `src` in the shared cache under `key` (written whole, then renamed)."""
    entry = CACHE_DIR / kind / key[:2] / key
    if entry.exists():
        return
    try:
        entry.parent.mkdir(parents=True, exist_ok=True)
        tmp = entry.with_name(f"{key}.{os.getpid()}-{threading.get_ident()}")
        shutil.copyfile(src, tmp)
        os.replace(tmp, entry)
    except OSError:
        pass


# mwccarm is proprietary and never committed. INSTALL.md says where to put it.
MWCC_ROOT = pathlib.Path(os.environ.get("MWCC_ROOT", ROOT / "tools" / "mwccarm"))

RESIDENT = ("main", "itcm", "dtcm", "autoload_2", "autoload_3")


# ------------------------------------------------------------------------------ modules

def modules() -> dict[str, dict]:
    path = ROM_DIR / "modules.json"
    if not path.exists():
        raise SystemExit("run `python tools/extract.py` first")
    return json.loads(path.read_text())


def module_image(name: str) -> bytes:
    return (ROM_DIR / f"{name}.bin").read_bytes()


def config_dir(module: str) -> pathlib.Path:
    if module == "main":
        return CONFIG
    if module.startswith("ov"):
        return CONFIG / "overlays" / module
    return CONFIG / module


# ------------------------------------------------------------------------------ symbols

SYM_LINE = re.compile(r"^(?P<name>\S+)\s+kind:(?P<kind>\w+)(?:\((?P<attrs>[^)]*)\))?"
                      r"\s+addr:0x(?P<addr>[0-9a-fA-F]+)")


@dataclasses.dataclass(frozen=True)
class Symbol:
    name: str
    module: str
    kind: str          # function | data | label
    address: int
    size: int
    thumb: bool
    recovered: bool = False


def _read_symbols(path: pathlib.Path, module: str, recovered: bool) -> list[Symbol]:
    out = []
    if not path.exists():
        return out
    for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
        m = SYM_LINE.match(line.strip())
        if not m:
            continue
        attrs = m.group("attrs") or ""
        sm = re.search(r"size=0x([0-9a-fA-F]+)", attrs)
        out.append(Symbol(m.group("name"), module, m.group("kind"), int(m.group("addr"), 16),
                          int(sm.group(1), 16) if sm else 0, "thumb" in attrs, recovered))
    return out


class SymbolTable:
    """Every symbol of every module, as dsd reads them from symbols.txt. A function's name
    is the one its source emits: the plain name for C, the mangled name for C++."""

    def __init__(self, mods: dict[str, dict]):
        self.by_module: dict[str, list[Symbol]] = {}
        for mod in mods:
            self.by_module[mod] = _read_symbols(config_dir(mod) / "symbols.txt", mod, False)
        # aliases.txt: a second name some sources still use for a symbol. It resolves to the
        # same address, with size 0 so counts and boundaries are unchanged.
        by_name = {s.name: s for syms in self.by_module.values() for s in syms}
        alias_file = CONFIG / "aliases.txt"
        if alias_file.exists():
            for line in alias_file.read_text().splitlines():
                if line.strip() and not line.startswith("#"):
                    alias, canon = line.split()
                    if canon in by_name:
                        s = by_name[canon]
                        self.by_module[s.module].append(dataclasses.replace(s, name=alias, size=0))
        # Linker-script symbols (NitroSDK's .lcf defines SDK_IRQ_STACKSIZE, the arena bounds,
        # ...): absolute values in no module. SDK code takes their addresses, so the ROM
        # holds each value as a plain, unrelocated word. Resolved like any unique name.
        absolute = _read_symbols(CONFIG / "absolute.txt", "absolute", False)
        if absolute:
            self.by_module["absolute"] = absolute
        self.by_name: dict[str, list[Symbol]] = {}
        self.by_addr: dict[tuple[str, int], list[Symbol]] = {}
        for syms in self.by_module.values():
            for s in syms:
                self.by_name.setdefault(s.name, []).append(s)
                self.by_addr.setdefault((s.module, s.address), []).append(s)

    def function(self, module: str, address: int) -> Symbol | None:
        # dsd sometimes leaves a size-0 `_unk` entry where a recovered boundary sits.
        hits = [s for s in self.by_addr.get((module, address), ()) if s.kind == "function"]
        return max(hits, key=lambda s: s.size, default=None)

    def lookup(self, name: str, from_module: str) -> Symbol | None:
        """Resolve a name the way the linker sees it from `from_module`.

        Names are unique except for a handful of SDK functions present in two modules;
        prefer the referencing module, then the resident modules, then anything unique.
        """
        cands = self.by_name.get(name)
        if not cands:
            return None
        for s in cands:
            if s.module == from_module:
                return s
        for s in cands:
            if s.module in RESIDENT:
                return s
        return cands[0] if len(cands) == 1 else None

    def at(self, address: int, from_module: str) -> list[Symbol]:
        """Symbols named at an address visible from `from_module` (for suggestions)."""
        out = list(self.by_addr.get((from_module, address), ()))
        for mod in RESIDENT:
            if mod != from_module:
                out += self.by_addr.get((mod, address), ())
        return out


# ------------------------------------------------------------------------------ sources

HEADER = re.compile(
    r"\A/\* (?P<name>\S+) @ 0x(?P<addr>[0-9a-f]{8}), 0x(?P<size>[0-9a-f]+) bytes, "
    r"(?P<isa>ARM|Thumb), module (?P<module>\w+)\n"
    r" \* mwccarm (?P<drop>\S+) (?P<opt>-O[0-4],[sp])\n"
    r"(?: \* compiler-emitted symbol: (?P<emitted>\S+)\n)?")


@dataclasses.dataclass(frozen=True)
class Source:
    path: pathlib.Path
    name: str
    address: int
    size: int
    thumb: bool
    module: str
    drop: str
    opt: str
    emitted: str | None

    @property
    def lang(self) -> str:
        return "c++" if self.path.suffix == ".cpp" else "c"

    @property
    def object_symbol(self) -> str:
        return self.emitted or self.name


def parse_source(path: pathlib.Path) -> Source | None:
    m = HEADER.match(path.read_text(encoding="utf-8", errors="replace"))
    if not m:
        return None
    return Source(path, m["name"], int(m["addr"], 16), int(m["size"], 16), m["isa"] == "Thumb",
                  m["module"], m["drop"], m["opt"], m["emitted"])


def all_sources() -> list[pathlib.Path]:
    return sorted(p for root in SOURCE_ROOTS if root.is_dir()
                  for p in root.rglob("*") if p.suffix in (".c", ".cpp"))


def module_sources(module: str) -> list[pathlib.Path]:
    """Every source of one module, game and library alike."""
    dirs = [SRC / module] + (sorted(LIBS.glob(f"*/{module}")) if LIBS.is_dir() else [])
    return sorted(p for d in dirs if d.is_dir() for p in d.glob("*.c*"))


def source_kind(path: pathlib.Path) -> str:
    """"libs" for library code, "game" for everything under src/."""
    return "libs" if path.resolve().is_relative_to(LIBS) else "game"


# Where library code sits in each module (the rest is game code). Used to place functions
# that have no source yet, e.g. the GameSpy code, which is not distributed.
LIBRARY_RANGES = {
    "main": [(0x02000000, 0x02000B48)],                       # BIOS veneers, crt0
    "itcm": [(0x01FF8000, 0x01FFCB28), (0x01FFD50C, 0x02000000)],
    "autoload_2": [(0x020FF9FC, 0x03000000)],
    "ov001": [(0, 1 << 32)],
    "ov065": [(0, 1 << 32)],
    "ov067": [(0, 1 << 32)],
}


def in_library(module: str, address: int) -> bool:
    return any(a <= address < b for a, b in LIBRARY_RANGES.get(module, ()))


# ------------------------------------------------------------------------------ compiler

def compile_flags(src: Source) -> list[str]:
    # -interworking: ARM functions return with `bx lr`. -char signed / -enum int are the
    # project defaults every match was made under. The optimisation level and the compiler
    # drop are per translation unit and come from the file's header.
    flags = ["-proc", "arm946e", src.opt, "-lang", src.lang, "-char", "signed",
             "-enum", "int", "-interworking", "-i", str(INCLUDE / "msl"), "-i", str(INCLUDE)]
    # The ROM's exception index lists only runtime-library functions, so the game was
    # built without exception tables.
    if SRC in src.path.resolve().parents:
        flags += ["-Cpp_exceptions", "off"]
        # The ROM's vtables hold 0 in the type-info slot (e.g. 0x020d82b4): no RTTI either.
        if src.lang == "c++":
            flags += ["-RTTI", "off"]
    if src.thumb:
        flags.append("-thumb")
    return flags


INCLUDE_LINE = re.compile(rb'^\s*#\s*include\s*"([^"]+)"', re.M)


def included_files(path: pathlib.Path) -> list[pathlib.Path]:
    """Every header `path` pulls in through #include "...", transitively, in a stable order."""
    seen: dict[pathlib.Path, None] = {}
    todo = [path]
    while todo:
        cur = todo.pop()
        for name in INCLUDE_LINE.findall(cur.read_bytes()):
            name = name.decode()
            for base in (cur.parent, INCLUDE, INCLUDE / "msl"):
                cand = (base / name).resolve()
                if cand.is_file():
                    if cand not in seen:
                        seen[cand] = None
                        todo.append(cand)
                    break
    return sorted(seen)


def compile_source(src: Source, wrapper: str | None = None,
                   force: bool = False) -> tuple[bytes | None, str]:
    """(object bytes, compiler output). Objects are cached by source, every header it
    includes, flags and compiler drop, so editing a header recompiles its users.
    `wrapper` overrides MWCC_WRAPPER for this compile; `force` ignores the cache."""
    exe = MWCC_ROOT / src.drop / "mwccarm.exe"
    if not exe.exists():
        raise SystemExit(f"mwccarm not found at {exe} (set MWCC_ROOT; see INSTALL.md)")
    text = src.path.read_bytes()
    flags = compile_flags(src)
    h = hashlib.sha1(text + "\0".join([src.drop, *flags]).encode())
    # the same, naming no checkout's own path: the key in the shared cache
    shared = hashlib.sha1(text + tree_free("\0".join([src.drop, *flags])).encode())
    for inc in included_files(src.path):
        data = inc.read_bytes()
        h.update(b"\0" + data)
        shared.update(b"\0" + data)
    key, shared = h.hexdigest(), shared.hexdigest()
    rel = src.path.resolve().relative_to(ROOT)
    obj = OBJ_DIR / rel.with_suffix(".o")
    stamp = obj.with_suffix(".key")
    if not force and obj.exists() and stamp.exists() and stamp.read_text() == key:
        cache_put("mwcc", shared, obj)
        return obj.read_bytes(), ""
    obj.parent.mkdir(parents=True, exist_ok=True)
    if not force and cache_get("mwcc", shared, obj):
        stamp.write_text(key)
        return obj.read_bytes(), ""
    env = dict(os.environ, LM_LICENSE_FILE=str(MWCC_ROOT / "license.dat"))
    # MWCC_WRAPPER (e.g. "wibo") runs the Windows compiler on another host. It is meant not to
    # change the output, so it is not part of the cache key; see verify.py for the few
    # functions where wibo and Windows disagree.
    cmd = shlex.split(os.environ.get("MWCC_WRAPPER", "") if wrapper is None else wrapper)
    # Compile in, and into, a small private directory, then move the object into place: under
    # wibo the compiler scans the directories it works in, and writing straight into an object
    # directory with thousands of files made each compile take seconds.
    work = WORK_DIR / f"{os.getpid()}-{threading.get_ident()}"
    work.mkdir(parents=True, exist_ok=True)
    tmp = work / "out.o"
    tmp.unlink(missing_ok=True)
    p = subprocess.run([*cmd, str(exe), *flags, "-c", str(src.path), "-o", str(tmp)],
                       capture_output=True, env=env, cwd=work, timeout=300)
    log = (p.stdout + p.stderr).decode("utf-8", "replace")
    if p.returncode != 0 or not tmp.exists():
        return None, log
    os.replace(tmp, obj)
    stamp.write_text(key)
    cache_put("mwcc", shared, obj)
    return obj.read_bytes(), log


# ------------------------------------------------------------------------------ ELF

@dataclasses.dataclass
class ElfSymbol:
    name: str
    value: int
    size: int
    type: int      # STT_*
    bind: int      # STB_*
    shndx: int


@dataclasses.dataclass
class ElfSection:
    name: str
    type: int
    offset: int
    size: int
    link: int
    info: int
    entsize: int


class Elf:
    def __init__(self, data: bytes):
        if data[:4] != b"\x7fELF":
            raise ValueError("not an ELF file")
        self.data = data
        shoff, = struct.unpack_from("<I", data, 0x20)
        shentsize, shnum, shstrndx = struct.unpack_from("<HHH", data, 0x2E)
        raw = []
        for i in range(shnum):
            o = shoff + i * shentsize
            name, typ = struct.unpack_from("<II", data, o)
            off, size, link, info = struct.unpack_from("<IIII", data, o + 0x10)
            entsize, = struct.unpack_from("<I", data, o + 0x24)
            raw.append((name, typ, off, size, link, info, entsize))
        strs = raw[shstrndx]
        self.sections = [ElfSection(self._str(strs[2], n), t, o, s, l, i, e)
                         for n, t, o, s, l, i, e in raw]
        self.symbols: list[ElfSymbol] = []
        for sec in self.sections:
            if sec.type == 2 and sec.entsize:
                strtab = self.sections[sec.link]
                for k in range(sec.size // sec.entsize):
                    so = sec.offset + k * sec.entsize
                    n, value, size = struct.unpack_from("<III", data, so)
                    info = data[so + 12]
                    shndx, = struct.unpack_from("<H", data, so + 14)
                    self.symbols.append(ElfSymbol(self._str(strtab.offset, n), value, size,
                                                  info & 0xF, info >> 4, shndx))

    def _str(self, base: int, off: int) -> str:
        end = self.data.find(b"\0", base + off)
        return self.data[base + off:end].decode("ascii", "replace")

    def section_bytes(self, index: int) -> bytes:
        s = self.sections[index]
        return b"" if s.type == 8 else self.data[s.offset:s.offset + s.size]

    def relocations(self, section_index: int) -> list[tuple[int, int, ElfSymbol, int | None]]:
        """(offset, type, symbol, addend) for every relocation applied to a section.

        mwccarm writes RELA sections, so the addend is explicit (calls carry -4/-8, the
        branch field itself is zero; a pointer to `sym + 8` carries 8). For a REL section
        the addend is None and lives in the instruction.
        """
        out = []
        for sec in self.sections:
            if sec.type not in (4, 9) or sec.info != section_index or not sec.entsize:
                continue
            for k in range(sec.size // sec.entsize):
                ro = sec.offset + k * sec.entsize
                off, info = struct.unpack_from("<II", self.data, ro)
                addend = struct.unpack_from("<i", self.data, ro + 8)[0] if sec.type == 4 else None
                out.append((off, info & 0xFF, self.symbols[info >> 8], addend))
        return out

    def function(self, name: str) -> ElfSymbol | None:
        for s in self.symbols:
            if s.name == name and s.type == 2 and s.size:
                return s
        return None
