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
import time

import versions

ROOT = pathlib.Path(__file__).resolve().parents[1]
# The ROM version the tools work on (tools/versions.py: --version, ACWW_VERSION, else adm-kr)
VERSION = versions.NAME
CONFIG = versions.CONFIG
SRC = ROOT / "src"
# Library code (NitroSDK, NitroSystem, ...) is kept out of the game tree, under
# libs/<Package>/<module>/. Both trees hold sources in the same format.
LIBS = ROOT / "libs"
SOURCE_ROOTS = (SRC, LIBS)
INCLUDE = ROOT / "include"
BUILD = versions.BUILD
ROM = versions.ROM
RECORDINGS = versions.RECORDINGS
ROM_DIR = BUILD / "rom"
OBJ_DIR = BUILD / "obj"
WORK_DIR = BUILD / "mwcc-cwd"
# Where each source's own data (its sections other than .text and .init) lands in the ROM:
# tools/link.py writes it, tools/native.py reads it. It is kept in the tree because only the
# link (mwccarm) can tell, and the PC build must not need mwccarm.
NATIVE_PRIVATE = ROOT / "runtime" / "native-private.txt"


def write_native_private(placement: dict[str, list[tuple[str, int, int]]]) -> None:
    """NATIVE_PRIVATE from {source (from the root): [(section, start, end), ...]}, by function key
    (function_key; a unit's data under its first function, as tools/native.py gives all of a
    unit's data to each of its functions), in key and address order."""
    lines = ["# Each source's own data in the ROM, outside its functions: function key, section, start",
             "# and end (written by tools/link.py; a unit's under its first function). While a function",
             "# of the source runs on the PC the words there are not compared with the Reference's, as",
             "# the PC's copy of the data is its own."]
    keyed: dict[str, list[tuple[str, int, int]]] = {}
    for path, sections in placement.items():
        src = parse_source(ROOT / path)
        if src is not None and sections:
            keyed.setdefault(function_key(src), []).extend(sections)
    for key in sorted(keyed):
        for name, start, end in sorted(keyed[key], key=lambda s: (s[1], s[2], s[0])):
            lines.append(f"{key} {name} {start:08x} {end:08x}")
    NATIVE_PRIVATE.write_text("\n".join(lines) + "\n", newline="\n")


def read_native_private() -> dict[str, list[tuple[str, int, int]]]:
    """NATIVE_PRIVATE: {function key: [(section, start, end), ...]}."""
    placement: dict[str, list[tuple[str, int, int]]] = {}
    for line in NATIVE_PRIVATE.read_text().splitlines():
        if line.strip() and not line.startswith("#"):
            key, name, start, end = line.split()
            placement.setdefault(key, []).append((name, int(start, 16), int(end, 16)))
    return placement


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
    entry = CACHE_DIR / kind / key[:2] / key
    try:
        shutil.copyfile(entry, dest)
        os.utime(entry)  # used: prune_cache keeps what was used last
        return True
    except OSError:
        return False


def cache_put(kind: str, key: str, src: pathlib.Path) -> None:
    """Keep a copy of `src` in the shared cache under `key` (written whole, then renamed)."""
    entry = CACHE_DIR / kind / key[:2] / key
    if entry.exists():
        # (not marked as used: on Windows that costs milliseconds a file, and an object kept
        # here as well as in a checkout's own cache loses nothing if the cache prunes it)
        return
    try:
        entry.parent.mkdir(parents=True, exist_ok=True)
        tmp = entry.with_name(f"{key}.{os.getpid()}-{threading.get_ident()}")
        shutil.copyfile(src, tmp)
        os.replace(tmp, entry)
    except OSError:
        pass


def prune_cache(kinds: tuple[str, ...] | None = None) -> None:
    """Keep the shared cache under ACWW_CACHE_LIMIT_GB (default 10): what was used longest ago
    goes first, a directory entry (a Reference run's results) as a whole. Nothing used in the
    last ten minutes is removed. The whole cache is looked over at most once an hour; with
    `kinds`, only those, every time, against their own limit (ACWW_CACHE_REFERENCE_GB, default
    16, for "reference2", the Reference runs: an entry is 2 to 15 MB, and a gate stores two for
    every scene), which the look over the whole cache leaves alone. ("reference" holds the
    entries of an older format, up to 700 MB each, which checkouts of before it still prune
    to 6 GB.)"""
    stamp = CACHE_DIR / ".pruned"
    now = time.time()
    if kinds is None:
        try:
            if now - stamp.stat().st_mtime < 3600:
                return
        except OSError:
            pass
        limit = float(os.environ.get("ACWW_CACHE_LIMIT_GB", "10")) * (1 << 30)
    else:
        limit = float(os.environ.get("ACWW_CACHE_REFERENCE_GB", "16")) * (1 << 30)
    entries = []  # (last used, size, path)
    for kind in (CACHE_DIR.iterdir() if CACHE_DIR.is_dir() else ()):
        if not kind.is_dir() or (kind.name not in kinds if kinds is not None else kind.name == "reference2"):
            continue
        for group in kind.iterdir():
            for entry in (group.iterdir() if group.is_dir() else ()):
                try:
                    if entry.is_dir():
                        files = [f.stat() for f in entry.rglob("*") if f.is_file()]
                        used, size = entry.stat().st_mtime, sum(f.st_size for f in files)
                    else:
                        st = entry.stat()
                        used, size = st.st_mtime, st.st_size
                except OSError:
                    continue
                entries.append((used, size, entry))
    total = sum(size for _, size, _ in entries)
    for used, size, entry in sorted(entries, key=lambda e: e[0]):
        if total <= limit or now - used < 600:
            break
        try:
            shutil.rmtree(entry) if entry.is_dir() else entry.unlink()
            total -= size
        except OSError:
            pass
    if kinds is None:
        try:
            stamp.parent.mkdir(parents=True, exist_ok=True)
            stamp.touch()
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


def config_dir(module: str, config: pathlib.Path = CONFIG) -> pathlib.Path:
    """A module's directory in the configuration of the current version (or `config`: another
    version's config/<version>/arm9)."""
    if module == "main":
        return config
    if module.startswith("ov"):
        return config / "overlays" / module
    return config / module


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


_TABLES: dict[tuple[str, ...], "SymbolTable"] = {}


def symbol_table(mods: dict[str, dict]) -> "SymbolTable":
    """The modules' SymbolTable, read once per process (for callers that only read it)."""
    key = tuple(sorted(mods))
    if key not in _TABLES:
        _TABLES[key] = SymbolTable(mods)
    return _TABLES[key]


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


# A translation unit of several functions (an original source file, regrouped) lists them in
# the order the file defines them, which is the reverse of their addresses: mwccarm writes a
# file's functions into its object last first, each in a section of its own, and mwldarm lays
# an object's sections out in the object's order (docs/verification.md).
#
#   /* pockets_room: 5 functions, module ov097
#    * mwccarm 1.2/base -O4,s
#    * func_ov097_022a29e4 @ 0x022a29e4, 0x90 bytes, Thumb
#    * ...
#    * func_ov097_022a27c0 @ 0x022a27c0, 0x3c bytes, Thumb
#    */
#
# A C++ function's line ends with the name the compiler emits: `, emits _ZN5Obj_x6methodEv`.
UNIT_HEADER = re.compile(
    r"\A/\* (?P<unit>[A-Za-z_]\w*): (?P<count>\d+) functions, module (?P<module>\w+)\n"
    r" \* mwccarm (?P<drop>\S+) (?P<opt>-O[0-4],[sp])\n"
    r"(?P<functions>(?: \* \S+ @ 0x[0-9a-f]{8}, 0x[0-9a-f]+ bytes, (?:ARM|Thumb)(?:, emits \S+)?\n)+)"
    r" \*/\n")
UNIT_FUNCTION = re.compile(r" \* (?P<name>\S+) @ 0x(?P<addr>[0-9a-f]{8}), 0x(?P<size>[0-9a-f]+) bytes, "
                           r"(?P<isa>ARM|Thumb)(?:, emits (?P<emitted>\S+))?\n")


def parse_sources(path: pathlib.Path) -> list[Source]:
    """Every function a source file defines: one for a file of one function, each one its header
    lists for a unit (UNIT_HEADER), in the file's order. Empty when the header is not either."""
    text = path.read_text(encoding="utf-8", errors="replace")
    m = HEADER.match(text)
    if m:
        return [Source(path, m["name"], int(m["addr"], 16), int(m["size"], 16), m["isa"] == "Thumb",
                       m["module"], m["drop"], m["opt"], m["emitted"])]
    u = UNIT_HEADER.match(text)
    if not u:
        return []
    return [Source(path, f["name"], int(f["addr"], 16), int(f["size"], 16), f["isa"] == "Thumb",
                   u["module"], u["drop"], u["opt"], f["emitted"])
            for f in UNIT_FUNCTION.finditer(u["functions"])]


def parse_source(path: pathlib.Path) -> Source | None:
    """The function of a file of one function; for a unit, the first it lists (which stands for
    the unit where only the file matters: its compiler flags, its object)."""
    found = parse_sources(path)
    return found[0] if found else None


def header_end(text: str) -> int:
    """Where a source's header comment (HEADER or UNIT_HEADER) ends, or 0."""
    m = HEADER.match(text) or UNIT_HEADER.match(text)
    return text.index("*/", m.end() - 3) + 2 if m else 0


def unit_definition(body: str, name: str) -> re.Match | None:
    """Where a unit (UNIT_HEADER) defines `name`: at the start of a line, its parameters and
    the brace. `body` is the text after the header. A definition starts in the first column; a
    call that starts an indented line of a condition (`    f(a) != 0 || g(b)) {`) is not one."""
    return re.search(r"^(?=\S)[^\n;{}()]*\b" + re.escape(name.split("::")[-1])
                     + r"\s*\([^;{]*\)\s*(?:const\s*)?\{", body, re.M)


def masked(text: str) -> str:
    """`text` with comments, string and character literals blanked (same length, same lines)."""
    out, i, n = list(text), 0, len(text)
    while i < n:
        if text.startswith('//', i):
            j = text.find('\n', i)
            j = n if j < 0 else j
        elif text.startswith('/*', i):
            j = text.find('*/', i + 2)
            j = n if j < 0 else j + 2
        elif text[i] in '"\'':
            j = i + 1
            while j < n and text[j] != text[i]:
                j += 2 if text[j] == '\\' else 1
            j += 1
        else:
            i += 1
            continue
        for k in range(i, min(j, n)):
            if out[k] != '\n':
                out[k] = ' '
        i = j
    return ''.join(out)


DEFINITION = r"^(?=\S)[^\n;{{}}()#]*\b{name}\s*\([^;{{]*\)\s*(?:const\s*)?(?::[^;{{]*)?\{{"


def function_span(text: str, name: str) -> tuple[int, int] | None:
    """Where the source `text` defines the function `name` (a header's name): from the start of
    the definition's first line to just after its closing brace, or None when it has none the
    tools can find (a static initializer the compiler writes, a definition made by a macro).
    A function defined twice (the `asm` version for mwccarm and the C one for the PC, under
    #ifdef __MWERKS__) spans both."""
    plain = masked(text)
    pattern = re.compile(DEFINITION.format(name=re.escape(name.split("::")[-1])), re.M)
    start = end = None
    for m in pattern.finditer(plain):
        if end is not None and m.start() < end:
            continue
        depth, i = 0, m.end() - 1
        for i in range(m.end() - 1, len(plain)):
            depth += (plain[i] == "{") - (plain[i] == "}")
            if depth == 0:
                break
        if depth:
            return None
        start = m.start() if start is None else start
        end = i + 1
    return None if start is None else (start, end)


def function_text(text: str, name: str) -> str:
    """The text of one function of a source: its definition (function_span), or, where the
    source has no definition the tools find, everything after its header. This text is the same
    in a file of one function and in a unit (tools/regroup.py moves only what is outside the
    definitions), so a table that pins a function by it (runtime/native-*.json, tools/native_*)
    holds across regrouping."""
    span = function_span(text, name)
    return text[span[0]:span[1]] if span else text[header_end(text):]


def function_sha256(text: str, name: str) -> str:
    """The SHA-256 of function_text: what the Native tables pin a function's source by."""
    return hashlib.sha256(function_text(text, name).encode()).hexdigest()


def function_changed(text: str, name: str) -> str:
    """`text` with the definition of `name` changed (a blank line after its opening brace), for
    the tests of the tables that pin it (pinned_sha256)."""
    span = function_span(text, name)
    start, end = span if span else (header_end(text), len(text))
    brace = text.find("{", start, end)
    brace = start if brace < 0 else brace + 1
    return text[:brace] + "\n" + text[brace:]


def pinned_sha256(key: str, text: str) -> str:
    """What a Native table pins `text` by: for a function of src/ (`key` is its function_key)
    its function_sha256, for any other file (a Clean source, by its path) the whole text's."""
    if "." in key.rpartition("/")[2]:
        return hashlib.sha256(text.encode()).hexdigest()
    return function_sha256(text, key.partition("/")[2])


def function_key(src: Source) -> str:
    """`<module>/<name>`: how the Native tables name a function, whichever file defines it."""
    return f"{src.module}/{src.name}"


_FUNCTION_SOURCES: dict[str, Source] = {}
_SCANNED: set[str] = set()
_SCAN_LOCK = threading.Lock()


def function_source(key: str) -> Source | None:
    """The source under src/ that defines the function `key` (function_key): the file of that
    name, or the unit that lists it."""
    module, _, name = key.partition("/")
    for suffix in (".c", ".cpp"):
        path = SRC / module / f"{name}{suffix}"
        if path.is_file():
            found = [s for s in parse_sources(path) if s.name == name]
            if found:
                return found[0]
    # the scan is published whole, after it is done: tools/native.py looks keys up from threads
    with _SCAN_LOCK:
        if module not in _SCANNED:
            found: dict[str, Source] = {}
            for path in sorted((SRC / module).glob("*.c*")):
                for s in parse_sources(path):
                    found.setdefault(function_key(s), s)
            for k, s in found.items():
                _FUNCTION_SOURCES.setdefault(k, s)
            _SCANNED.add(module)
    return _FUNCTION_SOURCES.get(key)


def key_path(key: str) -> pathlib.Path:
    """The file that defines the function `key` (function_source)."""
    found = function_source(key)
    if found is None:
        raise FileNotFoundError(f"no source defines {key}")
    return found.path


def unit_keys(key: str, among) -> list[str]:
    """The keys of the functions the file of `key` defines that are in `among` (a table's keys),
    `key` always among them: what native.source_copy gives a table for the file's text."""
    keys = [function_key(src) for src in parse_sources(key_path(key))]
    return [k for k in keys if k == key or k in among]


def function_alone(text: str, key: str) -> str:
    """`text` (a copy of the file of `key`) without the definitions of the file's other
    functions: the function as a file of one function, for a test fixture that runs it alone
    and does not define what the unit's other functions use. Each of them is left declared (a
    function defined above the one that calls it has no prototype of its own, and gcc 14 and
    later refuse a call to an undeclared function); a member function is declared by its class."""
    for src in parse_sources(key_path(key)):
        if function_key(src) != key:
            span = function_span(text, src.name)
            if span is None:
                raise ValueError(f"{key}: no definition of {src.name} in the copy")
            head = text[span[0]:text.index("{", span[0])].strip()
            text = text[:span[0]] + ("" if "::" in head else head + ";") + text[span[1]:]
    return text


def source_of(key: str) -> Source:
    """The function `key` itself (function_source), not the first function of its file."""
    found = function_source(key)
    if found is None:
        raise FileNotFoundError(f"no source defines {key}")
    return found


def undeclared_uses(body: str, names: list[str]) -> list[str]:
    """The unit functions `body` names before declaring them. A unit lists its functions last
    address first, so a function often calls one defined below it: that needs a prototype above
    the call (gcc 14 and later refuse an implicit declaration even with -w). A prototype is a
    declaration at the start of a line ending in `;`; a definition counts from where it starts.
    C++ member functions are declared by their class and are not looked at."""
    out = []
    for name in names:
        if "::" in name:
            continue
        defined = unit_definition(body, name)
        proto = re.search(r"^(?!return\b)[A-Za-z_][\w \t\*]*[ \t\*]" + re.escape(name)
                          + r"\s*\([^;{]*\)\s*;", body, re.M)
        declared = min([m.start() for m in (defined, proto) if m] or [len(body)])
        used = re.search(r"\b" + re.escape(name) + r"\b", body)
        if used and used.start() < declared:
            out.append(name)
    return out


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
