"""Synthetic resource tests: no game files, messages, fonts or compiler required."""
from __future__ import annotations

import struct
import unittest

import localize_clean as L


def bmg(texts: list[bytes], encoding: int, entry_size: int = 12) -> bytes:
    data = bytearray(b"\0" * (2 if encoding == 2 else 1))
    entries = bytearray()
    for text in texts:
        entries.extend(struct.pack("<I", len(data)))
        entries.extend(bytes([0x55]) * (entry_size - 4))
        data.extend(text)
    info = L.align(b"INF1" + b"\0" * 4 + struct.pack("<HHI", len(texts), entry_size, 0) + entries)
    info = info[:4] + struct.pack("<I", len(info)) + info[8:]
    section = L.align(b"DAT1" + b"\0" * 4 + data)
    section = section[:4] + struct.pack("<I", len(section)) + section[8:]
    header = bytearray(32)
    header[:8] = b"MESGbmg1"
    struct.pack_into("<II", header, 8, 32 + len(info) + len(section), 2)
    header[16] = encoding
    return bytes(header) + info + section


class Resources(unittest.TestCase):
    def test_byte_text_and_accents(self):
        self.assertEqual(L.convert_text(b"\xa1Qu\xe9!\n\0", {}), "\u00a1Qu\u00e9!\n\0".encode("utf-16le"))

    def test_control_parameters_are_not_expanded_as_text(self):
        original = bytes([26, 7, 2, 0, 0, 1, 2])
        self.assertEqual(L.convert_text(original, {}), bytes([26, 0, 8, 2, 0, 0, 1, 2]))

    def test_odd_tag_padding(self):
        self.assertEqual(L.convert_text(bytes([26, 6, 255, 0, 0, 5]), {}),
                         bytes([26, 0, 8, 255, 0, 0, 5, 0]))

    def test_grammar_is_explicitly_reported(self):
        report = {}
        self.assertEqual(L.convert_text(bytes([26, 8, 11, 4, 0]) + b"o\0a", report), b"o\0")
        self.assertEqual(report, {"4": 1})

    def test_rebuilt_offsets_attributes_and_sizes(self):
        kr = bmg([b"k\0\0\0", b"r\0\0\0"], 2)
        eu = bmg([b"one\0", b"two\0"], 1)
        converted = L.convert_bmg(kr, eu, {})
        self.assertIsNotNone(converted)
        size, count, entry = L.bmg_shape(converted)
        self.assertEqual((count, entry), (2, 12))
        self.assertEqual(struct.unpack_from("<I", converted, 8)[0], len(converted))
        self.assertEqual(converted[0x34:0x3C], kr[0x34:0x3C])
        offset = struct.unpack_from("<I", converted, 0x3C)[0]
        self.assertEqual(converted[32 + size + 8 + offset:32 + size + 8 + offset + 8], b"t\0w\0o\0\0\0")

    def test_shared_message_offsets(self):
        kr = bmg([b"k\0\0\0", b"r\0\0\0"], 2)
        eu = bytearray(bmg([b"same\0", b"unused\0"], 1))
        eu[0x3C:0x40] = eu[0x30:0x34]
        converted = L.convert_bmg(kr, bytes(eu), {})
        self.assertEqual(converted[0x30:0x34], converted[0x3C:0x40])

    def test_count_or_legacy_encoding_falls_back(self):
        self.assertIsNone(L.convert_bmg(bmg([b"a\0\0\0"], 2), bmg([b"a\0", b"b\0"], 1), {}))
        self.assertIsNone(L.convert_bmg(bmg([b"a\0"], 3), bmg([b"a\0"], 1), {}))

    def test_plain_and_compressed_resources(self):
        self.assertEqual(L.unpack(b"plain"), b"plain")
        self.assertEqual(L.unpack(b"LZ77\x10\x06\0\0\x10abc\0\x02"), b"abcabc")
        self.assertEqual(L.unpack(b"LZ77\xf7\x03\0\0\x07\0\0\0\x10\0abc"), b"abc")

    def test_invalid_compression_and_tags(self):
        for data in (b"\x10\x03\0\0\x80\0\0", b"\0\x03\0\0x"):
            with self.assertRaises(ValueError):
                L.lz10(data)
        for text in (bytes([26, 1, 0, 0, 0]), bytes([26, 8, 0, 0, 0])):
            with self.assertRaises(ValueError):
                L.convert_text(text, {})

    def test_font_merge_preserves_fallback_and_resizes_pixels(self):
        kr = {"head": struct.pack("<IHH", 2, 1, 1),
              "attr": struct.pack("<HBBHBB", 65, 1, 0, 0xAC00, 1, 0), "img": b"\x80\x80"}
        eu = {"head": struct.pack("<IHH", 1, 2, 1), "attr": struct.pack("<HBB", 65, 2, 0), "img": b"\x40"}
        result = L.merge_font(kr, eu)
        self.assertEqual(struct.unpack("<IHH", result["head"]), (2, 2, 1))
        self.assertEqual(result["img"], b"\x40\x80")
        self.assertEqual(result["attr"][:4], eu["attr"])
        self.assertEqual(result["attr"][4:], kr["attr"][4:])

    def test_rom_replacement_preserves_original_and_file_id(self):
        data = bytearray(0x244)
        struct.pack_into("<IIII", data, 0x40, 0x200, 15, 0x220, 8)
        struct.pack_into("<IHH", data, 0x200, 8, 0, 1)
        data[0x208:0x20F] = b"\x05a.bin\0"
        struct.pack_into("<II", data, 0x220, 0x240, 0x244)
        data[0x240:] = b"base"
        original = bytes(data)
        rom = L.Rom(original)
        result = rom.replace({"/a.bin": b"localized"})
        self.assertEqual(rom.data, original)
        replaced = L.Rom(result)
        self.assertEqual(replaced.files["/a.bin"], L.File(0, b"localized"))
        self.assertEqual(result[0x240:0x244], b"base")
        import setup
        self.assertEqual(struct.unpack_from("<H", result, 0x15E)[0], setup.header_crc(result))
        self.assertEqual(len(result), 1 << (result[0x14] + 17))

    def test_wrong_dumps_rejected_before_generation(self):
        with self.assertRaisesRegex(ValueError, "Korean base"):
            L.generate(b"wrong", b"wrong", "es")


if __name__ == "__main__":
    unittest.main()
