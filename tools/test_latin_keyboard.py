"""Latin key codes and tile labels, on synthetic tables and bitmap glyphs only."""
from __future__ import annotations

import struct
from types import SimpleNamespace
import unittest

import latin_keyboard as K
from localize_clean import File


class Keyboard(unittest.TestCase):
    def test_accent_page_has_thirty_signed_safe_codes(self):
        self.assertEqual(len(K.SYMBOLS), 30)
        self.assertEqual(len(set(K.SYMBOLS)), 30)
        self.assertTrue(all(0 < c < 0x100 for c in K.SYMBOLS))
        for code in (0xF1, 0xD1, 0xE1, 0xE9, 0xED, 0xF3, 0xFA, 0xFC, 0xBF, 0xA1):
            self.assertIn(code, K.SYMBOLS)

    def test_western_maps_fullwidth_without_changing_commands(self):
        self.assertEqual(K.western(0xFF21), ord("A"))
        self.assertEqual(K.western(0xFF41), ord("a"))
        self.assertEqual(K.western(0xFF5E), ord("~"))
        for value in (0x100, 0x11F, 0x120, 0x0A, 0x3000, 0xE9):
            self.assertEqual(K.western(value), value)

    def test_only_three_explicit_data_ranges_change(self):
        base = K.SYMBOL_TABLE - 16
        before = bytearray((K.UPPER_TABLE - base) + K.KEYS * 2 + 16)
        for address, count in ((K.SYMBOL_TABLE, 34), (K.LOWER_TABLE, K.KEYS), (K.UPPER_TABLE, K.KEYS)):
            struct.pack_into("<" + "H" * count, before, address - base, *([0xFF21] * count))
        after, ranges = K.key_table(bytes(before), base)
        allowed = {p for row in ranges for p in range(row["address"] - base, row["address"] - base + row["size"])}
        self.assertEqual(len(before), len(after))
        self.assertTrue(all(a == b or i in allowed for i, (a, b) in enumerate(zip(before, after))))
        self.assertEqual(struct.unpack_from("<30H", after, K.SYMBOL_TABLE - base), K.SYMBOLS)
        self.assertEqual(before[K.SYMBOL_TABLE - base + 60:K.SYMBOL_TABLE - base + 68],
                         after[K.SYMBOL_TABLE - base + 60:K.SYMBOL_TABLE - base + 68])

    def test_tile_decode_flip_bits_and_palette(self):
        data = b"\x21" + bytes(31)
        self.assertEqual(K.tile_pixels(data, K.TILE_FIRST)[:2], b"\x01\x02")
        self.assertEqual(K.tile_pixels(data, K.TILE_FIRST | 0x400)[6:8], b"\x02\x01")
        self.assertEqual(K.tile_pixels(data, K.TILE_FIRST | 0x800)[56:58], b"\x01\x02")
        self.assertEqual(K.tile_pixels(data, K.TILE_FIRST | 0xA000), K.tile_pixels(data, K.TILE_FIRST))

    def test_each_drawn_label_matches_its_key_in_both_layouts(self):
        files = {"/menu/chat2/key9.bch": File(0, bytes(K.TILE_COUNT * 32))}
        for name in ("b_key9.bsc", "b_chtk9.bsc"):
            files["/menu/chat2/" + name] = File(1, struct.pack("<1024H", *([0x10] * 1024)))
        donor = {
            "/font/fontB_head.bin": File(0, struct.pack("<IHH", 30, 1, 1)),
            "/font/fontB_attr.bin": File(1, b"".join(struct.pack("<HBB", c, 1, 0) for c in K.SYMBOLS)),
            "/font/fontB_img.bin": File(2, b"\x80" * 30),
        }
        result = K.graphics(SimpleNamespace(files=files), SimpleNamespace(files=donor))
        chars = result["/menu/chat2/key9.bch"]
        self.assertEqual(len(chars), K.TILE_COUNT * 32)
        for filename, top in (("b_key9.bsc", 96), ("b_chtk9.bsc", 104)):
            screen = struct.unpack("<1024H", result["/menu/chat2/" + filename])
            for i in range(30):
                x, y = 8 + i % 10 * 20 + 9, top + i // 10 * 16 + 7
                tile = screen[(y // 8) * 32 + x // 8]
                self.assertEqual(tile & 0xF000, 0x2000)
                self.assertEqual(K.tile_pixels(chars, tile)[y % 8 * 8 + x % 8], 1)
            self.assertEqual(screen[0], 0x10)


if __name__ == "__main__":
    unittest.main()
