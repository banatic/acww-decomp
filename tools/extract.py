"""Split the base ROM into the ARM9 modules the sources are checked against.

    python tools/extract.py            # finds the .nds in extract/ and checks its SHA-1

Writes build/adm-kr/rom/<module>.bin (decompressed, as loaded in RAM) and modules.json
(load address, code size and .bss size of each module). The main module and overlays may be
BLZ-compressed; autoloads (ITCM, DTCM, ...) follow the main module.
"""

from __future__ import annotations

import hashlib
import json
import pathlib
import struct
import sys

ROOT = pathlib.Path(__file__).resolve().parents[1]
EXTRACT = ROOT / "extract"
OUT = ROOT / "build" / "adm-kr" / "rom"
SHA1_FILE = ROOT / "adm-kr.sha1"

ARM9_BUILD_INFO_MAGIC = bytes.fromhex("2106c0de dec00621".replace(" ", ""))


def blz_decompress(data: bytes) -> bytes:
    """Backward LZ, the format NitroSDK's `compstatic` writes.

    The last eight bytes describe the stream: header length (top byte) and compressed
    length (low 24 bits), then how many bytes the output grows by. Everything before
    `len - compressed length` is stored as-is (the secure area, for the static image).
    """
    info, extra = struct.unpack_from("<II", data, len(data) - 8)
    if extra == 0:
        return data
    hdr_len, comp_len = info >> 24, info & 0xFFFFFF
    end = len(data)
    out = bytearray(data) + bytearray(extra)
    src, dst, stop = end - hdr_len, end + extra, end - comp_len
    while src > stop:
        src -= 1
        flags = data[src]
        for _ in range(8):
            if src <= stop:
                break
            if flags & 0x80:
                src -= 2
                pair = data[src + 1] << 8 | data[src]
                disp, n = (pair & 0xFFF) + 3, (pair >> 12) + 3
                for _ in range(n):
                    dst -= 1
                    out[dst] = out[dst + disp]
            else:
                src -= 1
                dst -= 1
                out[dst] = data[src]
            flags = (flags << 1) & 0xFF
    return bytes(out)


def find_rom() -> pathlib.Path:
    roms = sorted(EXTRACT.glob("*.nds"))
    if len(roms) != 1:
        sys.exit(f"put exactly one .nds file in {EXTRACT} (found {len(roms)})")
    return roms[0]


def split(rom: bytes) -> dict[str, tuple[int, bytes, int]]:
    """module name -> (load address, image bytes, .bss size)."""
    arm9_off, _entry, arm9_ram, arm9_size = struct.unpack_from("<IIII", rom, 0x20)
    ovt_off, ovt_size = struct.unpack_from("<II", rom, 0x50)
    fat_off, = struct.unpack_from("<I", rom, 0x48)

    arm9 = rom[arm9_off:arm9_off + arm9_size]
    # The build info block ends with the SDK's magic pair; its address is not in the
    # header, so find it the same way the SDK's own tools do.
    magic = arm9.find(ARM9_BUILD_INFO_MAGIC)
    if magic < 0:
        sys.exit("ARM9 build info not found")
    # The build info block precedes the magic: 7 words, then the magic.
    bi = magic - 0x1C
    (al_start, al_end, al_data, bss_start, bss_end,
     comp_end, _sdk) = struct.unpack_from("<7I", arm9, bi)
    if comp_end:
        n = comp_end - arm9_ram
        arm9 = bytearray(blz_decompress(arm9[:n]) + arm9[n:])
        # The SDK's decompressor clears this word once it has run; the image in RAM, which
        # is what the code was linked into, has zero here.
        struct.pack_into("<I", arm9, bi + 0x14, 0)
        arm9 = bytes(arm9)

    mods: dict[str, tuple[int, bytes, int]] = {}
    main_end = al_data - arm9_ram
    mods["main"] = (arm9_ram, arm9[:main_end], bss_end - bss_start)

    names = {0x01FF8000: "itcm", 0x027E0000: "dtcm"}
    unk = 2
    cursor = main_end
    for k in range((al_end - al_start) // 12):
        base, size, bss = struct.unpack_from("<III", arm9, al_start - arm9_ram + 12 * k)
        name = names.get(base)
        if name is None:
            name, unk = f"autoload_{unk}", unk + 1
        mods[name] = (base, arm9[cursor:cursor + size], bss)
        cursor += size

    for k in range(ovt_size // 32):
        (oid, ram, size, bss, _s0, _s1, file_id,
         flags) = struct.unpack_from("<8I", rom, ovt_off + 32 * k)
        start, end = struct.unpack_from("<II", rom, fat_off + 8 * file_id)
        data = rom[start:end]
        if (flags >> 24) & 1:
            data = blz_decompress(data[:flags & 0xFFFFFF])
        mods[f"ov{oid:03d}"] = (ram, data[:size], bss)
    return mods


def main() -> None:
    path = find_rom()
    rom = path.read_bytes()
    want = SHA1_FILE.read_text(encoding="utf-8").split()[0].lower()
    got = hashlib.sha1(rom).hexdigest()
    if got != want:
        sys.exit(f"{path.name}: SHA-1 {got}, expected {want} (see INSTALL.md)")

    OUT.mkdir(parents=True, exist_ok=True)
    table = {}
    for name, (base, image, bss) in split(rom).items():
        (OUT / f"{name}.bin").write_bytes(image)
        table[name] = {"base": base, "size": len(image), "bss": bss,
                       "sha1": hashlib.sha1(image).hexdigest()}
    (OUT / "modules.json").write_text(json.dumps(table, indent=1) + "\n")
    print(f"{path.name}: SHA-1 ok, {len(table)} modules -> {OUT.relative_to(ROOT)}")


if __name__ == "__main__":
    main()
