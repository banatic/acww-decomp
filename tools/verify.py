"""Compile every source and check it against the ROM.

    python tools/verify.py                 # everything; writes build/adm-kr/verify.json
    python tools/verify.py libs/NitroDWC   # a directory or individual files

BYTES  the function's code equals the ROM's, with linker-filled fields masked.
LINK   every relocation, resolved through config/, gives the ROM's call target or pointer,
       and the file's own literals and tables equal the ROM's data.

Statuses: ok | link (BYTES pass, LINK fails) | bytes (BYTES fail) | error.
"""

from __future__ import annotations

import argparse
import collections
import concurrent.futures as cf
import json
import os
import pathlib
import re
import struct
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import common as C  # noqa: E402

# R_ARM_* -> mask keeping the opcode bits and clearing the field the linker writes.
# THM_CALL also clears bit 12 of the second halfword: the compiler always emits BL and the
# linker turns it into BLX when the callee is ARM.
MASKS = {
    10: b"\x00\xf8\x00\xe8",   # THM_CALL
    30: b"\x00\xf8\x00\xe8",   # THM_JUMP24
    1:  b"\x00\x00\x00\xff",   # PC24
    28: b"\x00\x00\x00\xff",   # CALL
    29: b"\x00\x00\x00\xff",   # JUMP24
    2:  b"\x00\x00\x00\x00",   # ABS32
}
ARM_CALLS = {1, 28, 29}
THUMB_CALLS = {10, 30}

RELOC_LINE = re.compile(r"^from:0x([0-9a-f]+) kind:(\w+) to:0x([0-9a-f]+)")


def sext(v: int, bits: int) -> int:
    return v - (1 << bits) if v & (1 << (bits - 1)) else v


def thumb_target(lo16: int, hi16: int, p: int) -> int:
    off = sext(((lo16 & 0x7FF) << 12) | ((hi16 & 0x7FF) << 1), 23)
    if (hi16 & 0xF800) == 0xE800:          # BLX: relative to the word-aligned PC
        return ((p + 4) & ~3) + off
    return p + 4 + off


def arm_target(word: int, p: int) -> int:
    off = sext(word & 0xFFFFFF, 24) << 2
    if word >> 28 == 0xF:                  # BLX(imm): the H bit adds a halfword
        off |= ((word >> 24) & 1) << 1
    return p + 8 + off


def rom_load_relocs(module: str) -> set[int]:
    path = C.config_dir(module) / "relocs.txt"
    out = set()
    if path.exists():
        for line in path.read_text(encoding="utf-8").splitlines():
            m = RELOC_LINE.match(line)
            if m and m.group(2) == "load":
                out.add(int(m.group(1), 16))
    return out


RELOC_MODULE = re.compile(r" module:(\w+)(?:\(([\d,]+)\))?")


def rom_reloc_modules(module: str) -> dict[int, list[str]]:
    """ROM relocation site -> the module(s) relocs.txt says its target lives in. Overlays
    share addresses, so this is what tells ov065's symbol from ov067's at one address."""
    path = C.config_dir(module) / "relocs.txt"
    out: dict[int, list[str]] = {}
    if path.exists():
        for line in path.read_text(encoding="utf-8").splitlines():
            m, h = RELOC_LINE.match(line), RELOC_MODULE.search(line)
            if not m or not h:
                continue
            kind, nums = h.group(1), h.group(2)
            if kind in ("overlay", "overlays"):
                out[int(m.group(1), 16)] = [f"ov{int(n):03d}" for n in nums.split(",")]
            elif kind == "autoload":
                out[int(m.group(1), 16)] = [f"autoload_{nums}"] if nums else []
            elif kind != "none":
                out[int(m.group(1), 16)] = [kind]
    return out


class Checker:
    def __init__(self):
        self.mods = C.modules()
        self.syms = C.SymbolTable(self.mods)
        self.images = {m: C.module_image(m) for m in self.mods}
        self.loads = {m: rom_load_relocs(m) for m in self.mods}
        self.reloc_mods = {m: rom_reloc_modules(m) for m in self.mods}

    def rom(self, module: str, address: int, n: int) -> bytes:
        base = self.mods[module]["base"]
        img = self.images[module]
        off = address - base
        return img[off:off + n] if 0 <= off and off + n <= len(img) else b""

    def check(self, path: pathlib.Path) -> dict:
        res = self._check(path)
        # wibo and the Windows compiler disagree on a handful of switch-heavy functions;
        # Wine agrees with Windows. MWCC_FALLBACK (e.g. "wine") recompiles a BYTES failure
        # with it, so CI judges the code and not the emulator. A real mismatch still fails.
        fallback = os.environ.get("MWCC_FALLBACK")
        if res["status"] == "bytes" and fallback:
            res = self._check(path, wrapper=fallback, force=True)
        return res

    def _check(self, path: pathlib.Path, wrapper: str | None = None,
               force: bool = False) -> dict:
        src = C.parse_source(path)
        rel = path.relative_to(C.ROOT).as_posix()
        if src is None:
            return {"file": rel, "status": "error", "why": "no recognisable header"}
        res = {"file": rel, "module": src.module, "address": f"{src.address:#010x}",
               "size": src.size, "name": src.name}

        sym = self.syms.function(src.module, src.address)
        if sym is None or sym.size != src.size:
            return {**res, "status": "error",
                    "why": "header does not match a function in the symbol table"}
        if sym.name != src.name:
            res["renamed"] = sym.name
        target = self.rom(src.module, src.address, src.size)

        obj, log = C.compile_source(src, wrapper=wrapper, force=force)
        if obj is None:
            return {**res, "status": "bytes", "why": "does not compile: "
                    + (log.strip().splitlines() or ["?"])[-1][:160]}
        elf = C.Elf(obj)
        fn = elf.function(src.object_symbol)
        if fn is None:
            return {**res, "status": "bytes",
                    "why": f"no function {src.object_symbol} in the object"}
        sec = elf.section_bytes(fn.shndx)
        code = sec[fn.value:fn.value + fn.size]
        if len(code) != len(target):
            return {**res, "status": "bytes", "why": f"size {len(code):#x} != {len(target):#x}"}

        # ---- BYTES
        mask = bytearray(b"\xff" * len(code))
        relocs = [(off - fn.value, typ, s, add) for off, typ, s, add in elf.relocations(fn.shndx)
                  if fn.value <= off < fn.value + fn.size]
        for pos, typ, _, _ in relocs:
            m = MASKS.get(typ)
            if m:
                mask[pos:pos + 4] = m
            if typ in ARM_CALLS and code[pos + 3] == 0xEB and target[pos + 3] in (0xFA, 0xFB):
                mask[pos + 3] = 0
        diff = [i for i in range(len(code)) if (code[i] ^ target[i]) & mask[i]]
        if diff:
            return {**res, "status": "bytes",
                    "why": f"{len(diff)} bytes differ, first at +{diff[0]:#x}"}

        # ---- LINK
        problems, notes = [], collections.Counter()
        for pos, typ, s, addend in relocs:
            p = src.address + pos
            got = self.resolve(elf, fn, src, s, pos)
            if got is None:
                rom_at = self.rom_target(typ, src, pos, target)
                problems.append({"at": f"{p:#010x}", "kind": "unknown-name", "name": s.name,
                                 "rom": None if rom_at is None else f"{rom_at:#010x}"})
                continue
            if got == "local-data":
                same = self.local_data(elf, src, s, typ, self.addend(typ, code, pos, addend),
                                       target, pos)
                if same is None:
                    notes["local-data-unchecked"] += 1
                elif same:
                    notes["local-data"] += 1
                else:
                    problems.append({"at": f"{p:#010x}", "kind": "local-data-differs",
                                     "name": s.name or elf.sections[s.shndx].name})
                continue
            want = self.expected(typ, got, self.addend(typ, code, pos, addend))
            actual = self.rom_target(typ, src, pos, target)
            if want is None or actual is None:
                notes[f"reloc-type-{typ}"] += 1
                continue
            if want != actual:
                problems.append({"at": f"{p:#010x}", "kind": "wrong-target", "name": s.name,
                                 "resolves": f"{want:#010x}", "rom": f"{actual:#010x}"})
            elif self.isa_mismatch(typ, target, pos, got):
                # BYTES masks the BL/BLX bit; the linker picks it from the callee's
                # instruction set, so a callee of the wrong kind would relink differently.
                problems.append({"at": f"{p:#010x}", "kind": "wrong-isa", "name": s.name})
        # Pool words the ROM relocates but the object does not: a number written in the
        # source where a symbol should be.
        have = {src.address + pos for pos, _, _, _ in relocs}
        hard = sorted(a for a in self.loads.get(src.module, ())
                      if src.address <= a < src.address + src.size and a not in have)
        if hard:
            res["hardcoded"] = len(hard)
        if notes:
            res["notes"] = dict(notes)
        if problems:
            for pr in problems:
                if pr.get("rom"):
                    where = int(pr["rom"], 16)
                    # suggest the symbol in the module the ROM's relocation names, when
                    # relocs.txt names exactly one (an address alone is ambiguous)
                    hint = self.reloc_mods[src.module].get(int(pr["at"], 16), [])
                    if len(hint) == 1:
                        cands = self.syms.by_addr.get((hint[0], where & ~1), [])
                    else:
                        cands = self.syms.at(where & ~1, src.module)
                    named = [x.name for x in cands if x.kind != "label"]
                    if named:
                        pr["rom_symbol"] = named[0]
            return {**res, "status": "link", "problems": problems}
        return {**res, "status": "ok"}

    def rom_abs(self, address: int, module: str, n: int) -> bytes:
        """`n` ROM bytes at an absolute address, looked up in `module` and then in the
        resident modules (an overlay's string can live in main's .rodata)."""
        for mod in (module, *C.RESIDENT):
            got = self.rom(mod, address, n)
            if got:
                return got
        return b""

    def local_data(self, elf: C.Elf, src: C.Source, s: C.ElfSymbol, typ: int,
                   addend: int, target: bytes, pos: int) -> bool | None:
        """Does the object's own data (a string literal, a static table) equal the ROM's
        bytes at the address the ROM's pointer holds? None when it cannot be compared:
        .bss has no contents, and only absolute pointers carry an address."""
        sec = elf.sections[s.shndx]
        if typ != 2 or sec.type == 8:
            return None
        where, = struct.unpack_from("<I", target, pos)
        data = elf.section_bytes(s.shndx)
        if s.type in (1, 2) and s.size:             # a named object or static function
            start, end = s.value, s.value + s.size
            where -= addend
            if s.type == 2:
                where &= ~1
        else:                                       # a literal: up to its terminator
            start = s.value + addend
            nul = data.find(b"\0", start, start + 512)
            end = nul + 1 if nul >= 0 else start + 16
        item = bytearray(data[start:end])
        if not item:
            return None
        rom = bytearray(self.rom_abs(where, src.module, len(item)))
        if len(rom) != len(item):
            return False
        # Relocated fields inside the item: an external symbol must resolve, through the table,
        # to what the ROM holds there; a reference to the object's own data cannot be placed
        # and is skipped. Either way the field is then excluded from the byte compare.
        for off, typ2, s2, rela2 in elf.relocations(s.shndx):
            if not (start <= off < end and typ2 in MASKS):
                continue
            rel = off - start
            if s2.shndx == 0 and rel + 4 <= len(item):
                hit = self.syms.lookup(s2.name, src.module)
                if hit is None:
                    return False
                s_addr = hit.address | (1 if hit.kind == "function" and hit.thumb else 0)
                want = self.expected(typ2, s_addr, self.addend(typ2, bytes(item), rel, rela2))
                p = where + rel
                if typ2 == 2:
                    got = struct.unpack_from("<I", rom, rel)[0]
                elif typ2 in THUMB_CALLS:
                    lo, hi = struct.unpack_from("<HH", rom, rel)
                    got = thumb_target(lo, hi, p) & 0xFFFFFFFF
                else:
                    got = arm_target(struct.unpack_from("<I", rom, rel)[0], p) & 0xFFFFFFFF
                if want != got:
                    return False
            for i, m in enumerate(MASKS[typ2]):
                if rel + i < len(item):
                    item[rel + i] &= m
                    rom[rel + i] &= m
        return rom == item

    def resolve(self, elf: C.Elf, fn: C.ElfSymbol, src: C.Source, s: C.ElfSymbol, pos: int):
        """Absolute address the linker would give symbol `s` (Thumb bit included for
        Thumb functions), "local-data" for this object's own data, or None if unknown."""
        if s.shndx == 0:                                  # undefined: the symbol table
            hit = self.syms.lookup(s.name, src.module)
            if hit is None:
                return None
            return hit.address | (1 if hit.kind == "function" and hit.thumb else 0)
        if s.shndx == fn.shndx:                           # this function's own section
            if s.type == 2 and s.name:
                hit = self.syms.lookup(s.name, src.module)
                if hit is not None:
                    return hit.address | (1 if hit.thumb else 0)
            base = src.address + (s.value - fn.value)
            return base | (1 if (s.type == 2 and src.thumb) else 0)
        return "local-data"                               # string literals, local tables

    @staticmethod
    def addend(typ: int, code: bytes, pos: int, rela: int | None) -> int:
        """The relocation addend: explicit for RELA, else decoded from the instruction."""
        if rela is not None:
            return rela
        if typ == 2:
            return struct.unpack_from("<I", code, pos)[0]
        if typ in THUMB_CALLS:
            lo, hi = struct.unpack_from("<HH", code, pos)
            return sext(((lo & 0x7FF) << 12) | ((hi & 0x7FF) << 1), 23)
        if typ in ARM_CALLS:
            return sext(struct.unpack_from("<I", code, pos)[0] & 0xFFFFFF, 24) << 2
        return 0

    @staticmethod
    def expected(typ: int, s_addr: int, addend: int) -> int | None:
        """What the ROM site should hold/reach once `s_addr` is linked in (ELF semantics:
        a branch encodes S + A - P, and the CPU adds the pipeline offset back)."""
        if typ == 2:
            return (s_addr + addend) & 0xFFFFFFFF
        if typ in THUMB_CALLS:
            return ((s_addr & ~1) + addend + 4) & 0xFFFFFFFF
        if typ in ARM_CALLS:
            return ((s_addr & ~1) + addend + 8) & 0xFFFFFFFF
        return None

    @staticmethod
    def isa_mismatch(typ: int, target: bytes, pos: int, s_addr: int) -> bool:
        """True when the ROM's call is BL but the callee is ARM, or BLX but it is Thumb."""
        if typ == 10:
            blx = (struct.unpack_from("<H", target, pos + 2)[0] & 0xF800) == 0xE800
            return blx == bool(s_addr & 1)
        if typ in (1, 28):
            blx = target[pos + 3] >> 4 == 0xF
            return blx != bool(s_addr & 1)
        return False

    @staticmethod
    def rom_target(typ: int, src: C.Source, pos: int, target: bytes) -> int | None:
        """What the ROM site actually holds/reaches."""
        p = src.address + pos
        if typ == 2:
            return struct.unpack_from("<I", target, pos)[0]
        if typ in THUMB_CALLS:
            lo, hi = struct.unpack_from("<HH", target, pos)
            return thumb_target(lo, hi, p) & 0xFFFFFFFF
        if typ in ARM_CALLS:
            return arm_target(struct.unpack_from("<I", target, pos)[0], p) & 0xFFFFFFFF
        return None

def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("paths", nargs="*", type=pathlib.Path)
    ap.add_argument("--workers", type=int, default=max(1, (os.cpu_count() or 4) - 2))
    args = ap.parse_args()

    files: list[pathlib.Path] = []
    for p in args.paths or [r for r in C.SOURCE_ROOTS if r.is_dir()]:
        p = p.resolve()
        files += sorted(x for x in p.rglob("*") if x.suffix in (".c", ".cpp")) if p.is_dir() \
            else [p]
    chk = Checker()
    results = []
    with cf.ThreadPoolExecutor(args.workers) as pool:
        for i, r in enumerate(pool.map(chk.check, files), 1):
            results.append(r)
            if i % 2000 == 0:
                print(f"  {i}/{len(files)}", flush=True)

    counts = collections.Counter(r["status"] for r in results)
    hard = sum(1 for r in results if r.get("hardcoded"))
    renamed = sum(1 for r in results if r.get("renamed"))
    out = C.BUILD / "verify.json"
    if not args.paths:
        out.write_text(json.dumps(results, indent=1) + "\n")
    for r in results:
        if r["status"] in ("bytes", "error"):
            print(f"  {r['status'].upper():<6} {r['file']}  {r.get('why', '')}")
    print(f"\n{len(results)} sources: " + ", ".join(f"{k} {v}" for k, v in counts.most_common()))
    print(f"  with hardcoded addresses: {hard}   header name differs from symbol table: {renamed}")
    if not args.paths:
        print(f"  details: {out.relative_to(C.ROOT)}")
    sys.exit(1 if counts["bytes"] or counts["error"] else 0)


if __name__ == "__main__":
    main()
