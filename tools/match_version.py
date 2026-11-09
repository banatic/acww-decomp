"""Pair another version's functions and data with the first version's (docs/versions.md,
"Adding a version", step 3), and write that version's symbol tables with the first version's names.

    python tools/match_version.py --version adm-us-r1            # pair and report
    python tools/match_version.py --version adm-us-r1 --write    # ... and write config/adm-us-r1/arm9/

Reads the first version's configuration (config/adm-kr/arm9: symbols, relocations, sections),
both versions' modules (build/<version>/rom, tools/extract.py) and ROMs (extract/<version>.nds:
the entry point, the overlay table). Writes build/<version>/match/: pairs.txt (every function:
both addresses and sizes, class, call check), unsure.txt (the pairs to review by hand) and
report.txt (the counts per module). With --write, config/<version>/arm9/ gets symbols.txt,
relocs.txt, delinks.txt and config.yaml for every module, in the first version's layout: names
and addresses only, nothing of the ROM's contents.

How a function is paired (the class each pair is reported under):

  exact        the first version's instructions, apart from the words relocations fill and the
               calls, at the only place in the module that has them, or, when several do, at
               the place its paired neighbours' offset predicts.
  call         the same, at the place where the calls of exact pairs land on it.
  gap          between two pairs, the first version's unpaired functions are laid out over the
               other version's bytes: each starts where its first bytes agree best near where
               the one before it ended (where a call lands on it, when one does), and runs to
               the next one's start; same size as the first version's.
  gap-resized  the same with another size. A gap placement less than half alike to the first
               version's function (bytes in order, difflib) is not kept.

A pair is call-confirmed when the calls it makes and the calls made to it (by same-size pairs,
through the first version's relocations) land where the pairs say, at least one and none
elsewhere; unsure.txt lists the pairs that are neither exact nor confirmed, or that a call
contradicts. Data and .bss symbols are placed by the pool words of same-size pairs: a word that
points at (or into) a first-version symbol gives that symbol's address in the other version, by
the vote of every word that names it.

A function of the other version with no counterpart gets a name made from its own address in a
form no first-version name has: `func_us_020e9a20` (`func_us_ov097_022a29e4` in an overlay), with
the version's region (`us` for adm-us-r1). Only spans between two pairs that sit next to each
other in the first version and that start with a push are named this way; the other unpaired
bytes are counted in report.txt.
"""
from __future__ import annotations

import argparse
import bisect
import collections
import dataclasses
import difflib
import json
import pathlib
import re
import struct
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import versions  # noqa: E402

ROOT = versions.ROOT
SYM = re.compile(r"^(?P<name>\S+) kind:(?P<kind>\w+)(?:\((?P<attrs>[^)]*)\))?(?P<rest>.*?) "
                 r"addr:0x(?P<addr>[0-9a-f]+)(?P<tail>.*)$")
RELOC = re.compile(r"^from:0x(?P<frm>[0-9a-f]+) kind:(?P<kind>\w+) to:0x(?P<to>[0-9a-f]+) module:(?P<mod>\S+)$")
SECTION = re.compile(r"^\s+(?P<name>\.\w+)\s+start:0x(?P<start>[0-9a-f]+) end:0x(?P<end>[0-9a-f]+)(?P<rest>.*)$")
CALLS = {"thumb_call", "thumb_call_arm", "arm_call", "arm_call_thumb", "arm_branch"}
MANY = 64        # more places than this with a function's bytes: its neighbours decide
PUSH_ARM = bytes([0x2D, 0xE9])  # stmdb sp!, {...} (the high halfword)


@dataclasses.dataclass
class Sym:
    name: str
    kind: str          # function | data | bss | label
    addr: int
    size: int          # functions only
    thumb: bool
    attrs: str         # the text in the parentheses, as written
    rest: str          # text between them and addr (" ambiguous", " local")
    tail: str


@dataclasses.dataclass
class Reloc:
    frm: int
    kind: str
    to: int
    mod: str


@dataclasses.dataclass
class Pair:
    kr: Sym            # the first version's function
    addr: int
    size: int
    cls: str
    note: str = ""


def config_dir(root: pathlib.Path, module: str) -> pathlib.Path:
    if module == "main":
        return root
    if module.startswith("ov"):
        return root / "overlays" / module
    return root / module


def read_symbols(path: pathlib.Path) -> list[Sym]:
    out = []
    if not path.exists():
        return out
    for line in path.read_text(encoding="utf-8").splitlines():
        m = SYM.match(line.strip())
        if not m:
            continue
        attrs = m["attrs"] or ""
        size = re.search(r"size=0x([0-9a-f]+)", attrs)
        out.append(Sym(m["name"], m["kind"], int(m["addr"], 16), int(size[1], 16) if size else 0,
                       attrs.startswith("thumb"), attrs, m["rest"], m["tail"]))
    return out


def read_relocs(path: pathlib.Path) -> list[Reloc]:
    out = []
    if path.exists():
        for line in path.read_text(encoding="utf-8").splitlines():
            if m := RELOC.match(line.strip()):
                out.append(Reloc(int(m["frm"], 16), m["kind"], int(m["to"], 16), m["mod"]))
    return out


def target_modules(text: str) -> list[str]:
    """The modules a relocation's `module:` names."""
    if text in ("main", "itcm", "dtcm"):
        return [text]
    m = re.match(r"(\w+)\(([\d,]+)\)", text)
    if not m:
        return []
    nums = [int(n) for n in m[2].split(",")]
    if m[1] in ("overlay", "overlays"):
        return [f"ov{n:03d}" for n in nums]
    if m[1] == "autoload":
        return [f"autoload_{n}" for n in nums]
    return []


def sext(v: int, bits: int) -> int:
    return v - (1 << bits) if v & (1 << (bits - 1)) else v


def call_target(kind: str, word: bytes, at: int) -> int | None:
    """Where the call at `at` (its four bytes `word`) lands, Thumb bit clear; None when the word
    is no call."""
    if len(word) != 4:
        return None
    if kind.startswith("thumb_call"):
        lo, hi = struct.unpack("<HH", word)
        if lo & 0xF800 != 0xF000 or hi & 0xE800 != 0xE800:
            return None
        off = sext(((lo & 0x7FF) << 12) | ((hi & 0x7FF) << 1), 23)
        if hi & 0xF800 == 0xE800:      # BLX: from the word-aligned PC
            return (((at + 4) & ~3) + off) & ~3
        return (at + 4 + off) & ~1
    w, = struct.unpack("<I", word)
    if (w >> 25) & 7 != 5:
        return None
    off = sext(w & 0xFFFFFF, 24) << 2
    if w >> 28 == 0xF:
        off |= ((w >> 24) & 1) << 1
    return (at + 8 + off) & ~1


def masked(data: bytes, offsets: list[int]) -> bytes:
    b = bytearray(data)
    for o in offsets:
        b[o:o + 4] = bytes(len(b[o:o + 4]))
    return bytes(b)


def longest_run(n: int, offsets: list[int]) -> tuple[int, int]:
    """(start, length) of the longest span of [0, n) outside the four bytes at each offset."""
    best, at = (0, 0), 0
    for o in sorted(offsets) + [n]:
        if o - at > best[1]:
            best = (at, o - at)
        at = max(at, o + 4)
    return best


def lis(rows: list[tuple[Sym, int]]) -> list[tuple[Sym, int]]:
    """The longest subsequence (in the first version's order) whose other addresses increase."""
    tails: list[int] = []
    idx: list[int] = []
    back = [-1] * len(rows)
    for i, (_, addr) in enumerate(rows):
        j = bisect.bisect_left(tails, addr)
        if j == len(tails):
            tails.append(addr)
            idx.append(i)
        else:
            tails[j] = addr
            idx[j] = i
        back[i] = idx[j - 1] if j else -1
    out, k = [], idx[-1] if idx else -1
    while k >= 0:
        out.append(rows[k])
        k = back[k]
    return out[::-1]


class Module:
    def __init__(self, name: str, base: int, image: bytes, bss: int, syms: list[Sym], relocs: list[Reloc],
                 sections: list[tuple[str, int, int, str]]):
        self.name, self.base, self.image, self.bss = name, base, image, bss
        self.syms, self.relocs, self.sections = syms, relocs, sections
        self.functions = sorted((s for s in syms if s.kind == "function" and s.size), key=lambda s: s.addr)
        self.reloc_at = {r.frm: r for r in relocs}
        self.reloc_sites = sorted(self.reloc_at)
        self.starts = sorted({s.addr for s in syms})

    def bytes_at(self, addr: int, n: int) -> bytes:
        off = addr - self.base
        return self.image[off:off + n] if 0 <= off and off + n <= len(self.image) else b""

    def relocs_in(self, addr: int, size: int) -> list[Reloc]:
        i = bisect.bisect_left(self.reloc_sites, addr)
        j = bisect.bisect_left(self.reloc_sites, addr + size)
        return [self.reloc_at[a] for a in self.reloc_sites[i:j]]


def load(version: str, config: pathlib.Path | None) -> dict[str, Module]:
    rom = ROOT / "build" / version / "rom"
    if not (rom / "modules.json").exists():
        raise SystemExit(f"no {versions.rel(rom)}/modules.json: python tools/setup.py ROM --version {version}")
    table = json.loads((rom / "modules.json").read_text())
    out = {}
    for name, info in table.items():
        syms, relocs, sections = [], [], []
        if config is not None:
            d = config_dir(config, name)
            syms = read_symbols(d / "symbols.txt")
            relocs = read_relocs(d / "relocs.txt")
            if (d / "delinks.txt").exists():
                for line in (d / "delinks.txt").read_text().splitlines():
                    m = SECTION.match(line)
                    if not m:
                        break
                    sections.append((m["name"], int(m["start"], 16), int(m["end"], 16), m["rest"]))
        out[name] = Module(name, info["base"], (rom / f"{name}.bin").read_bytes(), info["bss"], syms, relocs,
                           sections)
    return out


def rom_header(version: str) -> bytes:
    with open(ROOT / "extract" / f"{version}.nds", "rb") as f:
        return f.read(0x200)


def overlay_ctors(version: str) -> dict[str, tuple[int, int]]:
    """Each overlay's static initializer table (start, end) from the ROM's overlay table."""
    with open(ROOT / "extract" / f"{version}.nds", "rb") as f:
        head = f.read(0x200)
        off, size = struct.unpack_from("<II", head, 0x50)
        f.seek(off)
        table = f.read(size)
    out = {}
    for k in range(size // 32):
        oid, _ram, _size, _bss, s0, s1 = struct.unpack_from("<6I", table, 32 * k)
        out[f"ov{oid:03d}"] = (s0, s1)
    return out


class Matcher:
    """One module: the first version's functions (a) placed in the other version's image (b)."""

    def __init__(self, a: Module, b: Module):
        self.a, self.b = a, b
        self.pairs: dict[int, Pair] = {}          # first version's address -> pair
        self.cands: dict[int, list[int]] = {}
        self.hints: dict[int, int] = {}           # where calls land on an unpaired function
        self.rejected = 0                          # gap placements too unlike to keep
        self._masks: dict[int, list[int]] = {}

    # ---------------------------------------------------------------- bytes
    def mask_offsets(self, f: Sym) -> list[int]:
        """The words relocations fill, and every other call: the first version's relocations
        leave out calls whose target the link does not move."""
        if f.addr in self._masks:
            return self._masks[f.addr]
        offs = {r.frm - f.addr for r in self.a.relocs_in(f.addr, f.size)}
        code = self.a.bytes_at(f.addr, f.size)
        if f.thumb:
            for o in range(0, len(code) - 3, 2):
                lo, hi = struct.unpack_from("<HH", code, o)
                if lo & 0xF800 == 0xF000 and hi & 0xE800 == 0xE800:
                    offs.add(o)
        else:
            for o in range(0, len(code) - 3, 4):
                if code[o + 3] & 0x0F == 0x0B or code[o + 3] in (0xFA, 0xFB):
                    offs.add(o)
        self._masks[f.addr] = sorted(offs)
        return self._masks[f.addr]

    def want(self, f: Sym) -> bytes:
        return masked(self.a.bytes_at(f.addr, f.size), self.mask_offsets(f))

    def same_at(self, f: Sym, addr: int) -> bool:
        got = self.b.bytes_at(addr, f.size)
        return len(got) == f.size and masked(got, self.mask_offsets(f)) == self.want(f)

    def similar(self, f: Sym, addr: int, size: int, prefix: bool = False) -> float:
        """The share of equal bytes in place (calls and relocated words left out) between f and
        `size` bytes at addr; with prefix, of f's first `size` bytes only."""
        offs = self.mask_offsets(f)
        a = self.want(f)
        if prefix:
            a = a[:size]
        b = self.b.bytes_at(addr, size)
        if not b:
            return 0.0
        b = masked(b, [o for o in offs if o + 4 <= len(b)])
        n = min(len(a), len(b))
        return sum(1 for i in range(n) if a[i] == b[i]) / max(len(a), len(b))

    # ---------------------------------------------------------------- exact
    def search(self) -> None:
        img = self.b.image
        for f in self.a.functions:
            want = self.want(f)
            if len(want) != f.size:
                continue
            start, length = longest_run(f.size, self.mask_offsets(f))
            found: list[int] = []
            if length >= 4:
                needle = want[start:start + length]
                at, hits = img.find(needle), 0
                while at >= 0 and hits <= MANY:
                    hits += 1
                    addr = self.b.base + at - start
                    if addr % (2 if f.thumb else 4) == 0 and self.same_at(f, addr):
                        found.append(addr)
                    at = img.find(needle, at + 1)
                if hits > MANY:
                    found = []
            self.cands[f.addr] = found

    def anchor(self) -> None:
        """Functions found at one place only, kept where they agree with the order of the others
        (the longest run of increasing addresses)."""
        uniq = [(f, self.cands[f.addr][0]) for f in self.a.functions if len(self.cands.get(f.addr, ())) == 1]
        for f, addr in lis(uniq):
            self.pairs[f.addr] = Pair(f, addr, f.size, "exact")

    def fits(self, f: Sym, addr: int, size: int) -> bool:
        """Between the pairs of its neighbours in the first version, overlapping none."""
        keys = sorted(k for k in self.pairs if k != f.addr)
        i = bisect.bisect_left(keys, f.addr)
        lo = self.pairs[keys[i - 1]].addr + self.pairs[keys[i - 1]].size if i else self.b.base
        hi = self.pairs[keys[i]].addr if i < len(keys) else self.b.base + len(self.b.image)
        return lo <= addr and addr + size <= hi

    def fill_by_neighbours(self) -> None:
        """Unpaired functions with their bytes where a neighbour's offset puts them, or at one of
        their places between the neighbours' pairs."""
        changed = True
        while changed:
            changed = False
            keys = sorted(self.pairs)
            for f in self.a.functions:
                if f.addr in self.pairs:
                    continue
                i = bisect.bisect_left(keys, f.addr)
                prev = self.pairs[keys[i - 1]] if i else None
                nxt = self.pairs[keys[i]] if i < len(keys) else None
                lo = prev.addr + prev.size if prev else self.b.base
                hi = nxt.addr if nxt else self.b.base + len(self.b.image)
                tries = [f.addr + (p.addr - p.kr.addr) for p in (prev, nxt) if p is not None]
                tries += [c for c in self.cands.get(f.addr, ()) if lo <= c and c + f.size <= hi]
                for addr in dict.fromkeys(tries):
                    if lo <= addr and addr + f.size <= hi and self.same_at(f, addr):
                        self.pairs[f.addr] = Pair(f, addr, f.size, "exact")
                        keys = sorted(self.pairs)
                        changed = True
                        break

    # ---------------------------------------------------------------- calls
    def callees(self, exact_only: bool = False) -> dict[tuple[str, int], collections.Counter]:
        """(module, first version's callee address) -> votes for the other version's address,
        from the calls of same-size pairs (with exact_only, of pairs with the same bytes)."""
        votes: dict[tuple[str, int], collections.Counter] = collections.defaultdict(collections.Counter)
        for p in self.pairs.values():
            if p.size != p.kr.size or exact_only and p.cls not in ("exact", "call"):
                continue
            for r in self.a.relocs_in(p.kr.addr, p.kr.size):
                if r.kind not in CALLS:
                    continue
                at = p.addr + (r.frm - p.kr.addr)
                got = call_target(r.kind, self.b.bytes_at(at, 4), at)
                if got is None:
                    continue
                for mod in target_modules(r.mod):
                    votes[(mod, r.to & ~1)][got] += 1
        return votes

    # ---------------------------------------------------------------- gaps
    def gaps(self) -> None:
        """Unpaired first-version functions between two pairs, laid out over the other version's
        bytes between the same two pairs."""
        keys = sorted(self.pairs)
        bounds = [None, *[self.pairs[k] for k in keys], None]
        fns = self.a.functions
        for prev, nxt in zip(bounds, bounds[1:]):
            lo_a = prev.kr.addr + prev.kr.size if prev else self.a.base
            hi_a = nxt.kr.addr if nxt else (fns[-1].addr + fns[-1].size if fns else self.a.base)
            lo_b = prev.addr + prev.size if prev else self.b.base
            hi_b = nxt.addr if nxt else None
            todo = [f for f in fns if lo_a <= f.addr < hi_a and f.addr not in self.pairs]
            if not todo:
                continue
            if hi_b is None:
                hi_b = lo_b + (hi_a - lo_a)
                if hi_b > self.b.base + len(self.b.image):
                    continue
            self.align(todo, lo_a, hi_a, lo_b, hi_b)

    def align(self, todo: list[Sym], lo_a: int, hi_a: int, lo_b: int, hi_b: int) -> None:
        """Each function's start where its first bytes agree best, near where the one before it
        puts it (or where a call lands on it); it starts with the first version's first
        instruction (its push). Its size runs to the next one's start, less the bytes the first
        version has between them that are not its own."""
        spread = min(max(abs((hi_b - lo_b) - (hi_a - lo_a)) + 32, 64), 512)
        shift = lo_b - lo_a
        placed: list[tuple[Sym, int]] = []
        floor = lo_b
        for f in todo:
            step = 2 if f.thumb else 4
            hint = self.hints.get(f.addr)
            if hint is not None and floor <= hint < hi_b:
                s = hint
            else:
                first = self.a.bytes_at(f.addr, step)
                best = None
                for d in sorted(range(-spread, spread + 1, step), key=abs):
                    s = f.addr + shift + d
                    if s < floor or s >= hi_b or s % step or self.b.bytes_at(s, step) != first:
                        continue
                    score = self.similar(f, s, min(f.size, 48), prefix=True)
                    if best is None or score > best[0]:
                        best = (score, s)
                if best is None:
                    continue
                s = best[1]
            placed.append((f, s))
            shift = s - f.addr
            floor = s + 2
        for i, (f, s) in enumerate(placed):
            e, n = (placed[i + 1][1], placed[i + 1][0].addr) if i + 1 < len(placed) else (hi_b, hi_a)
            size = (e - s) - (n - (f.addr + f.size))
            if size > 0:
                self.add_gap(f, s, size, "gap" if size == f.size else "gap-resized")

    def add_gap(self, f: Sym, addr: int, size: int, cls: str) -> None:
        if size <= 0 or addr % (2 if f.thumb else 4) or not self.fits(f, addr, size):
            return
        share = self.similar(f, addr, size)
        if share < 0.9:
            # bytes shifted by an insertion compare badly in place: the share the two have in
            # common, in order, decides
            b = self.b.bytes_at(addr, size)
            share = max(share, difflib.SequenceMatcher(None, self.want(f), b, autojunk=False).ratio())
            if share < 0.5:
                self.rejected += 1
                return
        self.pairs[f.addr] = Pair(f, addr, size, cls, f"{share:.0%} alike" if share < 0.9 else "")


def unpaired_name(region: str, module: str, addr: int) -> str:
    return f"func_{region}_{module}_{addr:08x}" if module.startswith("ov") else f"func_{region}_{addr:08x}"


def module_order(name: str) -> tuple[int, str]:
    order = ["main", "itcm", "dtcm", "autoload_2", "autoload_3"]
    return (order.index(name), name) if name in order else (len(order), name)


def pair_functions(matchers: dict[str, Matcher], base: str, target: str) -> None:
    for m in matchers.values():
        m.search()
        m.anchor()
    # calls of pairs place unpaired callees, in any module; the first round only from the
    # functions found at one place, which runs of look-alike small functions need
    for round_ in range(5):
        votes: dict[tuple[str, int], collections.Counter] = collections.defaultdict(collections.Counter)
        for m in matchers.values():
            for k, c in m.callees().items():
                votes[k].update(c)
        added = 0
        for (mod, addr), c in votes.items():
            m = matchers.get(mod)
            if m is None or addr in m.pairs or len(c) != 1:
                continue
            f = next((s for s in m.a.functions if s.addr == addr), None)
            if f is None:
                continue
            got = next(iter(c))
            if m.same_at(f, got) and m.fits(f, got, f.size):
                m.pairs[addr] = Pair(f, got, f.size, "call")
                added += 1
            else:
                m.hints[addr] = got
        if not added and round_ > 0:
            break
        for m in matchers.values():
            m.fill_by_neighbours()
    # the entry point: the header names it in both versions
    ma = matchers.get("main")
    if ma is not None:
        entry_a, entry_b = (struct.unpack_from("<I", rom_header(v), 0x24)[0] for v in (base, target))
        f = next((s for s in ma.a.functions if s.addr == entry_a), None)
        if f is not None and f.addr not in ma.pairs and ma.fits(f, entry_b, 4):
            ma.hints[f.addr] = entry_b
    for m in matchers.values():
        m.gaps()
    # a pair that the calls of byte-identical pairs all place elsewhere (a run of look-alike
    # functions laid out one place off): moved there when its bytes are there
    for _ in range(3):
        votes = collections.defaultdict(collections.Counter)
        for m in matchers.values():
            for k, c in m.callees(exact_only=True).items():
                votes[k].update(c)
        moved = 0
        for (mod, addr), c in votes.items():
            m = matchers.get(mod)
            if m is None or addr not in m.pairs or len(c) != 1:
                continue
            got = next(iter(c))
            p = m.pairs[addr]
            if got == p.addr or any(q.addr == got for q in m.pairs.values()) or not m.fits(p.kr, got, p.kr.size):
                continue
            if m.same_at(p.kr, got):
                m.pairs[addr] = Pair(p.kr, got, p.kr.size, "call", f"moved from {p.addr:#010x}")
            elif m.similar(p.kr, got, p.kr.size) >= 0.75:
                m.pairs[addr] = Pair(p.kr, got, p.kr.size, "gap", f"moved from {p.addr:#010x} by calls")
            else:
                continue
            moved += 1
        if not moved:
            break
        for m in matchers.values():
            m.gaps()


def split_at_calls(matchers: dict[str, Matcher]) -> dict[str, list[tuple[int, int, bool]]]:
    """A call of a same-size pair that lands inside a laid-out (gap) pair, not at its start,
    starts a function of this version's own there: the pair ends at the first such place, and
    each piece after it is a new function (module -> [(address, size, thumb)])."""
    targets: dict[str, dict[int, bool]] = collections.defaultdict(dict)
    for m in matchers.values():
        for p in m.pairs.values():
            if p.size != p.kr.size:
                continue
            for r in m.a.relocs_in(p.kr.addr, p.kr.size):
                mods = target_modules(r.mod)
                if r.kind not in CALLS or len(mods) != 1:
                    continue
                at = p.addr + (r.frm - p.kr.addr)
                got = call_target(r.kind, m.b.bytes_at(at, 4), at)
                if got is not None:
                    targets[mods[0]][got] = r.kind in ("thumb_call", "arm_call_thumb")
    extra: dict[str, list[tuple[int, int, bool]]] = collections.defaultdict(list)
    for mod, m in matchers.items():
        inside = sorted(targets.get(mod, {}))
        for p in m.pairs.values():
            if p.cls not in ("gap", "gap-resized"):
                continue
            i = bisect.bisect_right(inside, p.addr)
            cuts = [x for x in inside[i:bisect.bisect_left(inside, p.addr + p.size)]]
            if not cuts:
                continue
            end = p.addr + p.size
            p.size, p.cls = cuts[0] - p.addr, "gap-resized"
            p.note = (p.note + " " if p.note else "") + f"cut where a call lands at {cuts[0]:#010x}"
            for a, b in zip(cuts, [*cuts[1:], end]):
                extra[mod].append((a, b - a, targets[mod][a]))
    return extra


def check_calls(matchers: dict[str, Matcher]) -> tuple[set, dict]:
    """(confirmed, disagreeing call counts): the calls a same-size pair makes, and the calls of
    same-size pairs to it, land where the pairs say (at least one, none elsewhere)."""
    pair_at = {(mod, a): p for mod, m in matchers.items() for a, p in m.pairs.items()}
    good: collections.Counter = collections.Counter()
    bad: collections.Counter = collections.Counter()
    for mod, m in matchers.items():
        for a, p in m.pairs.items():
            if p.size != p.kr.size:
                continue
            for r in m.a.relocs_in(p.kr.addr, p.kr.size):
                if r.kind not in CALLS:
                    continue
                at = p.addr + (r.frm - p.kr.addr)
                got = call_target(r.kind, m.b.bytes_at(at, 4), at)
                tgt = [(t, r.to & ~1) for t in target_modules(r.mod) if (t, r.to & ~1) in pair_at]
                if not tgt or got is None:
                    continue
                hit = [k for k in tgt if pair_at[k].addr == got]
                if hit:
                    good[(mod, a)] += 1
                    good[hit[0]] += 1
                else:
                    bad[(mod, a)] += 1
                    for k in tgt:
                        bad[k] += 1
    return {k for k in good if not bad[k]}, dict(bad)


def pair_data(matchers: dict[str, Matcher]) -> tuple[dict, int]:
    """(module, first version's address) -> (symbol, other address, how), and how many were left
    out because their address collides with a better-voted symbol or a function."""
    votes: dict[tuple[str, int], collections.Counter] = collections.defaultdict(collections.Counter)
    starts = {mod: m.a.starts for mod, m in matchers.items()}
    by_addr = {mod: {s.addr: s for s in m.a.syms} for mod, m in matchers.items()}

    def containing(mod: str, addr: int) -> Sym | None:
        st = starts.get(mod)
        if not st:
            return None
        i = bisect.bisect_right(st, addr) - 1
        return by_addr[mod][st[i]] if i >= 0 else None

    for m in matchers.values():
        for p in m.pairs.values():
            if p.size != p.kr.size:
                continue
            for r in m.a.relocs_in(p.kr.addr, p.kr.size):
                if r.kind != "load":
                    continue
                word = m.b.bytes_at(p.addr + (r.frm - p.kr.addr), 4)
                if len(word) != 4:
                    continue
                w, = struct.unpack("<I", word)
                for t in target_modules(r.mod):
                    s = containing(t, r.to)
                    if s is not None and s.kind != "function":
                        votes[(t, s.addr)][w - (r.to - s.addr)] += 1
    pairs: dict[tuple[str, int], tuple[Sym, int, str]] = {}
    weight: dict[tuple[str, int], int] = {}
    for (mod, addr), c in votes.items():
        mb = matchers[mod].b
        for w in [w for w in c if not mb.base <= w <= mb.base + len(mb.image) + mb.bss]:
            del c[w]  # not an address in the module: a word that is no pointer in this version
        if not c:
            continue
        (best, n), = c.most_common(1)
        pairs[(mod, addr)] = (by_addr[mod][addr], best, "votes" if len(c) == 1 else f"split {n}/{sum(c.values())}")
        weight[(mod, addr)] = n
    dropped = 0
    for mod, m in matchers.items():
        code = sorted((p.addr, p.addr + p.size) for p in m.pairs.values())
        lows = [lo for lo, _ in code]
        taken: set[int] = set()
        for key in sorted((k for k in pairs if k[0] == mod), key=lambda k: -weight[k]):
            addr = pairs[key][1]
            i = bisect.bisect_right(lows, addr) - 1
            if addr in taken or i >= 0 and addr < code[i][1]:
                dropped += 1
                del pairs[key]
            else:
                taken.add(addr)
    return pairs, dropped


def module_hash(data: bytes) -> int:
    """ds-decomp's hash of a module (config.yaml `hash:`): Rust's FxHasher over the slice, its
    length first."""
    k, mask = 0x517CC1B727220A95, (1 << 64) - 1

    def add(h: int, w: int) -> int:
        return ((((h << 5) | (h >> 59)) & mask ^ w) * k) & mask

    h = add(0, len(data))
    i = 0
    while i + 8 <= len(data):
        h = add(h, struct.unpack_from("<Q", data, i)[0])
        i += 8
    for size, fmt in ((4, "<I"), (2, "<H"), (1, "<B")):  # the tail: at most one of each
        if i + size <= len(data):
            h = add(h, struct.unpack_from(fmt, data, i)[0])
            i += size
    return h


def sym_line(name: str, s: Sym, addr: int, size: int | None = None) -> str:
    attrs = s.attrs
    if size is not None and "size=" in attrs:
        attrs = re.sub(r"size=0x[0-9a-f]+", f"size={size:#x}", attrs)
    paren = f"({attrs})" if attrs else ""
    return f"{name} kind:{s.kind}{paren}{s.rest} addr:{addr:#010x}{s.tail}"


def write_config(matchers: dict[str, Matcher], data_pairs: dict, extra: dict, target: str, base: str,
                 region: str) -> tuple[int, int, int, int]:
    """config/<target>/arm9/: symbols (pairs under the first version's names, new functions
    under func_<region>_...), the relocations of same-size pairs, the sections, config.yaml.
    Returns (functions named, unpaired spans and bytes left unnamed, section bounds estimated)."""
    a_root = ROOT / "config" / base / "arm9"
    b_root = ROOT / "config" / target / "arm9"
    named = left = left_bytes = estimated = 0
    ctors, ctors_a = overlay_ctors(target), overlay_ctors(base)
    tables: dict[str, list[tuple[int, str]]] = {}
    for mod, m in matchers.items():
        d = config_dir(b_root, mod)
        d.mkdir(parents=True, exist_ok=True)
        # sections: a bound where a pair starts or ends moves with it; the module's start, end
        # and .bss come from the module, an overlay's .ctor from the overlay table; any other
        # bound moves with the nearest pair before it (estimated), up to its alignment
        moved = {p.kr.addr: p.addr for p in m.pairs.values()}
        moved.update({a: addr for (dm, a), (_s, addr, _h) in data_pairs.items() if dm == mod})
        moved.update({p.kr.addr + p.kr.size: p.addr + p.size for p in m.pairs.values()})
        moved[m.a.base] = m.b.base
        moved[m.a.base + len(m.a.image)] = m.b.base + len(m.b.image)
        bss_end = m.a.base + len(m.a.image) + m.a.bss
        moved[bss_end] = m.b.base + len(m.b.image) + m.b.bss
        ctor, ctor_a = ctors.get(mod), ctors_a.get(mod)
        if ctor is not None and ctor_a is not None:
            # the table, the end of its entries, and the 32-byte boundary after it (.data's start)
            moved[ctor_a[0]] = ctor[0]
            moved[ctor_a[1] - 4] = ctor[1] - 4
            moved[-(-ctor_a[1] // 32) * 32] = -(-ctor[1] // 32) * 32
        known = sorted(k for k in moved if k != bss_end)
        bounds: list[list] = []
        for name, start, end, rest in m.a.sections:
            def at(x: int) -> int:
                nonlocal estimated
                if x in moved:
                    return moved[x]
                i = bisect.bisect_right(known, x) - 1
                estimated += 1
                return moved[known[i]] + (x - known[i])
            s, e = at(start), at(end)
            align = int(g[1]) if (g := re.search(r"align:(\d+)", rest)) else 1
            if s % align:
                old, s = s, -(-s // align) * align
                if bounds and bounds[-1][2] == old:
                    bounds[-1][2] = s
                e = max(e, s)
            bounds.append([name, s, e, rest])
        (d / "delinks.txt").write_text("".join(f"    {n:<11} start:{s:#010x} end:{e:#010x}{r}\n"
                                               for n, s, e, r in bounds), newline="\n")
        # a laid-out function that runs past the end of its code section ends there
        for _n, s, e, rest in bounds:
            if "kind:code" not in rest:
                continue
            for p in m.pairs.values():
                if s <= p.addr < e < p.addr + p.size:
                    p.size, p.cls = e - p.addr, "gap-resized"
                    p.note = (p.note + " " if p.note else "") + f"ends with its section at {e:#010x}"
        rows: list[tuple[int, str]] = [(p.addr, sym_line(p.kr.name, p.kr, p.addr, p.size)) for p in m.pairs.values()]
        # labels inside same-size pairs
        fn_pairs = sorted(m.pairs.values(), key=lambda p: p.kr.addr)
        kr_starts = [p.kr.addr for p in fn_pairs]
        for s in m.a.syms:
            if s.kind != "label":
                continue
            i = bisect.bisect_right(kr_starts, s.addr) - 1
            if i >= 0:
                p = fn_pairs[i]
                if p.size == p.kr.size and s.addr < p.kr.addr + p.kr.size:
                    rows.append((p.addr + s.addr - p.kr.addr, sym_line(s.name, s, p.addr + s.addr - p.kr.addr)))
        rows += [(addr, sym_line(s.name, s, addr)) for (dm, _a), (s, addr, _h) in data_pairs.items() if dm == mod]
        # code with no counterpart between two pairs that are neighbours in the first version
        bs = sorted(m.pairs.values(), key=lambda p: p.addr)
        for p, q in zip(bs, bs[1:]):
            lo, hi = p.addr + p.size, q.addr
            gap_a = q.kr.addr - (p.kr.addr + p.kr.size)
            if hi - lo <= max(gap_a, 0) + 3 or not m.b.bytes_at(lo, hi - lo).strip(b"\0"):
                continue  # padding, as the first version has it
            if gap_a > 3 or any(p.kr.addr < f.addr < q.kr.addr for f in m.a.functions):
                left += 1  # the first version has data or unpaired functions there
                left_bytes += hi - lo
                continue
            step = 2 if p.kr.thumb else 4
            while hi - lo >= step and not m.b.bytes_at(lo, step).strip(b"\0"):
                lo += step
            head = m.b.bytes_at(lo, step)
            if not (p.kr.thumb and head[1] in (0xB4, 0xB5) or not p.kr.thumb and head[2:] == PUSH_ARM):
                left += 1  # does not start as a function does (a push)
                left_bytes += hi - lo
                continue
            isa = "thumb" if p.kr.thumb else "arm"
            fake = Sym("", "function", lo, hi - lo, p.kr.thumb, f"{isa},size={hi - lo:#x}", "", "")
            rows.append((lo, sym_line(unpaired_name(region, mod, lo), fake, lo)))
            named += 1
        for addr, size, thumb in extra.get(mod, ()):
            isa = "thumb" if thumb else "arm"
            fake = Sym("", "function", addr, size, thumb, f"{isa},size={size:#x}", "", "")
            rows.append((addr, sym_line(unpaired_name(region, mod, addr), fake, addr)))
            named += 1
        rows.sort()
        tables[mod] = rows
        (d / "symbols.txt").write_text("".join(f"{line}\n" for _, line in rows), newline="\n")
    # relocations: the first version's, inside same-size pairs, with this version's targets; a
    # target that is not a symbol of this version's table (code or data that did not pair) is
    # left to its address (module:none), as ds-decomp needs a symbol at every relocated target
    starts_b = {mod: {addr for addr, _ in rows} for mod, rows in tables.items()}
    kr_code = {mod: ([(f.addr, f.addr + f.size) for f in m.a.functions], [f.addr for f in m.a.functions])
               for mod, m in matchers.items()}

    def covered(ranges: tuple, addr: int) -> bool:
        spans, lows = ranges
        i = bisect.bisect_right(lows, addr) - 1
        return i >= 0 and addr < spans[i][1]

    for mod, m in matchers.items():
        d = config_dir(b_root, mod)
        rel = []
        for p in m.pairs.values():
            if p.size != p.kr.size:
                continue
            for r in m.a.relocs_in(p.kr.addr, p.kr.size):
                at = p.addr + (r.frm - p.kr.addr)
                word = m.b.bytes_at(at, 4)
                if r.kind == "load":
                    to, = struct.unpack("<I", word)
                else:
                    to = call_target(r.kind, word, at)
                    if to is None:
                        continue
                    to |= r.to & 1
                mods = [x for x in target_modules(r.mod) if x in matchers]
                if r.kind == "load" and mods and not any(
                        matchers[x].b.base <= to <= matchers[x].b.base + len(matchers[x].b.image) + matchers[x].b.bss
                        for x in mods):
                    continue  # the word is no pointer into the module here (the pair's code differs)
                where = r.mod
                if mods:
                    code = [x for x in mods if r.kind != "load" or covered(kr_code[x], r.to & ~1)]
                    look = to & ~1 if code else to
                    have = [x for x in (code or mods) if look in starts_b[x]]
                    if not have:
                        where = "none"  # code or data that did not pair, or a word the votes overruled
                    elif r.mod.startswith("overlay"):
                        nums = [str(int(x[2:])) for x in have]  # the overlays that have it here
                        where = f"overlay({nums[0]})" if len(nums) == 1 else f"overlays({','.join(nums)})"
                rel.append((at, f"from:{at:#010x} kind:{r.kind} to:{to:#010x} module:{where}"))
        rel.sort()
        (d / "relocs.txt").write_text("".join(f"{line}\n" for _, line in rel), newline="\n")

    text = (a_root / "config.yaml").read_text()
    text = text.replace(f"/{base}/", f"/{target}/").replace(f"/{base}\n", f"/{target}\n")
    # each module's hash, as ds-decomp checks a built module against it
    out_lines, name = [], None
    for line in text.split("\n"):
        if g := re.match(r"^\s*-?\s*name: (\S+)$", line):
            name = g[1]
        if (g := re.match(r"^(\s*hash: ).*$", line)) and name in matchers:
            h = f"{module_hash(matchers[name].b.image):016x}"
            line = g[1] + (f'"{h}"' if h.isdigit() else h)
        out_lines.append(line)
    text = "\n".join(out_lines)
    (b_root / "config.yaml").write_text(text, newline="\n")
    # aliases are names for names, the same in every version; the linker script's constants
    # (absolute.txt) are the version's own and are not known here
    (b_root / "aliases.txt").write_text((a_root / "aliases.txt").read_text(), newline="\n")
    if not (b_root / "absolute.txt").exists():
        (b_root / "absolute.txt").write_text("", newline="\n")
    return named, left, left_bytes, estimated


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--from", dest="base", default=versions.DEFAULT, help="the version whose names are taken")
    ap.add_argument("--write", action="store_true", help="write config/<version>/arm9/")
    ap.add_argument("--region", help="the region in unpaired names (default: from the version's name)")
    args = ap.parse_args()
    target = versions.NAME
    if target == args.base:
        raise SystemExit(f"--version names the version to pair with {args.base}, not {args.base} itself")
    region = args.region or target.split("-")[1]
    A, B = load(args.base, ROOT / "config" / args.base / "arm9"), load(target, None)
    out = ROOT / "build" / target / "match"
    out.mkdir(parents=True, exist_ok=True)

    matchers = {m: Matcher(A[m], B[m]) for m in A if m in B}
    pair_functions(matchers, args.base, target)
    extra = split_at_calls(matchers)
    confirmed, disagree = check_calls(matchers)
    data_pairs, dropped = pair_data(matchers)

    written = write_config(matchers, data_pairs, extra, target, args.base, region) if args.write else None

    lines, unsure = [], []
    total: collections.Counter = collections.Counter()
    per_module = []
    for mod in sorted(matchers, key=module_order):
        m = matchers[mod]
        cls = collections.Counter(p.cls for p in m.pairs.values())
        nd = sum(1 for s in m.a.syms if s.kind in ("data", "bss"))
        dp = sum(1 for (mm, _a) in data_pairs if mm == mod)
        conf = sum(1 for a in m.pairs if (mod, a) in confirmed)
        total.update(cls)
        total.update({"functions": len(m.a.functions), "confirmed": conf, "data": nd, "data paired": dp,
                      "rejected": m.rejected})
        per_module.append((mod, len(m.a.functions), len(m.pairs), cls, conf, nd, dp, m.a.image == m.b.image))
        for a in sorted(m.pairs):
            p = m.pairs[a]
            flag = "confirmed" if (mod, a) in confirmed else (
                f"{disagree[(mod, a)]} calls disagree" if (mod, a) in disagree else "")
            line = (f"{mod} {p.kr.name} {p.kr.addr:#010x} {p.kr.size:#x} -> {p.addr:#010x} {p.size:#x} "
                    f"{p.cls} {flag} {p.note}").rstrip()
            lines.append(line)
            if (mod, a) in disagree or p.cls not in ("exact", "call") and ((mod, a) not in confirmed or p.note):
                unsure.append(line)
        lines += [f"{mod} {f.name} {f.addr:#010x} {f.size:#x} -> none" for f in m.a.functions if f.addr not in m.pairs]
    (out / "pairs.txt").write_text("\n".join(lines) + "\n", newline="\n")
    (out / "unsure.txt").write_text("\n".join(unsure) + "\n", newline="\n")
    paired = sum(len(m.pairs) for m in matchers.values())
    rep = [f"{target} paired with {args.base}: {paired} of {total['functions']} functions "
           f"({', '.join(f'{k} {total[k]}' for k in ('exact', 'call', 'gap', 'gap-resized'))}; "
           f"{total['rejected']} gap placements too unlike to keep), {total['confirmed']} call-confirmed, "
           f"{len(unsure)} to review; data/.bss {total['data paired']} of {total['data']} "
           f"({dropped} more left out: their votes collide with another symbol)",
           "module     functions  paired  exact call   gap resized  confirmed   data paired/total  same image"]
    for mod, nfun, npair, cls, conf, nd, dp, same in per_module:
        rep.append(f"{mod:<10} {nfun:9} {npair:7} {cls['exact']:6} {cls['call']:4} {cls['gap']:5} "
                   f"{cls['gap-resized']:7} {conf:10} {dp:7}/{nd:<7}     {'yes' if same else ''}".rstrip())
    if written is not None:
        named, left, left_bytes, estimated = written
        rep.append(f"written: config/{target}/arm9/; functions with no counterpart named func_{region}_...: {named}; "
                   f"unpaired spans left unnamed: {left} ({left_bytes:#x} bytes); section bounds estimated: {estimated}")
    (out / "report.txt").write_text("\n".join(rep) + "\n", newline="\n")
    print(rep[0])
    print(f"  per module: {versions.rel(out / 'report.txt')}; pairs: {versions.rel(out / 'pairs.txt')}; "
          f"to review: {versions.rel(out / 'unsure.txt')}")
    if args.write:
        print("  " + rep[-1])
    return 0


if __name__ == "__main__":
    sys.exit(main())
