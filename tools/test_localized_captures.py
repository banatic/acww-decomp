"""Synthetic tests for the explicitly audited fish capture archive shape."""
from __future__ import annotations

import struct
import unittest

import localize_clean as L
from test_localize_clean import bmg


def pair():
    return (bmg(["original\0".encode("utf-16le")] * 65 + [b"\0\0"] * 2, 2),
            bmg([f"row {i}\0".encode("ascii") for i in range(65)], 1))


class Capture(unittest.TestCase):
    def test_opt_in_preserves_all_indices_and_original_attributes(self):
        base, donor = pair()
        self.assertIsNone(L.convert_bmg(base, donor, {}))
        result = L.convert_bmg(base, donor, {}, allow_fish_tail=True)
        size, count, entry = L.bmg_shape(result)
        self.assertEqual((count, entry), (67, 12))
        data = result[32 + size + 8:]
        for i in range(67):
            offset, = struct.unpack_from("<I", result, 48 + i * entry)
            self.assertEqual(result[52 + i * entry:48 + (i + 1) * entry],
                             base[52 + i * entry:48 + (i + 1) * entry])
            expected = (f"row {i}\0" if i < 65 else "\0").encode("utf-16le")
            self.assertEqual(data[offset:offset + len(expected)], expected)

    def test_nonempty_original_tail_is_rejected(self):
        _, donor = pair()
        base = bmg([b"x\0\0\0"] * 66 + [b"y\0\0\0"], 2)
        self.assertFalse(L.fish_capture_compatible(base, donor))
        self.assertIsNone(L.convert_bmg(base, donor, {}, allow_fish_tail=True))

    def test_other_counts_entry_sizes_and_encodings_are_not_approved(self):
        base, donor = pair()
        alternatives = [(bmg([b"\0\0"] * 66, 2), donor),
                        (base, bmg([b"x\0"] * 64, 1)),
                        (bmg([b"\0\0"] * 67, 2, 4), bmg([b"x\0"] * 65, 1, 4)),
                        (bmg([b"\0"] * 67, 1), donor)]
        for first, second in alternatives:
            self.assertFalse(L.fish_capture_compatible(first, second))

    def test_corrupt_empty_tail_offset_is_rejected(self):
        base, donor = pair()
        broken = bytearray(base)
        struct.pack_into("<I", broken, 48 + 65 * 12, 0xFFFFFFF0)
        with self.assertRaises(ValueError):
            L.fish_capture_compatible(bytes(broken), donor)


if __name__ == "__main__":
    unittest.main()
