"""Rebuild every ARM9 module image from the sources and compare it with the ROM.

    python tools/relink.py            # all modules; writes build/adm-kr/relink/<module>.bin
    python tools/relink.py ov065 main

Each function is compiled, placed at its address and relocated with this repository's
symbol table (BL/BLX chosen by the callee's instruction set). Bytes outside functions are
copied from the ROM, since data is not decompiled yet; the report shows how many bytes of
each module came from sources.
"""

from __future__ import annotations

import argparse
import concurrent.futures as cf
import hashlib
import os
import pathlib
import struct
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import common as C  # noqa: E402
import verify as V  # noqa: E402

OUT = C.BUILD / "relink"


def encode(typ: int, word: bytes, p: int, s_addr: int, addend: int) -> bytes | None:
    """The 4 bytes at P after linking symbol address `s_addr` (Thumb bit set for Thumb)."""
    if typ == 2:
        return struct.pack("<I", (s_addr + addend) & 0xFFFFFFFF)
    if typ in V.THUMB_CALLS:
        dest = (s_addr & ~1) + addend + 4
        if s_addr & 1 or typ == 30:                 # Thumb callee: BL
            off = dest - (p + 4)
            return struct.pack("<HH", 0xF000 | ((off >> 12) & 0x7FF), 0xF800 | ((off >> 1) & 0x7FF))
        off = dest - ((p + 4) & ~3)                  # ARM callee: BLX
        return struct.pack("<HH", 0xF000 | ((off >> 12) & 0x7FF), 0xE800 | ((off >> 1) & 0x7FE))
    if typ in V.ARM_CALLS:
        dest = (s_addr & ~1) + addend + 8
        off = dest - (p + 8)
        orig, = struct.unpack("<I", word)
        if s_addr & 1 and typ != 29:                # Thumb callee: BLX(imm)
            return struct.pack("<I", 0xFA000000 | (((off >> 1) & 1) << 24) | ((off >> 2) & 0xFFFFFF))
        return struct.pack("<I", (orig & 0xFF000000) | ((off >> 2) & 0xFFFFFF))
    return None


class Linker(V.Checker):
    def link_function(self, path: pathlib.Path):
        """(address, linked code, unresolved names) or (address, None, reason)."""
        src = C.parse_source(path)
        obj, log = C.compile_source(src)
        if obj is None:
            return src, None, ["does not compile"]
        elf = C.Elf(obj)
        fn = elf.function(src.object_symbol)
        if fn is None:
            return src, None, [f"no {src.object_symbol} in object"]
        code = bytearray(elf.section_bytes(fn.shndx)[fn.value:fn.value + fn.size])
        target = self.rom(src.module, src.address, src.size)
        unresolved = []
        for off, typ, s, rela in elf.relocations(fn.shndx):
            pos = off - fn.value
            if not 0 <= pos < len(code):
                continue
            addend = self.addend(typ, code, pos, rela)
            got = self.resolve(elf, fn, src, s, pos)
            if got is None:
                unresolved.append(s.name)
                continue
            if got == "local-data":
                # The data layout is not decompiled: place the item where the ROM has it.
                code[pos:pos + 4] = target[pos:pos + 4]
                continue
            new = encode(typ, bytes(code[pos:pos + 4]), src.address + pos, got, addend)
            if new is not None:
                code[pos:pos + 4] = new
        return src, bytes(code), unresolved

    def build(self, module: str, workers: int) -> dict:
        info = self.mods[module]
        base, rom = info["base"], self.images[module]
        img = bytearray(rom)                        # non-code bytes come from the ROM
        from_src = 0
        unresolved = failed = 0
        files = C.module_sources(module)
        with cf.ThreadPoolExecutor(workers) as pool:
            for src, code, why in pool.map(self.link_function, files):
                off = src.address - base
                if code is None:
                    failed += 1
                    img[off:off + src.size] = bytes(src.size)
                    continue
                img[off:off + len(code)] = code
                from_src += len(code)
                unresolved += bool(why)
        OUT.mkdir(parents=True, exist_ok=True)
        (OUT / f"{module}.bin").write_bytes(img)
        diff = next((i for i in range(len(img)) if img[i] != rom[i]), None)
        return {"module": module, "size": len(rom), "functions": len(files),
                "from_source": from_src, "unresolved": unresolved, "failed": failed,
                "match": hashlib.sha1(img).hexdigest() == info["sha1"],
                "first_diff": None if diff is None else base + diff}


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("modules", nargs="*")
    ap.add_argument("--workers", type=int, default=max(1, (os.cpu_count() or 4) - 2))
    args = ap.parse_args()
    lk = Linker()
    names = args.modules or sorted(lk.mods, key=lambda m: (m.startswith("ov"), m))
    rows = [lk.build(m, args.workers) for m in names]

    print(f"{'module':<11} {'funcs':>6} {'code from src':>14} {'ROM size':>9}  sha1   first diff")
    for r in rows:
        pct = 100 * r["from_source"] / r["size"] if r["size"] else 0
        print(f"{r['module']:<11} {r['functions']:>6} {r['from_source']:>8} ({pct:4.1f}%)"
              f" {r['size']:>9}  {'ok' if r['match'] else 'DIFF':<5}  "
              f"{'' if r['first_diff'] is None else hex(r['first_diff'])}")
    total = sum(r["size"] for r in rows)
    src = sum(r["from_source"] for r in rows)
    ok = sum(r["match"] for r in rows)
    print(f"\n{ok}/{len(rows)} modules SHA-1 identical; {src:,} of {total:,} bytes "
          f"({100 * src / total:.1f}%) are linked code from sources, the rest copied from the ROM")


if __name__ == "__main__":
    main()
