"""Build experimental European-language resources for the Korean Clean runtime.

Both user-supplied ROMs stay private. The generated ROM retains the Korean executable;
only filesystem resources are replaced. See docs/localized-clean.md for limitations.
"""
from __future__ import annotations

import argparse
from dataclasses import dataclass
import hashlib
import json
from pathlib import Path
import struct

ROOT = Path(__file__).resolve().parents[1]
LANGUAGES = {"en": "ENG", "fr": "FRN", "de": "GER", "es": "SPN", "it": "ITA"}
EU_SHA1 = "858da57a18852e75304e423519dde6a548d5264b"
KR_SHA1 = "1fffd601d3439e37cd934e72d08e487a93fc449b"


def checked(data: bytes, start: int, size: int) -> bytes:
    if start < 0 or size < 0 or start + size > len(data):
        raise ValueError("resource range outside its container")
    return data[start:start + size]


@dataclass(frozen=True)
class File:
    id: int
    data: bytes


class Rom:
    def __init__(self, data: bytes):
        self.data = data
        names_at, names_size = struct.unpack_from("<II", data, 0x40)
        self.fat_at, fat_size = struct.unpack_from("<II", data, 0x48)
        names = checked(data, names_at, names_size)
        fat = checked(data, self.fat_at, fat_size)
        self.files: dict[str, File] = {}
        seen = set()

        def walk(directory: int, parent: str = "") -> None:
            if directory in seen:
                raise ValueError("cyclic ROM directory table")
            seen.add(directory)
            row = checked(names, (directory & 0xFFF) * 8, 8)
            offset, file_id, _ = struct.unpack("<IHH", row)
            while checked(names, offset, 1)[0]:
                tag = names[offset]
                offset += 1
                name = checked(names, offset, tag & 127).decode("ascii")
                offset += tag & 127
                path = f"{parent}/{name}"
                if tag & 128:
                    child, = struct.unpack("<H", checked(names, offset, 2))
                    offset += 2
                    walk(child, path)
                else:
                    start, end = struct.unpack("<II", checked(fat, file_id * 8, 8))
                    if path in self.files:
                        raise ValueError(f"duplicate ROM path: {path}")
                    self.files[path] = File(file_id, checked(data, start, end - start))
                    file_id += 1

        walk(0xF000)

    def replace(self, replacements: dict[str, bytes], unnamed: dict[int, bytes] | None = None) -> bytes:
        """Append files and update their FAT entries; never rewrite executable images."""
        result = bytearray(self.data)
        files = {self.files[name].id: data for name, data in replacements.items()}
        for file_id, data in (unnamed or {}).items():
            if file_id in files:
                raise ValueError("duplicate named/unnamed resource replacement")
            files[file_id] = data
        for file_id, data in sorted(files.items()):
            result.extend(b"\xff" * (-len(result) % 4))
            start = len(result)
            result.extend(data)
            struct.pack_into("<II", result, self.fat_at + file_id * 8, start, len(result))
        struct.pack_into("<I", result, 0x80, len(result))
        capacity = max(0, (len(result) - 1).bit_length() - 17)
        result[0x14] = capacity
        result.extend(b"\xff" * ((1 << (capacity + 17)) - len(result)))
        import setup
        struct.pack_into("<H", result, 0x15E, setup.header_crc(result))
        return bytes(result)


def lz10(data: bytes, limit: int | None = None) -> bytes:
    size = int.from_bytes(checked(data, 1, 3), "little")
    if limit is not None:
        size = min(size, limit)
    if data[0] == 0:
        return checked(data, 4, size)
    if data[0] != 0x10:
        raise ValueError("unsupported LZ type")
    result = bytearray()
    pos = 4
    while len(result) < size:
        flags = checked(data, pos, 1)[0]
        pos += 1
        for bit in range(7, -1, -1):
            if len(result) == size:
                break
            if flags & (1 << bit):
                a, b = checked(data, pos, 2)
                pos += 2
                distance = ((a & 15) << 8 | b) + 1
                count = (a >> 4) + 3
                if distance > len(result):
                    raise ValueError("invalid LZ back reference")
                for _ in range(min(count, size - len(result))):
                    result.append(result[-distance])
            else:
                result.extend(checked(data, pos, 1))
                pos += 1
    return bytes(result)


def unpack(data: bytes) -> bytes:
    if data[:4] != b"LZ77":
        return data
    info, = struct.unpack("<I", checked(data, 4, 4))
    if info & 0xF0 != 0xF0:
        return lz10(data[4:])
    size, block_size = info >> 8, 32 << (info & 15)
    count = (size + block_size - 1) // block_size
    ends = [0, *struct.unpack("<" + "H" * count, checked(data, 8, count * 2))]
    start = 8 + count * 2
    blocks = [lz10(checked(data, start + ends[i], ends[i + 1] - ends[i]), min(block_size, size - i * block_size))
              for i in range(count)]
    result = b"".join(blocks)
    if len(result) != size:
        raise ValueError("incorrect decompressed resource size")
    return result


def align(data: bytes, alignment: int = 32) -> bytes:
    return data + b"\0" * (-len(data) % alignment)


def convert_text(text: bytes, grammar: dict[str, int]) -> bytes:
    """Expand byte characters and the five-byte tag header to Korean UTF-16 format.

    European grammatical alternatives have no Korean implementation. Resolve their first
    form explicitly and report that approximation; do not dispatch them as Korean particles.
    """
    result = bytearray()
    pos = 0
    while pos < len(text):
        char = text[pos]
        if char != 0x1A:
            result.extend((char, 0))
            pos += 1
            continue
        length, group, kind = struct.unpack("<BBH", checked(text, pos + 1, 4))
        if length < 5:
            raise ValueError("short BMG tag")
        tag = checked(text, pos, length)
        if group == 11:
            key = str(kind)
            grammar[key] = grammar.get(key, 0) + 1
            if kind >= 4:
                first = tag[5:].split(b"\0", 1)[0]
                for char in first:
                    result.extend((char, 0))
        else:
            expanded = b"\x1a\0\0" + tag[2:]
            expanded = align(expanded, 2)
            if len(expanded) > 255:
                raise ValueError("expanded BMG tag exceeds byte size")
            result.extend(expanded[:2] + bytes([len(expanded)]) + expanded[3:])
        pos += length
    return bytes(result)


def bmg_shape(data: bytes) -> tuple[int, int, int]:
    checked(data, 0, 0x30)
    if data[:8] != b"MESGbmg1" or data[0x20:0x24] != b"INF1":
        raise ValueError("invalid BMG magic")
    section_size, count, entry_size = struct.unpack_from("<IHH", data, 0x24)
    if entry_size not in (4, 12) or 16 + count * entry_size > section_size:
        raise ValueError("invalid BMG entries")
    if checked(data, 0x20 + section_size, 4) != b"DAT1":
        raise ValueError("missing BMG data section")
    return section_size, count, entry_size


def convert_bmg(korean: bytes, european: bytes, grammar: dict[str, int]) -> bytes | None:
    _, kr_count, kr_entry = bmg_shape(korean)
    section_size, count, entry = bmg_shape(european)
    if (kr_count, kr_entry) != (count, entry):
        return None
    if european[0x10] != 1 or korean[0x10] != 2:
        return None  # Unused Japanese remnants are not compatible with this UTF-16 reader.
    source = european[0x20 + section_size + 8:]
    payload = bytearray(b"\0\0")
    entries = bytearray()
    offsets = [struct.unpack_from("<I", european, 0x30 + i * entry)[0] for i in range(count)]
    boundaries = sorted(set(offsets)) + [len(source)]
    cache = {}
    for old_offset, next_offset in zip(boundaries, boundaries[1:]):
        cache[old_offset] = len(payload)
        payload.extend(convert_text(checked(source, old_offset, next_offset - old_offset), grammar))
    for i in range(count):
        old_offset = offsets[i]
        entries.extend(struct.pack("<I", cache[old_offset]))
        # Keep the base game's attributes and message indices; only replace text data.
        entries.extend(korean[0x34 + i * entry:0x30 + (i + 1) * entry])
    info = align(b"INF1" + b"\0" * 4 + struct.pack("<HHI", count, entry, 0) + entries)
    info = info[:4] + struct.pack("<I", len(info)) + info[8:]
    data = align(b"DAT1" + b"\0" * 4 + payload)
    data = data[:4] + struct.pack("<I", len(data)) + data[8:]
    header = bytearray(korean[:0x20])
    struct.pack_into("<I", header, 8, 0x20 + len(info) + len(data))
    return bytes(header) + info + data


def merge_font(korean: dict[str, bytes], european: dict[str, bytes]) -> dict[str, bytes]:
    """Keep Korean fallback glyphs while replacing Western glyphs and preserving accents."""
    fonts = []
    for source in (korean, european):
        count, width, height = struct.unpack("<IHH", source["head"])
        stride = (width * height + 7) // 8
        checked(source["attr"], 0, count * 4)
        checked(source["img"], 0, count * stride)
        fonts.append((source, count, width, height, stride))
    width = max(fonts[0][2], fonts[1][2])
    height = max(fonts[0][3], fonts[1][3])
    stride = (width * height + 7) // 8
    if stride > 0x84:
        raise ValueError("font glyph exceeds the Korean renderer's buffer")
    glyphs = {}
    for source, count, old_width, old_height, old_stride in fonts:
        for i in range(count):
            attribute = source["attr"][i * 4:(i + 1) * 4]
            code, = struct.unpack_from("<H", attribute)
            old = source["img"][i * old_stride:(i + 1) * old_stride]
            bitmap = bytearray(stride)
            for y in range(old_height):
                for x in range(old_width):
                    bit = y * old_width + x
                    if old[bit // 8] & (0x80 >> (bit % 8)):
                        target = y * width + x
                        bitmap[target // 8] |= 0x80 >> (target % 8)
            glyphs[code] = (attribute, bytes(bitmap))
    ordered = [glyphs[c] for c in sorted(glyphs)]
    return {"head": struct.pack("<IHH", len(ordered), width, height),
            "attr": b"".join(a for a, _ in ordered), "img": b"".join(b for _, b in ordered)}


def generate(korean: bytes, european: bytes, language: str, latin_keyboard: bool = False) -> tuple[bytes, dict]:
    if language not in LANGUAGES:
        raise ValueError("unsupported language")
    if hashlib.sha1(korean).hexdigest() != KR_SHA1:
        raise ValueError("Korean base ROM does not match adm-kr.sha1")
    if hashlib.sha1(european).hexdigest() != EU_SHA1:
        raise ValueError("unsupported European ROM revision or dump")
    base, donor = Rom(korean), Rom(european)
    replacements, fallback, grammar = {}, [], {}
    prefix = f"/script/{LANGUAGES[language]}/"
    for name, file in base.files.items():
        if not name.startswith("/script/KOR/"):
            continue
        target = prefix + name[len("/script/KOR/"):]
        try:
            converted = convert_bmg(unpack(file.data), unpack(donor.files[target].data), grammar)
        except ValueError as exc:
            raise ValueError(f"{name}: {exc}") from exc
        if converted is None:
            fallback.append(name)
        else:
            replacements[name] = converted
    for font in "ABCD":
        name = f"/font/font{font}"
        suffix = "_" + LANGUAGES[language].lower() if font == "C" else ""
        parts = ("head", "attr", "img")
        merged = merge_font({p: unpack(base.files[f"{name}_{p}.bin"].data) for p in parts},
                            {p: unpack(donor.files[f"{name}_{p}{suffix}.bin"].data) for p in parts})
        for part, data in merged.items():
            replacements[f"{name}_{part}.bin"] = data
    # Only the title's four language-specific graphics share this layout and basename.
    for name in base.files:
        if name.startswith("/a_mes/a_mes_ttl_"):
            target = name.replace("_n", "_" + LANGUAGES[language].lower() + "_n")
            if target in donor.files:
                replacements[name] = donor.files[target].data
    unnamed, keyboard_report = {}, None
    if latin_keyboard:
        import latin_keyboard as keyboard
        resources, file_id, image, keyboard_report = keyboard.build(korean, base, donor)
        replacements.update(resources)
        unnamed[file_id] = image
    result = bytearray(base.replace(replacements, unnamed))
    if latin_keyboard:
        # Store the replacement overlay uncompressed; its load size and code are unchanged.
        row = keyboard_report["overlay_table_offset"]
        struct.pack_into("<I", result, row + 28, 0)
    result = bytes(result)
    import extract
    original_modules = extract.split(korean)
    actual_modules = extract.split(result)
    for name, (address, image, bss) in original_modules.items():
        expected = unnamed[file_id] if latin_keyboard and name == "ov095" else image
        if actual_modules[name] != (address, expected, bss):
            raise ValueError(f"localization changed an unexpected executable module: {name}")
    report = {"language": language, "mode": "Clean, Korean executable with localized resources",
              "base_sha1": KR_SHA1, "donor_sha1": EU_SHA1,
              "generated_sha1": hashlib.sha1(result).hexdigest(),
              "replaced_files": len(replacements), "fallback_files": fallback,
              "grammar_first_form_tags": grammar,
              "executable_modules_unchanged": len(original_modules) - int(latin_keyboard),
              "latin_keyboard": keyboard_report}
    return result, report


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--korean", type=Path, default=ROOT / "extract" / "adm-kr.nds")
    ap.add_argument("--european", type=Path, required=True)
    ap.add_argument("--language", choices=LANGUAGES, default="es")
    ap.add_argument("--latin-keyboard", action="store_true", help="Latin symbol page with Western accents")
    args = ap.parse_args()
    try:
        path, report = prepare(args.korean, args.european, args.language, args.latin_keyboard)
    except (ValueError, OSError, KeyError, struct.error) as exc:
        ap.error(str(exc))
    print(f"{report['replaced_files']} resources replaced; {len(report['fallback_files'])} files kept Korean")
    print(f"All {report['executable_modules_unchanged']} executable modules unchanged. ROM: {path}")


def prepare(korean: Path, european: Path, language: str, latin_keyboard: bool = False) -> tuple[Path, dict]:
    data, report = generate(korean.read_bytes(), european.read_bytes(), language, latin_keyboard)
    out = ROOT / "build" / "localized-clean" / language
    out.mkdir(parents=True, exist_ok=True)
    path = out / "game.nds"
    if not path.exists() or hashlib.sha1(path.read_bytes()).hexdigest() != report["generated_sha1"]:
        path.write_bytes(data)
    (out / "report.json").write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    return path, report


if __name__ == "__main__":
    main()
