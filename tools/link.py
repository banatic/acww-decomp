"""Link the whole ARM9 program with the original linker and check it against the ROM.

    python tools/link.py
    python tools/link.py --why [FILE...]   # plan only: why each source stays out of the link

Every game source whose object can stand alone becomes a `complete` translation unit; the
rest of each module comes from ds-decomp's delinked objects. dsd writes the linker script,
mwldarm links, and `dsd check modules` compares every module with the ROM. On success the
linked sources are listed in build/adm-kr/linked.json (read by progress_map.py), and the link
units in build/adm-kr/link/units.txt.

The object linked for a source is the compiled one, rewritten where the original link or the
original file differed (the rewritten copies are under build/adm-kr/link/obj):
- dead-stripping: an out-of-line copy of an inline function, or a D2 destructor, that
  nothing in the object reaches is dropped, as the original link dropped it;
- a shared copy: an inline body the ROM keeps in another object (in another module, or
  apart from the source's own code and data) is dropped and used by its ROM name;
- the sections of one name are put in ROM order, and the ROM's name is defined as well for
  data that a word elsewhere in the ROM points at;
- a link unit: sources whose pieces interleave in the ROM (the original file held their
  functions and data together) are joined into one object, a hole in their data that no
  source defines filled with the ROM's bytes, as ds-decomp's own objects hold it;
- the .bss of a source of main or autoload_2 is autoload_3's in this ROM, and links as a
  second object there.

A source (or link unit) stays out of the link, with its reason counted, when:
- a section of its object has no place in the ROM, or two pointers place it differently;
- a section lands in another module, or in a ROM section of another kind;
- its unit has a hole in its code, or two sources claim the same bytes differently;
- a data range does not start and end on the ROM's symbol boundaries;
- it claims bytes another source claims;
- its data order contradicts its code order relative to the other sources (link order);
- a word outside it points into its data where the ROM has no symbol;
- its code ends on a 2-byte boundary followed by a Thumb nop, which the compiler emits only
  between two functions of one object.

Needs ds-decomp's `dsd` (DSD; default build/tools/dsd, see INSTALL.md) and mwldarm from
MWCC_ROOT (1.2/base).
"""

from __future__ import annotations

import bisect
import collections
import concurrent.futures as cf
import functools
import hashlib
import json
import os
import pathlib
import re
import shlex
import shutil
import struct
import subprocess
import sys
import time

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import common as C  # noqa: E402
import verify as V  # noqa: E402

LINK = C.BUILD / "link"
CFG = LINK / "config" / "arm9"
DSD = pathlib.Path(os.environ.get("DSD", C.ROOT / "build" / "tools" / ("dsd.exe" if os.name == "nt" else "dsd")))
SECTION = re.compile(r"\s+(\.\w+)\s+start:0x([0-9a-f]+) end:0x([0-9a-f]+)")
SYMBOL = re.compile(r"(\S+) kind:(\w+)(?:\([^)]*\))? addr:0x([0-9a-f]+)")
RELOC = re.compile(r"from:0x([0-9a-f]+) kind:\w+ to:0x([0-9a-f]+) module:(\S+)")
RELOC_KIND = re.compile(r"from:0x([0-9a-f]+) kind:(\w+) to:0x([0-9a-f]+) module:(\S+)")
ORDER = [".text", ".init", ".ctor", ".rodata", ".data", ".bss"]
# modules whose .bss is autoload_3's in this ROM (their own .bss is empty): a source's
# uninitialised data lands there, and links as a second entry in autoload_3's delinks.txt
BSS_IN_AUTOLOAD_3 = ("main", "autoload_2")


def bss_name(f: str) -> str:
    """The name of the object holding the .bss a source of main or autoload_2 has in
    autoload_3 (ds-decomp takes one file name in one module only)."""
    p = pathlib.PurePosixPath(f)
    return str(p.with_name(f"{p.stem}_bss{p.suffix}"))


def home(module: str, name: str) -> str:
    """The module a section of a source of `module` lands in."""
    return "autoload_3" if name == ".bss" and module in BSS_IN_AUTOLOAD_3 else module


def module_dir(root: pathlib.Path, module: str) -> pathlib.Path:
    return root / C.config_dir(module).relative_to(C.CONFIG)


def module_sections(module: str) -> list[tuple[str, int, int]]:
    rows = []
    for line in (C.config_dir(module) / "delinks.txt").read_text().splitlines():
        m = SECTION.match(line)
        if not m:
            break
        rows.append((m.group(1), int(m.group(2), 16), int(m.group(3), 16)))
    return rows


# ------------------------------------------------------------------------------ objects

# sections that describe code rather than land in a module (dsd places none of them)
META = (".comment", ".exceptix", ".exception")


def strippable(elf: C.Elf, si: int) -> bool:
    """A section the original link dropped when nothing used it: mwccarm writes an out-of-line
    copy of every inline function it emits (a weak symbol, bind 2, or 13 in mwccarm's
    objects) and the base-object destructor (D2) of a class whose destructor it defines, used
    or not."""
    defs = [y for y in elf.symbols if y.shndx == si and y.type in (1, 2) and y.name
            and not y.name.startswith("$")]
    return bool(defs) and all(y.bind in (2, 13) or y.name.endswith("D2Ev") for y in defs)


def dead_sections(elf: C.Elf, root: int, secs: dict) -> set[int]:
    """The strippable sections that nothing kept in the object reaches through a relocation,
    starting from the function's own section and every section that is not strippable."""
    refs = collections.defaultdict(set)
    for si in secs:
        for _, _, s, _ in elf.relocations(si):
            refs[si].add(s.shndx)
    live, work = set(), [root, *(si for si in secs if not strippable(elf, si))]
    while work:
        si = work.pop()
        if si not in live:
            live.add(si)
            work += refs[si]
    return set(secs) - live


class Obj:
    """A relocatable ELF taken apart so it can be written back with sections dropped, or
    joined with other objects into one (a link unit)."""

    def __init__(self, data: bytes):
        self.header = data[:0x34]
        shoff, = struct.unpack_from("<I", data, 0x20)
        shnum, shstrndx = struct.unpack_from("<HH", data, 0x30)
        raw = [struct.unpack_from("<10I", data, shoff + 40 * i) for i in range(shnum)]
        names = raw[shstrndx][4]

        def string(base: int, off: int) -> str:
            return data[base + off:data.index(b"\0", base + off)].decode("latin-1")

        # [name, type, flags, addralign, entsize, bytes]
        self.secs = [[string(names, h[0]), h[1], h[2], h[8], h[9],
                      b"" if h[1] == 8 else data[h[4]:h[4] + h[5]], h[5]] for h in raw]
        self.syms: list[list] = []  # [name, value, size, info, other, shndx]
        # target section -> (type, flags, [[offset, type, symbol, addend]])
        self.rels: dict[int, tuple[int, int, list]] = {}
        for h in raw:
            if h[1] == 2:
                strtab = raw[h[6]][4]
                for o in range(h[4], h[4] + h[5], 16):
                    n, value, size, info, other, shndx = struct.unpack_from("<IIIBBH", data, o)
                    self.syms.append([string(strtab, n), value, size, info, other, shndx])
        for h in raw:
            if h[1] in (4, 9):
                ent = 12 if h[1] == 4 else 8
                rows = []
                for o in range(h[4], h[4] + h[5], ent):
                    off, info = struct.unpack_from("<II", data, o)
                    add = struct.unpack_from("<i", data, o + 8)[0] if ent == 12 else None
                    rows.append([off, info & 0xFF, info >> 8, add])
                self.rels[h[7]] = (h[1], h[2], rows)

    def content(self) -> list[int]:
        """Indices of the sections other than the symbol, string and relocation tables."""
        return [i for i, s in enumerate(self.secs) if i and s[1] not in (2, 3, 4, 9)]


def write_object(objs: list[Obj], keep: list[tuple[int, int]],
                 alias: dict[tuple[int, int], tuple[int, int]] | None = None) -> bytes:
    """One relocatable ELF holding the sections `keep` [(object, section)] of `objs`, in that
    order. A symbol of a section left out is dropped; `alias` maps a left-out section to a
    kept one with the same bytes (a duplicate inline body), whose symbols stand in for its.
    Local symbols stay local; a global that one object defines and another uses is the
    definition. A .exceptix record of a function left out goes with it."""
    alias = alias or {}
    new, n = {}, 1  # section header index of each kept section; its relocations follow it
    for k, i in keep:
        new[k, i] = n
        n += 2 if i in objs[k].rels else 1
    locals_, globals_, symmap = [[""] + [0] * 5], {}, {}
    pending = []
    for k, o in enumerate(objs):
        for j, (name, value, size, info, other, shndx) in enumerate(o.syms):
            if j == 0:
                continue
            if 0 < shndx < 0xFF00:
                ks = alias.get((k, shndx), (k, shndx))
                if ks not in new:
                    continue
                if ks != (k, shndx):
                    pending.append((k, j, ks))
                    continue
                row = [name, value, size, info, other, new[ks]]
            else:
                row = [name, value, size, info, other, shndx]
            if info >> 4 == 0:
                symmap[k, j] = ("L", len(locals_))
                locals_.append(row)
            else:
                if name not in globals_ or (shndx and not globals_[name][5]):
                    globals_[name] = row
                symmap[k, j] = ("G", name)
    for k, j, ks in pending:  # a symbol of a duplicate: the kept copy's symbol of that name
        name, value, _, info, _, _ = objs[k].syms[j]
        if info >> 4:
            if name not in globals_ or not globals_[name][5]:  # a second name for the kept copy
                globals_[name] = [name, value, *objs[k].syms[j][2:5], new[ks]]
            symmap[k, j] = ("G", name)
        else:
            row = next((n for n, r in enumerate(locals_) if r[0] == name and r[1] == value
                        and r[5] == new[ks]), None)
            if row is None:
                row = len(locals_)
                locals_.append([name, value, *objs[k].syms[j][2:5], new[ks]])
            symmap[k, j] = ("L", row)
    gnames = list(globals_)
    index = {("L", n): n for n in range(len(locals_))}
    index.update({("G", g): len(locals_) + n for n, g in enumerate(gnames)})
    syms = locals_ + [globals_[g] for g in gnames]

    # section headers: null, each kept section followed by its relocations, the tables
    out_secs = []
    for ks in keep:
        k, i = ks
        o = objs[k]
        name, typ, flags, align, entsize, data, size = o.secs[i]
        rows = o.rels[i][2] if i in o.rels else []
        mapped, dropped = [], []
        for off, rtype, sym, add in rows:
            if (k, sym) in symmap:
                mapped.append([off, rtype, index[symmap[k, sym]], add])
            else:
                dropped.append(off)
        if dropped:
            if name != ".exceptix":
                raise ValueError(f"{name} refers to a section left out")
            gone = {off // 12 for off in dropped}
            data = b"".join(data[r * 12:r * 12 + 12] for r in range(len(data) // 12) if r not in gone)
            size = len(data)
            mapped = [[off - 12 * sum(g < off // 12 for g in gone), *rest]
                      for off, *rest in mapped if off // 12 not in gone]
        out_secs.append([name, typ, flags, align, entsize, data, size, 0, 0])
        if i in o.rels:
            rtyp, rflags, _ = o.rels[i]
            ent = 12 if rtyp == 4 else 8
            body = b"".join(struct.pack("<II", off, (s << 8) | t) + (struct.pack("<i", a) if ent == 12 else b"")
                            for off, t, s, a in mapped)
            out_secs.append([(".rela" if rtyp == 4 else ".rel") + name, rtyp, rflags, 4, ent, body,
                             len(body), "symtab", len(out_secs)])
    symtab = len(out_secs) + 1
    strtab = bytearray(b"\0")
    symbytes = bytearray()
    for name, value, size, info, other, shndx in syms:
        n = 0
        if name:
            n = len(strtab)
            strtab += name.encode("latin-1") + b"\0"
        symbytes += struct.pack("<IIIBBH", n, value, size, info, other, shndx)
    out_secs.append([".symtab", 2, 0, 4, 16, bytes(symbytes), len(symbytes), symtab + 1, len(locals_)])
    out_secs.append([".strtab", 3, 0, 1, 0, bytes(strtab), len(strtab), 0, 0])
    shstr = bytearray(b"\0")
    out_secs.append([".shstrtab", 3, 0, 1, 0, b"", 0, 0, 0])
    name_off = []
    for s in out_secs:
        name_off.append(len(shstr))
        shstr += s[0].encode("latin-1") + b"\0"
    out_secs[-1][5] = bytes(shstr)
    out_secs[-1][6] = len(shstr)
    body = bytearray(objs[0].header)
    heads = [b"\0" * 40]
    for n, (name, typ, flags, align, entsize, data, size, link, info) in enumerate(out_secs):
        while len(body) % max(4, align or 1):
            body += b"\0"
        off = len(body)
        body += data
        if link == "symtab":
            link = symtab
        heads.append(struct.pack("<10I", name_off[n], typ, flags, 0, off, size, link, info, align, entsize))
    while len(body) % 4:
        body += b"\0"
    shoff = len(body)
    body += b"".join(heads)
    struct.pack_into("<I", body, 0x20, shoff)
    struct.pack_into("<HHH", body, 0x2E, 40, len(heads), len(heads) - 1)
    return bytes(body)


def source_object(plan: dict, rename: dict[str, str], exports: dict[int, str],
                  away: bool = False) -> tuple[Obj, bool]:
    """A source's object as it is linked: every name config/aliases.txt lists is the symbol's
    own name (`rename`; a branch to an absolute symbol at an odd, Thumb, address lands one
    halfword late, so a call by an alias needs the real symbol), and each symbol of a shared
    copy (Planner.plan's "extern") is a reference to the ROM's copy, by its name there.
    With `away`, its .bss is another object's (bss_object): each symbol there is a reference,
    a static by the ROM's name. Also says whether anything changed."""
    obj, _ = C.compile_source(C.parse_source(C.ROOT / plan["file"]))
    o = Obj(obj)
    changed = bool(plan.get("extern")) or away
    if away:
        start = {si: s[3] for si, s in zip(plan["index"], plan["sections"])}
        rom = {a: n for a, n, _ in module_symbols("autoload_3")}
        for y in o.syms:
            if y[5] in start and o.secs[y[5]][1] == 8 and y[0] and not y[0].startswith("$"):
                name = y[0] if y[3] >> 4 else rom[start[y[5]] + y[1]]
                y[:] = [name, 0, 0, (1 << 4) | (y[3] & 0xF), 0, 0]
    for j, name in plan.get("extern", ()):
        o.syms[j][:4] = [name, 0, 0, (1 << 4) | (o.syms[j][3] & 0xF)]
        o.syms[j][5] = 0
    for y in o.syms:
        if y[5] == 0 and y[0] in rename:
            y[0] = rename[y[0]]
            changed = True
    have = {y[0] for y in o.syms if y[5]}
    for addr, name in exports.items():  # the ROM's names for its data (choose's EXPORTS)
        si = next((i for i, s in zip(plan["index"], plan["sections"]) if s[3] <= addr < s[4]), None)
        if si is not None and name not in have:
            o.syms.append([name, addr - plan["sections"][plan["index"].index(si)][3], 0, (1 << 4) | 1, 0, si])
            changed = True
    return o, changed


def linked_object(plan: dict, rename: dict[str, str], exports: dict[int, str],
                  away: bool = False) -> bytes | None:
    """The object to link for a source, if it is not the compiled one: without the sections
    the original link would not have kept (Planner.plan's "strip"), see source_object."""
    o, changed = source_object(plan, rename, exports, away)
    keep = [i for i in o.content() if i not in plan["strip"] and not (away and o.secs[i][1] == 8)]
    # mwldarm lays out an object's sections of one name in the object's order; mwccarm's
    # order of a function's literals is not always the ROM's
    start = {si: s[3] for si, s in zip(plan["index"], plan["sections"])}
    for name in {o.secs[i][0] for i in start}:
        mine = [start[i] for i in keep if i in start and o.secs[i][0] == name]
        if mine != sorted(mine):
            changed = True
            keep.sort(key=lambda i: (o.secs[i][0], start.get(i, 0)))
            break
    if not changed and not plan["strip"]:
        return None
    return write_object([o], [(0, i) for i in keep])


def bss_object(template: Obj, a: int, b: int, names: list[list]) -> bytes:
    """The object for the .bss [a, b) in autoload_3 of a source (or link unit) of main or
    autoload_2: the ROM's symbols there and the source's own global names [name, address]."""
    o = filler(template, "autoload_3", [(".bss", a, b)])
    have = {y[0] for y in o.syms}
    o.syms += [[n, x - a, 0, (1 << 4) | 1, 0, 1] for n, x in names if a <= x < b and n not in have]
    return write_object([o], [(0, 1)])


def filler(template: Obj, mod: str, holes: list[tuple[str, int, int]]) -> Obj:
    """An object holding the ROM's bytes and symbols for the holes [(section, start, end)] of
    a link unit, with the pointers there as relocations (see filler_targets)."""
    o = Obj.__new__(Obj)
    o.header, o.secs, o.syms, o.rels = template.header, [["", 0, 0, 0, 0, b"", 0]], [["", 0, 0, 0, 0, 0]], {}
    flags = {s[0]: s[2] for s in template.secs}
    undef: dict[str, int] = {}
    for name, a, b in holes:
        si = len(o.secs)
        bss = name == ".bss"
        at = home(mod, name)
        img, base = C.module_image(at), C.modules()[at]["base"]
        o.secs.append([name, 8 if bss else 1, flags.get(name, 3 if name != ".rodata" else 2), 4, 0,
                       b"" if bss else img[a - base:b - base], b - a])
        o.syms += [[n, x - a, 0, (1 << 4) | 1, 0, si] for x, n, _ in between(module_symbols(at), a, b)]
        rows = []
        for off, name_, add in ([] if bss else filler_targets(at, a, b)):
            if name_ not in undef:
                undef[name_] = len(o.syms)
                o.syms.append([name_, 0, 0, 2 << 4, 0, 0])  # weak, as in ds-decomp's objects
            rows.append([off, 2, undef[name_], add])
        if rows:
            o.rels[si] = (4, 0, rows)
    return o


def unit_object(plans: list[dict], copies: dict, holes: list, rename: dict[str, str],
                exports: dict[int, str], away: bool = False) -> bytes:
    """One object for a link unit: its sources' objects joined, each section at its place in
    ROM order (sections of each name in address order), every copy of a section another
    member has (`copies`) left to that member's, and the holes filled from the ROM."""
    objs, placed, rest = [], [], []
    pos = {r["file"]: k for k, r in enumerate(plans)}
    for k, r in enumerate(plans):
        o, _ = source_object(r, rename, exports, away)
        objs.append(o)
        start = {si: s[3] for si, s in zip(r["index"], r["sections"])}
        for i in o.content():
            if i in r["strip"] or (r["file"], i) in copies or (away and o.secs[i][1] == 8):
                continue
            name = o.secs[i][0]
            if i in start:
                placed.append((ORDER.index(name) if name in ORDER else 99, start[i], k, i))
            elif name != ".comment" or k == 0:
                rest.append((k, i))
    holes = [h for h in holes if not (away and h[0] == ".bss")]
    if holes:
        objs.append(filler(objs[0], plans[0]["module"], holes))
        placed += [(ORDER.index(name) if name in ORDER else 99, a, len(objs) - 1, i + 1)
                   for i, (name, a, _) in enumerate(holes)]
    alias = {(pos[f], i): (pos[g], j) for (f, i), (g, j) in copies.items()}
    return write_object(objs, [(k, i) for _, _, k, i in sorted(placed)] + rest, alias)


# ------------------------------------------------------------------------------ placement

class Planner:
    """Where each section of a source's object lands in the ROM. The function's section is
    at the function's address; any other section is placed by pointers the ROM holds into
    it, from the function's literal pool or from an already placed section."""

    def __init__(self):
        self.chk = V.Checker()
        self.sections = {m: module_sections(m) for m in self.chk.mods}
        # config/aliases.txt: second names some sources use; link() defines for the linker the
        # ones whose canonical symbol exists, at its address
        pairs = [line.split() for line in (C.CONFIG / "aliases.txt").read_text().splitlines()
                 if line.strip() and not line.startswith("#")]
        names = {m.group(1) for p in C.CONFIG.rglob("symbols.txt") for line in p.read_text().splitlines()
                 if (m := SYMBOL.match(line))}
        self.aliases = {a for a, c in pairs if c not in names}
        self.rename = {a: c for a, c in pairs if c in names}
        # module -> {address: name} from symbols.txt, and module -> {address: the modules
        # relocs.txt says the word there points into}
        self.names: dict[str, dict[int, str]] = {}
        self.targets: dict[str, dict[int, list[str]]] = {}
        for m in self.chk.mods:
            d = C.config_dir(m)
            if not (d / "symbols.txt").exists():
                continue
            names = self.names[m] = {}
            for line in (d / "symbols.txt").read_text().splitlines():
                if x := SYMBOL.match(line):
                    names.setdefault(int(x.group(3), 16), x.group(1))
            self.targets[m] = {int(x.group(1), 16): reloc_modules(x.group(3))
                               for line in (d / "relocs.txt").read_text().splitlines()
                               if (x := RELOC.match(line)) and x.group(3) != "none"}

    def where(self, addr: int, prefer: str, only: list[str] | None = None) -> tuple[str | None, str | None]:
        for m in only or (prefer, *C.RESIDENT, *self.sections):
            for name, a, b in self.sections.get(m, ()):
                if a <= addr < b:
                    return m, name
        return None, None

    def place(self, elf: C.Elf, src: C.Source, fn: C.ElfSymbol, secs: dict):
        """Each section's candidate addresses, and the modules the relocation that placed it
        names (overlays share addresses)."""
        anchors = collections.defaultdict(set)
        anchors[fn.shndx].add(src.address - fn.value)
        only: dict[int, list[str] | None] = {fn.shndx: [src.module]}
        work, done = [fn.shndx], set()
        while work:
            si = work.pop()
            if si in done:
                continue
            done.add(si)
            base = min(anchors[si])
            here = self.where(base, src.module, only.get(si))[0] or src.module
            for off, typ, s, add in elf.relocations(si):
                if typ != 2 or s.shndx in (0, fn.shndx) or s.shndx not in secs:
                    continue
                word = self.chk.rom_abs(base + off, here, 4)
                if len(word) < 4:
                    continue
                value, = struct.unpack("<I", word)
                if s.type == 2:
                    value &= ~1
                anchors[s.shndx].add(value - (add or 0) - s.value)
                if s.shndx not in only:
                    only[s.shndx] = next((self.targets[m][base + off] for m in (here, *C.RESIDENT)
                                          if base + off in self.targets.get(m, {})), None)
                work.append(s.shndx)
        return anchors, only

    def shared(self, elf: C.Elf, root: int, secs: dict, anchors: dict, only: dict,
               module: str) -> dict[int, dict[int, str | None]]:
        """The placed copies of inline bodies (sections whose symbols are all weak) that are
        the ROM's copy kept from another object: in another module, or apart from this
        source's own code and data of that kind (a run of same-named sections with no
        section of its own). Each maps the symbols in it to the name symbols.txt has at their
        address; a copy whose symbol the rest of the object uses without a name stays."""
        def defs(si: int) -> list[C.ElfSymbol]:
            return [y for y in elf.symbols if y.shndx == si and y.type in (1, 2) and y.name
                    and not y.name.startswith("$")]
        weak = {si for si in secs if si != root and defs(si) and all(y.bind in (2, 13) for y in defs(si))}
        mod = {si: self.where(min(anchors[si]), module, only.get(si))[0] for si in secs if anchors.get(si)}
        cand = {si for si in weak if si in mod and mod[si] != module}
        by = collections.defaultdict(list)
        for si, m in mod.items():
            if m == module:
                base = min(anchors[si])
                by[elf.sections[si].name].append((base, base + elf.sections[si].size, si))
        for parts in by.values():
            parts.sort()
            runs = [[parts[0]]]
            for p in parts[1:]:
                if aligned(runs[-1][-1][1], p[0]):
                    runs[-1].append(p)
                else:
                    runs.append([p])
            own = [r for r in runs if any(si not in weak for _, _, si in r)]
            if own or len(runs) > 1:
                cand |= {si for r in runs if r not in own for _, _, si in r if si in weak}
        out: dict[int, dict[int, str | None]] = {}
        for si in cand:
            names = self.names.get(mod[si], {})
            out[si] = {j: names.get(min(anchors[si]) + y.value) for j, y in enumerate(elf.symbols)
                       if y.shndx == si and y.name}
        index = {id(y): j for j, y in enumerate(elf.symbols)}
        while True:  # a copy is shared only if every use from what stays has a ROM name
            bad = {y.shndx for si in secs if si not in out for _, _, y, _ in elf.relocations(si)
                   if y.shndx in out and out[y.shndx].get(index[id(y)]) is None}
            if not bad:
                return out
            for si in bad:
                del out[si]

    def plan(self, path: pathlib.Path) -> dict | None:
        src = C.parse_source(path)
        if src is None:
            return None
        rel = path.relative_to(C.ROOT).as_posix()
        obj, _ = C.compile_source(src)
        if obj is None:
            return {"file": rel, "error": "does not compile"}
        elf = C.Elf(obj)
        fn = elf.function(src.object_symbol)
        if fn is None:
            return {"file": rel, "error": "function not in the object"}
        secs = {i: s for i, s in enumerate(elf.sections) if s.size and s.type in (1, 8)
                and not s.name.startswith(META)}
        dead = dead_sections(elf, fn.shndx, secs)
        secs = {i: s for i, s in secs.items() if i not in dead}
        anchors, only = self.place(elf, src, fn, secs)
        shared = self.shared(elf, fn.shndx, secs, anchors, only, src.module)
        extern = []
        if shared:
            # what only the shared copies used goes with them
            rest = {i: s for i, s in secs.items() if i not in shared}
            gone = dead_sections(elf, fn.shndx, rest)
            dead |= set(shared) | gone
            secs = {i: s for i, s in rest.items() if i not in gone}
            index = {id(y): j for j, y in enumerate(elf.symbols)}
            used = {index[id(y)] for si in secs for _, _, y, _ in elf.relocations(si)}
            extern = sorted([j, n] for m in shared.values() for j, n in m.items() if j in used)
        # "index": each section's index in the object; "same": its bytes and relocations, to
        # tell an identical copy (an inline body two sources of a link unit both emit);
        # "extern": [symbol index, name] of each symbol of a shared copy, used by its ROM name
        out = {"file": rel, "module": src.module, "root": fn.shndx, "sections": [], "strip": sorted(dead),
               "index": list(secs), "same": [], "extern": extern}
        for si, s in secs.items():
            out["same"].append(hashlib.sha1(repr((elf.section_bytes(si), sorted(
                (o, t, y.name, y.value if y.bind == 0 else 0, a) for o, t, y, a in elf.relocations(si))))
                .encode()).hexdigest()[:16])
            if not anchors.get(si):
                out["sections"].append([s.name, None, None, None, s.size])
                out["error"] = "a section has no place in the ROM"
                continue
            if len(anchors[si]) > 1:
                out["error"] = "pointers place a section differently"
            base = min(anchors[si])
            out["sections"].append([s.name, *self.where(base, src.module, only.get(si)), base, base + s.size])
        out["globals"] = [[y.name, min(anchors[y.shndx]) + y.value] for y in elf.symbols
                          if y.bind == 1 and y.name and y.shndx in secs and y.shndx != fn.shndx
                          and anchors.get(y.shndx)]
        # the statics in .bss, by address: named by the ROM when the .bss is another object's
        out["bss_locals"] = sorted(min(anchors[y.shndx]) + y.value for y in elf.symbols
                                   if y.bind == 0 and y.name and not y.name.startswith("$")
                                   and y.shndx in secs and secs[y.shndx].type == 8 and anchors.get(y.shndx))
        if "error" not in out and any(y.shndx == 0 and y.name in self.aliases for y in elf.symbols):
            out["error"] = "uses a name config/aliases.txt maps to no symbol"
        return out


# ------------------------------------------------------------------------------ choosing TUs

def reloc_modules(spec: str) -> list[str]:
    if spec == "main":
        return ["main"]
    if spec.startswith("overlay"):
        return [f"ov{int(x):03d}" for x in spec[spec.index("(") + 1:-1].split(",")]
    if spec.startswith("autoload"):
        return [f"autoload_{spec[spec.index('(') + 1:-1]}"]
    return [spec]


def longest_increasing(items: list[tuple[str, int]]) -> set[str]:
    """Names on a longest increasing run of `items` [(name, value)]."""
    tails, idx, prev = [], [], [None] * len(items)
    for i, (_, v) in enumerate(items):
        k = bisect.bisect_left(tails, v)
        if k == len(tails):
            tails.append(v)
            idx.append(i)
        else:
            tails[k] = v
            idx[k] = i
        prev[i] = idx[k - 1] if k else None
    keep, i = set(), idx[-1] if idx else None
    while i is not None:
        keep.add(items[i][0])
        i = prev[i]
    return keep


# source -> the reason it stays out of the link (filled by choose)
LEFT_OUT: dict[str, str] = {}
# the first source of a link unit -> (its sources in ROM order, {(source, section index):
# (source, section index)} for each section that is a copy of another member's)
UNITS: dict[str, tuple[list[str], dict, list]] = {}


# source (or link unit) -> {address: name}: the ROM's names its object defines as well
EXPORTS: dict[str, dict[int, str]] = {}
# source -> (reason, the addresses that made it fail that check), printed by --why
DETAIL: dict[str, tuple[str, str]] = {}


def aligned(a1: int, b0: int) -> bool:
    """Does a section starting at b0 follow one ending at a1 in the same object (padding to 4)?"""
    return a1 <= b0 <= (a1 + 3) & ~3


@functools.cache
def module_relocs(mod: str) -> list[tuple[int, str, int, str]]:
    """(from, kind, to, module) of each relocation in a module's relocs.txt, by address."""
    return sorted((int(m.group(1), 16), m.group(2), int(m.group(3), 16), m.group(4))
                  for line in (C.config_dir(mod) / "relocs.txt").read_text().splitlines()
                  if (m := RELOC_KIND.match(line)))


@functools.cache
def module_symbols(mod: str) -> list[tuple[int, str, bool]]:
    """(address, name, Thumb) of each symbol in a module's symbols.txt, by address."""
    out = {}
    for line in (C.config_dir(mod) / "symbols.txt").read_text().splitlines():
        if m := SYMBOL.match(line):
            out.setdefault(int(m.group(3), 16), (m.group(1), "thumb" in line))
    return sorted((a, n, th) for a, (n, th) in out.items())


def between(rows: list, a: int, b: int) -> list:
    """The rows of a list sorted by address whose address is in [a, b)."""
    keys = [r[0] for r in rows]
    return rows[bisect.bisect_left(keys, a):bisect.bisect_left(keys, b)]


def filler_targets(mod: str, a: int, b: int) -> list[tuple[int, str, int]] | None:
    """For a hole [a, b) of a link unit's data: (offset, symbol, addend) of each pointer the
    ROM has there, by the symbol each points to (as ds-decomp's own gap objects name it), or
    None when one cannot be named."""
    out = []
    for frm, kind, to, spec in between(module_relocs(mod), a, b):
        mods = reloc_modules(spec) if spec != "none" else []
        if kind != "load" or len(mods) != 1:
            return None
        syms = module_symbols(mods[0])
        k = bisect.bisect_right([s[0] for s in syms], to) - 1
        if k < 0 or (syms[k][2] and to != syms[k][0] + 1):  # a Thumb function: the linker adds the bit
            return None
        addr, name, thumb = syms[k]
        out.append((frm - a, name, to - addr - (1 if thumb else 0)))
    return out


def find_units(good: dict[str, dict], seeds: list[str], module: dict[str, str], root: dict[str, int],
               banned: dict[frozenset, str]) -> tuple[dict, dict[str, str]]:
    """Link units: the sources a source with gaps between its same-named sections has to be
    linked with as one object, because the original file held their functions and data
    interleaved. A unit is the closure of the sources whose pieces lie inside its span of a
    section, and it holds only when, sorted by ROM address, each section's pieces follow one
    another one without a hole no member defines. Two members' sections at one place are one
    copy of one thing (both match the ROM there: an inline body, a class's vtable or a
    destructor two sources emit) and count once. A hole in the data that no source defines
    (data the sources use by name, or a static object a constructor elsewhere builds) is
    filled with the ROM's bytes and symbols, as ds-decomp's gap objects hold them; a hole in
    the code is not. `good`: source -> {section: [(start, end, index, same)]}.
    Returns ({first source: (members, {section: (start, end)}, copies, holes)},
    {seed: reason})."""
    by = collections.defaultdict(list)  # (module, section) -> [(start, end, source)]
    for f, secs in good.items():
        for name, parts in secs.items():
            by[module[f], name] += [(a, b, f) for a, b, _, _ in parts]
    longest = {}
    for k, v in by.items():
        v.sort()
        longest[k] = max(b - a for a, b, _ in v)
    starts = {k: [a for a, _, _ in v] for k, v in by.items()}
    units, failed, done = {}, {}, set()
    for seed in seeds:
        if seed in done:
            continue
        mod, group = module[seed], {seed}
        while True:
            spans = {}
            for f in group:
                for name, parts in good[f].items():
                    lo, hi = spans.get(name, (1 << 40, 0))
                    spans[name] = (min(lo, parts[0][0]), max(hi, parts[-1][1]))
            new = set()
            for name, (lo, hi) in spans.items():
                k = (mod, name)
                i = bisect.bisect_left(starts[k], lo - longest[k])
                j = bisect.bisect_left(starts[k], hi)
                new |= {f for a, b, f in by[k][i:j] if a < hi and b > lo}
            if new <= group:
                break
            group |= new
        done |= group
        reason, copies, merged, holes = None, {}, {}, []
        for name in spans:
            # a source's own function first: the copy kept of two at one place
            parts = sorted((a, b, i != root[f], f, i) for f in group for a, b, i, _ in good[f].get(name, ()))
            kept, end = parts[0], parts[0][1]
            for cur in parts[1:]:
                if cur[:2] == kept[:2]:
                    copies[cur[3], cur[4]] = (kept[3], kept[4])
                    continue
                if cur[0] < end:
                    reason = reason or "link unit: two sources claim the same bytes"
                elif not aligned(end, cur[0]):
                    hole = (name, (end + 3) & ~3, cur[0])
                    if name in (".text", ".init") or (
                            name != ".bss" and filler_targets(home(mod, name), *hole[1:]) is None):
                        if not reason:
                            reason = "link unit: a hole no source defines"
                            DETAIL.update({f: (reason, f"{name} {hole[1]:#x}-{hole[2]:#x}") for f in group})
                    holes.append(hole)
                kept, end = cur, max(end, cur[1])
            merged[name] = (parts[0][0], end)
        members = sorted(group, key=lambda f: next(iter(good[f].get(".text") or good[f][".init"]))[0])
        reason = reason or banned.get(frozenset(group))
        if reason:
            failed.update({f: reason for f in seeds if f in group})
        else:
            units[members[0]] = (members, merged, copies, holes)
    return units, failed


def choose(plans: list[dict], mods: dict) -> tuple[dict[str, list], collections.Counter]:
    """module -> [(file, {section: (start, end)})] of the sources (and link units, by their
    first source) that can be linked, and the reasons the others cannot (counted, and per
    source in LEFT_OUT). A link unit that fails a check is taken apart and its sources tried
    alone."""
    banned: dict[frozenset, str] = {}
    while True:
        entries, why, broken = choose_once(plans, mods, banned)
        if not broken:
            return entries, why
        banned.update(broken)


@functools.cache
def reloc_targets() -> dict[str, list[tuple[int, int]]]:
    """module -> [(target, source address)] of every relocation in config/ into it."""
    refs: dict[str, list] = collections.defaultdict(list)
    for p in C.CONFIG.rglob("relocs.txt"):
        for line in p.read_text().splitlines():
            m = RELOC.match(line)
            if m and m.group(3) != "none":
                for mod in reloc_modules(m.group(3)):
                    refs[mod].append((int(m.group(2), 16), int(m.group(1), 16)))
    return refs


def choose_once(plans: list[dict], mods: dict, banned: dict[frozenset, str]):
    LEFT_OUT.clear()
    UNITS.clear()
    EXPORTS.clear()
    why: collections.Counter = collections.Counter()
    entries: dict[str, list] = collections.defaultdict(list)
    exported: dict[str, dict[int, str]] = {}
    good, seeds, module = {}, [], {}
    by_file = {r["file"]: r for r in plans}
    for r in plans:
        if r.get("error"):
            why[r["error"]] += 1
            LEFT_OUT[r["file"]] = r["error"]
            continue
        secs: dict[str, list] = {}
        reason = None
        for (name, mod, romsec, start, end), si, same in zip(r["sections"], r["index"], r["same"]):
            if mod != r["module"] and mod != home(r["module"], name):
                reason = "data in another module"
            elif romsec != name:
                reason = f"{name} lands in {romsec}"
            if reason:
                break
            secs.setdefault(name, []).append((start, end, si, same))
        if reason:
            why[reason] += 1
            LEFT_OUT[r["file"]] = reason
            continue
        for parts in secs.values():
            parts.sort()
        good[r["file"]], module[r["file"]] = secs, r["module"]
        exported[r["file"]] = {a: n for n, a in r["globals"]}
        if any(not aligned(p[1], q[0]) for parts in secs.values() for p, q in zip(parts, parts[1:])):
            seeds.append(r["file"])
    a3 = {a for a, _, _ in module_symbols("autoload_3")}
    for f in list(good):
        if home(module[f], ".bss") != module[f] and any(a not in a3 for a in by_file[f]["bss_locals"]):
            del good[f]
            if f in seeds:
                seeds.remove(f)
            why["a static in autoload_3's .bss has no symbol there"] += 1
            LEFT_OUT[f] = "a static in autoload_3's .bss has no symbol there"
    units, failed = find_units(good, seeds, module, {r["file"]: r.get("root") for r in plans}, banned)
    in_unit = {f for members, *_ in units.values() for f in members}
    for f, reason in failed.items():
        why[reason] += 1
        LEFT_OUT[f] = reason
    for f, secs in good.items():
        if f in failed or f in in_unit:
            continue
        entries[module[f]].append((f, {n: (p[0][0], p[-1][1]) for n, p in secs.items()}))
    for key, (members, merged, copies, holes) in units.items():
        UNITS[key] = (members, copies, holes)
        entries[module[key]].append((key, merged))
        exported[key] = {a: n for f in members for a, n in exported[f].items()}
        for name, a, b in holes:
            exported[key].update({x: n for x, n, _ in between(module_symbols(home(module[key], name)), a, b)})

    bad: set[str] = set()
    broken: dict[frozenset, str] = {}

    def drop(f: str, reason: str) -> None:
        if f not in bad:
            bad.add(f)
            if f in UNITS:  # tried again without the unit
                broken[frozenset(UNITS[f][0])] = "link unit: " + reason
                if f in DETAIL:
                    DETAIL.update({g: ("link unit: " + reason, DETAIL[f][1]) for g in UNITS[f][0]})
            else:
                why[reason] += 1
                LEFT_OUT[f] = reason

    refs = reloc_targets()
    foreign = [(a, b, f) for mod in BSS_IN_AUTOLOAD_3 for f, m in entries.get(mod, ())
               for n, (a, b) in m.items() if n == ".bss"]
    if foreign:
        entries.setdefault("autoload_3", [])
    for mod, es in entries.items():
        bounds: set[int] = set()
        names: dict[int, str] = {}
        targets = []
        ends = []  # where each ROM section of the module ends
        for at in dict.fromkeys((mod, home(mod, ".bss"))):
            bounds |= {x for _, a, b in module_sections(at) for x in (a, b)}
            ends += [b for _, _, b in module_sections(at)]
            for line in (C.config_dir(at) / "symbols.txt").read_text().splitlines():
                m = SYMBOL.match(line)
                if m:
                    a = int(m.group(3), 16)
                    names.setdefault(a, m.group(1))
                    if m.group(2) in ("data", "bss"):
                        bounds.add(a)
            targets += refs[at]
        targets.sort()
        keys = [t for t, _ in targets]
        img, base = C.module_image(mod), mods[mod]["base"]
        for f, merged in es:
            _, end = merged.get(".text") or merged[".init"]  # an initialiser sits in .init
            if end % 4 == 2 and img[end - base:end - base + 2] == b"\xc0\x46":
                drop(f, "Thumb nop after the code: shares an object with what follows")
                continue
            spans = list(merged.values())
            for name, (x, y) in merged.items():
                if name in (".text", ".init"):
                    continue
                # past the end, up to the next symbol or the end of the ROM section (padding to
                # the module's alignment) is nothing
                after = min([a for a in bounds if a >= y] + [e for e in ends if e >= y])
                if x not in bounds or (y not in bounds and (y + 3) & ~3 not in bounds and after not in ends):
                    DETAIL[f] = ("data size differs from the ROM's symbols", f"{name} {x:#x}-{y:#x}")
                    drop(f, DETAIL[f][0])
                    break
                if y not in bounds and (y + 3) & ~3 not in bounds:
                    merged[name] = (x, after)  # ds-decomp takes the ROM's last symbol to the end
                outside = [t for t, frm in targets[bisect.bisect_left(keys, x):bisect.bisect_left(keys, y)]
                           if not any(p <= frm < q for p, q in spans)]
                # a word elsewhere in the ROM points here: the linker resolves it by the
                # ROM's name, which the object then defines too (its own name may differ, or
                # be local: a static that a constructor in another source builds)
                miss = [t for t in outside if exported[f].get(t) != names.get(t)]
                if any(t not in names for t in miss):
                    DETAIL[f] = ("data used from outside at an address with no symbol",
                                 " ".join(f"{t:#x}" for t in miss if t not in names))
                    drop(f, DETAIL[f][0])
                    break
                EXPORTS.setdefault(f, {}).update({t: names[t] for t in miss})
        # an object's tail padding up to the next object belongs to it
        es[:] = [(f, {n: (a, (b + 3) & ~3) for n, (a, b) in m.items()}) for f, m in es]
        claims = sorted([(a, b, f) for f, m in es if f not in bad for n, (a, b) in m.items()
                         if home(mod, n) == mod]
                        + [(a, (b + 3) & ~3, f) for a, b, f in foreign if mod == "autoload_3" and f not in bad])
        for (_, a1, f0), (b0, _, f1) in zip(claims, claims[1:]):
            if b0 < a1:
                drop(f0, "overlapping claims")
                drop(f1, "overlapping claims")
        for sec in ORDER[1:]:
            seq = sorted(((m.get(".text") or m[".init"])[0], f, m[sec][0]) for f, m in es if sec in m and f not in bad)
            keep = longest_increasing([(f, a) for _, f, a in seq])
            for _, f, _ in seq:
                if f not in keep:
                    drop(f, "link order")
    return {m: [e for e in es if e[0] not in bad] for m, es in entries.items()}, why, broken


# ------------------------------------------------------------------------------ link

def write_config(entries: dict[str, list]) -> None:
    """A copy of config/ with build paths under build/adm-kr/link and the TUs appended."""
    if LINK.exists():
        shutil.rmtree(LINK)
    LINK.mkdir(parents=True)
    shutil.copytree(C.CONFIG, CFG)
    up = "../" * len(CFG.relative_to(C.ROOT).parts)
    text = (CFG / "config.yaml").read_text()
    text = re.sub(r"\.\./\.\./\.\./", up, text)
    text = re.sub(r"^build_path: .*$", f"build_path: {up}build/adm-kr/obj", text, flags=re.M)
    text = re.sub(r"^delinks_path: .*$", f"delinks_path: {up}build/adm-kr/link/delinks", text, flags=re.M)
    # mwldarm writes the modules to <build_path>/build
    text = text.replace(f"{up}build/adm-kr/build/", f"{up}build/adm-kr/obj/build/")
    (CFG / "config.yaml").write_text(text, newline="\n")
    rows = collections.defaultdict(list)  # module -> [(first address, file, {section: range})]
    for mod, es in entries.items():
        for f, merged in es:
            split = collections.defaultdict(dict)
            for name, span in merged.items():
                split[home(mod, name)][name] = span
            for at, secs in split.items():
                rows[at].append((min(a for a, _ in secs.values()), f if at == mod else bss_name(f), secs))
    for mod, es in rows.items():
        lines = []
        for _, f, merged in sorted(es):
            lines += [f"{f}:", "    complete"]
            for name in sorted(merged, key=lambda n: ORDER.index(n) if n in ORDER else 99):
                a, b = merged[name]
                lines.append(f"    {name:<11} start:0x{a:08x} end:0x{b:08x}")
            lines.append("")
        dl = module_dir(CFG, mod) / "delinks.txt"
        dl.write_text(dl.read_text().rstrip("\n") + "\n\n" + "\n".join(lines), newline="\n")


def step(what: str, t0: list[float] = [time.monotonic()]) -> None:
    now = time.monotonic()
    print(f"  {now - t0[0]:6.0f}s  {what}", flush=True)


def run(cmd: list[str], log: str) -> None:
    step(log.removesuffix(".log"))
    # mwldarm checks the same license file as the compiler
    env = dict(os.environ, LM_LICENSE_FILE=str(C.MWCC_ROOT / "license.dat"))
    p = subprocess.run(cmd, cwd=C.ROOT, capture_output=True, text=True, errors="replace", env=env)
    (LINK / log).write_text(p.stdout + p.stderr, newline="\n")
    if p.returncode != 0:
        tail = [line for line in (p.stdout + p.stderr).splitlines()
                if "multiply defined" not in line and "Ignoring the definition" not in line]
        raise SystemExit(f"{cmd[0]} failed (build/adm-kr/link/{log}):\n" + "\n".join(tail[-15:]))


def link(objects: dict[str, bytes]) -> None:
    """`objects`: source -> the object to link for it in place of its compiled one."""
    cfg = str(CFG / "config.yaml")
    if not (C.ROOT / "extract" / "adm-kr" / "config.yaml").exists():
        run([str(DSD), "rom", "extract", "-r", "extract/adm-kr.nds", "-o", "extract/adm-kr"],
            "extract.log")
    run([str(DSD), "delink", "-c", cfg], "delink.log")
    run([str(DSD), "lcf", "-c", cfg], "lcf.log")
    obj = C.BUILD / "obj"
    lcf = obj / "arm9.lcf"
    # the linker script names objects by file name; objects.txt says where each one is
    listed = (obj / "objects.txt").read_text()
    for f, data in objects.items():
        rel = pathlib.Path(f).with_suffix(".o")
        path = LINK / "obj" / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(data)
        old = f'"{C.OBJ_DIR / rel}"'
        if old not in listed:
            raise SystemExit(f"{old} is not in objects.txt")
        listed = listed.replace(old, f'"{path}"')
    (obj / "objects.txt").write_text(listed, newline="\n")
    # absolute.txt: constants NitroSDK's linker script defines (stack sizes, overlay IDs, ...)
    defined = set(re.findall(r"^\s*(\w+)\s*=", lcf.read_text(), re.M))
    consts = [f"    {m.group(1)} = 0x{m.group(3)};"
              for line in (C.CONFIG / "absolute.txt").read_text().splitlines()
              if (m := SYMBOL.match(line)) and m.group(1) not in defined]
    # config/aliases.txt: second names some sources use for a function or object (mostly C++
    # member names of functions defined as C), as absolute symbols at the canonical symbol's
    # address, with the Thumb bit for Thumb code
    where = {}
    for path in C.CONFIG.rglob("symbols.txt"):
        for line in path.read_text().splitlines():
            if m := SYMBOL.match(line):
                where.setdefault(m.group(1), int(m.group(3), 16) | (1 if "thumb" in line else 0))
    for line in (C.CONFIG / "aliases.txt").read_text().splitlines():
        if line.strip() and not line.startswith("#"):
            alias, canon = line.split()
            if canon in where and alias not in defined:
                consts.append(f"    {alias} = 0x{where[canon]:08x};")
    lcf.write_text(lcf.read_text().replace("SECTIONS {", "SECTIONS {\n" + "\n".join(consts), 1),
                   newline="\n")
    out = obj / "build"
    if out.exists():
        shutil.rmtree(out)
    out.mkdir(parents=True)
    ld = C.MWCC_ROOT / "1.2" / "base" / "mwldarm.exe"
    # LD_WRAPPER runs the Windows linker elsewhere (default: MWCC_WRAPPER). wibo is slow here:
    # it scans the directories it opens files in, and the object tree has thousands of files.
    wrapper = shlex.split(os.environ.get("LD_WRAPPER", os.environ.get("MWCC_WRAPPER", "")))
    # -nodead: every gap object is reachable only through the ROM's own tables
    run([*wrapper, str(ld), "-proc", "arm946e", "-nodead", "-nostdlib", "-interworking",
         "-map", "closure,unused", "-m", "Entry", f"@{obj / 'objects.txt'}", str(lcf),
         "-o", str(obj / "arm9.o")], "link.log")
    run([str(DSD), "check", "modules", "-c", cfg, "--fail"], "check.log")


def main() -> None:
    # --why [FILE...]: plan only, and print why each named source (or every one left out) stays
    # out of the link; nothing is linked or written
    only = [pathlib.Path(a).as_posix() for a in sys.argv[2:]] if sys.argv[1:2] == ["--why"] else None
    planner = Planner()
    paths = [p for p in C.all_sources() if C.SRC in p.parents]
    with cf.ThreadPoolExecutor(max(1, (os.cpu_count() or 4) - 2)) as pool:
        plans = [r for r in pool.map(planner.plan, paths) if r]
    step(f"planned {len(plans)} sources")
    entries, why = choose(plans, planner.chk.mods)
    linked = sorted(g for es in entries.values() for f, _ in es for g in UNITS.get(f, ([f],))[0])
    chosen = set(linked)
    in_units = {f for members, *_ in UNITS.values() for f in members}
    if only is not None:
        for f in only or sorted(LEFT_OUT):
            unit = next((m for m, *_ in UNITS.values() if f in m), None)
            state = f"linked in a unit of {len(unit)} sources" if unit else "linked"
            reason = LEFT_OUT.get(f, state if f in chosen else "not a planned source")
            if DETAIL.get(f, ("",))[0] == reason:
                reason += f" ({DETAIL[f][1]})"
            print(f"{f}: {reason}")
        return
    write_config(entries)
    # where each source's own data lands in the ROM, for the runtime's checks (tools/native.py)
    (C.BUILD / "placement.json").write_text(json.dumps(
        {r["file"]: [s for s in r["sections"] if s[0] not in (".text", ".init") and s[3] is not None]
         for r in plans if "sections" in r}) + "\n", newline="\n")
    (LINK / "left-out.txt").write_text("".join(f"{n:6} {k}\n" for k, n in why.most_common()),
                                       newline="\n")
    objects = {}
    by_file = {r["file"]: r for r in plans}
    ranges = {f: (mod, merged) for mod, es in entries.items() for f, merged in es}
    for f, (mod, merged) in ranges.items():
        away = ".bss" in merged and home(mod, ".bss") != mod
        members = UNITS[f][0] if f in UNITS else [f]
        if f in UNITS:
            _, copies, holes = UNITS[f]
            objects[f] = unit_object([by_file[g] for g in members], copies, holes, planner.rename,
                                     EXPORTS.get(f, {}), away)
        elif (data := linked_object(by_file[f], planner.rename, EXPORTS.get(f, {}), away)) is not None:
            objects[f] = data
        if away:
            template = Obj(C.compile_source(C.parse_source(C.ROOT / f))[0])
            objects[bss_name(f)] = bss_object(template, *merged[".bss"],
                                              [g for m in members for g in by_file[m]["globals"]])
    lines = [" ".join(UNITS[f][0]) for f in ranges if f in UNITS]
    # the link units, one per line: their sources in ROM order
    (LINK / "units.txt").write_text("".join(f"{x}\n" for x in sorted(lines)), newline="\n")
    link(objects)
    step("done")
    (C.BUILD / "linked.json").write_text(json.dumps(linked, indent=0) + "\n", newline="\n")
    print(f"{len(linked)} of {len(paths)} sources linked; every module matches the ROM")
    for k, n in why.most_common():
        print(f"  {n:6} left out: {k}")


if __name__ == "__main__":
    main()
