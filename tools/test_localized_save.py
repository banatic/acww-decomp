"""Synthetic saved-town integrity tests; no ROM or real save required."""
from __future__ import annotations

import struct
import unittest

import check_localized_save as S


def bank(player="pe\u00f1a", town="\u00e1lano"):
    data = bytearray(S.BANK_SIZE)
    data[0] = 0x32
    for offset, name in ((S.PLAYER_NAME, player), (S.TOWN_NAME, town)):
        raw = name.encode("utf-16le")
        data[offset:offset + len(raw)] = raw
    checksum = -sum(struct.unpack(f"<{S.BANK_SIZE // 2}H", data)) & 0xFFFF
    struct.pack_into("<H", data, S.CHECKSUM, checksum)
    return bytes(data)


def save(first=None, second=None):
    return (first or bank()) + (second or bank()) + bytes(S.SAVE_SIZE - 2 * S.BANK_SIZE)


class SavedTown(unittest.TestCase):
    def test_both_copies_preserve_accents(self):
        report = S.validate(save(), "pe\u00f1a", "\u00e1lano")
        self.assertEqual(len(report["banks"]), 2)
        self.assertTrue(all(b["names_match"] for b in report["banks"]))

    def test_corrupt_secondary_copy_is_rejected(self):
        broken = bytearray(bank())
        broken[80] ^= 1
        with self.assertRaisesRegex(ValueError, "bank 1: invalid checksum"):
            S.validate(save(second=bytes(broken)), "pe\u00f1a", "\u00e1lano")

    def test_valid_checksum_with_wrong_name_is_rejected(self):
        with self.assertRaisesRegex(ValueError, "stored names differ"):
            S.validate(save(second=bank(player="other")), "pe\u00f1a", "\u00e1lano")

    def test_blank_and_truncated_chips_are_rejected(self):
        with self.assertRaisesRegex(ValueError, "not been set up"):
            S.validate(bytes([255]) * S.SAVE_SIZE, "x", "y")
        with self.assertRaisesRegex(ValueError, "save bytes"):
            S.validate(save()[:-1], "pe\u00f1a", "\u00e1lano")


if __name__ == "__main__":
    unittest.main()
