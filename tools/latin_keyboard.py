"""Opt-in Latin keyboard data and graphics. No game function instructions are modified."""
from __future__ import annotations

import struct

from localize_clean import Rom, checked, unpack

SYMBOLS = (
    0xE1, 0xE9, 0xED, 0xF3, 0xFA, 0xF1, 0xFC, 0xBF, 0xA1, 0xE7,
    0xC1, 0xC9, 0xCD, 0xD3, 0xDA, 0xD1, 0xDC, 0xE0, 0xE8, 0xEC,
    0xF2, 0xF9, 0xE4, 0xF6, 0xE2, 0xEA, 0xEE, 0xF4, 0xFB, 0xDF,
)
TILE_FIRST, TILE_COUNT = 0x1EA, 0x116
SYMBOL_TABLE = 0x0229E774
LOWER_TABLE, UPPER_TABLE = 0x0229E874, 0x0229E8E0
KEYS = 53


def western(code: int) -> int:
    return code - 0xFEE0 if 0xFF01 <= code <= 0xFF5E else code


def key_table(image: bytes, base: int) -> tuple[bytes, list[dict]]:
    result = bytearray(image)
    changes = []
    for address, count in ((SYMBOL_TABLE, 30), (LOWER_TABLE, KEYS), (UPPER_TABLE, KEYS)):
        start = address - base
        before = checked(image, start, count * 2)
        old = struct.unpack("<" + "H" * count, before)
        codes = SYMBOLS if address == SYMBOL_TABLE else tuple(western(c) for c in old)
        after = struct.pack("<" + "H" * count, *codes)
        result[start:start + len(after)] = after
        changes.append({"address": address, "size": len(after)})
    return bytes(result), changes


def font_glyphs(donor: Rom) -> dict[int, tuple[int, int, int, bytes]]:
    prefix = "/font/fontB_"
    header = unpack(donor.files[prefix + "head.bin"].data)
    attributes = unpack(donor.files[prefix + "attr.bin"].data)
    bitmaps = unpack(donor.files[prefix + "img.bin"].data)
    count, width, height = struct.unpack("<IHH", header)
    stride = (width * height + 7) // 8
    result = {}
    for i in range(count):
        code, advance, _ = struct.unpack("<HBB", checked(attributes, i * 4, 4))
        result[code] = (width, height, advance, checked(bitmaps, i * stride, stride))
    return result


def tile_pixels(chars: bytes, tile: int) -> bytes:
    number = (tile & 0x3FF) - TILE_FIRST
    if not 0 <= number < TILE_COUNT:
        return bytes(64)
    data = checked(chars, number * 32, 32)
    result = bytearray(64)
    for y in range(8):
        for x in range(8):
            sx = 7 - x if tile & 0x400 else x
            sy = 7 - y if tile & 0x800 else y
            result[y * 8 + x] = (data[sy * 4 + sx // 2] >> (4 * (sx & 1))) & 15
    return bytes(result)


def graphics(base: Rom, donor: Rom) -> dict[str, bytes]:
    chars = unpack(base.files["/menu/chat2/key9.bch"].data)
    glyphs = font_glyphs(donor)
    tiles, tile_numbers, outputs = [], {}, {}
    for filename, offset in (("b_key9.bsc", 0), ("b_chtk9.bsc", 8)):
        path = "/menu/chat2/" + filename
        screen = bytearray(unpack(base.files[path].data))
        original = struct.unpack("<1024H", screen)
        pixels = bytearray(256 * 256)
        for ty in range(9, 23):
            for tx in range(32):
                block = tile_pixels(chars, original[ty * 32 + tx])
                for y in range(8):
                    pos = (ty * 8 + y) * 256 + tx * 8
                    pixels[pos:pos + 8] = block[y * 8:y * 8 + 8]
        top = 96 + offset
        for y in range(top, top + 48):
            pixels[y * 256 + 8:y * 256 + 208] = bytes(200)
        for i, code in enumerate(SYMBOLS):
            width, height, advance, bitmap = glyphs[code]
            left = 8 + (i % 10) * 20 + (20 - advance) // 2
            y0 = top + (i // 10) * 16 + (16 - height) // 2
            for y in range(height):
                for x in range(width):
                    bit = y * width + x
                    if bitmap[bit // 8] & (0x80 >> (bit & 7)):
                        pixels[(y0 + y) * 256 + left + x] = 1
        for ty in range(9, 23):
            for tx in range(32):
                old = original[ty * 32 + tx]
                edited = tx * 8 < 208 and (tx + 1) * 8 > 8 and ty * 8 < top + 48 and (ty + 1) * 8 > top
                if not edited and not TILE_FIRST <= (old & 0x3FF) < TILE_FIRST + TILE_COUNT:
                    continue
                packed = bytearray()
                for y in range(8):
                    row = pixels[(ty * 8 + y) * 256 + tx * 8:(ty * 8 + y) * 256 + tx * 8 + 8]
                    packed.extend(row[x] | row[x + 1] << 4 for x in range(0, 8, 2))
                packed = bytes(packed)
                if packed not in tile_numbers:
                    if len(tiles) == TILE_COUNT:
                        raise ValueError("Latin keyboard exceeds its reserved tile range")
                    tile_numbers[packed] = TILE_FIRST + len(tiles)
                    tiles.append(packed)
                palette = 0x2000 if edited else old & 0xF000
                struct.pack_into("<H", screen, (ty * 32 + tx) * 2, palette | tile_numbers[packed])
        outputs[path] = bytes(screen)
    outputs["/menu/chat2/key9.bch"] = b"".join(tiles).ljust(TILE_COUNT * 32, b"\0")
    return outputs


def build(korean: bytes, base: Rom, donor: Rom) -> tuple[dict[str, bytes], int, bytes, dict]:
    import extract
    address, image, _ = extract.split(korean)["ov095"]
    patched, changes = key_table(image, address)
    allowed = {i for change in changes for i in range(change["address"] - address,
                                                     change["address"] - address + change["size"])}
    if any(a != b and i not in allowed for i, (a, b) in enumerate(zip(image, patched))):
        raise ValueError("keyboard patch changed bytes outside the three key tables")
    offset, size = struct.unpack_from("<II", korean, 0x50)
    for row in range(offset, offset + size, 32):
        overlay = struct.unpack_from("<8I", korean, row)
        if overlay[0] == 95:
            return graphics(base, donor), overlay[6], patched, {
                "overlay_table_offset": row, "data_ranges": changes,
                "symbols": list(SYMBOLS), "function_instructions_unchanged": True,
                "page": "symbols (third tab); existing English lower/upper pages retained"}
    raise ValueError("overlay 95 not found")
