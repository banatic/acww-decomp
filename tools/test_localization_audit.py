"""Synthetic archive classification and safe empty-tail import tests."""
from __future__ import annotations

import unittest

import audit_localization as A
import localize_clean as L
from test_localize_clean import bmg


class Audit(unittest.TestCase):
    def test_only_the_documented_test_actor_gets_an_unreachable_claim(self):
        message, evidence = A.usage(A.TEST_ACTOR_ARCHIVE)
        self.assertIn("retail Korean spawner", message)
        self.assertEqual(evidence["profile"], "0x7c")
        message, evidence = A.usage("/script/KOR/message/bo/ai/clo1_.bmg")
        self.assertIn("not established", message)
        self.assertIsNone(evidence)

    def test_shared_legacy_is_not_claimed_unreachable(self):
        base = bmg([b"legacy\0"], 3)
        donor = bmg([b"shared\0"], 1)
        self.assertEqual(A.classify(base, donor, True, False), "shared_legacy_archive")
        self.assertEqual(A.classify(base, donor, False, False), "unsupported_encoding")

    def test_normal_and_mapping_required(self):
        base = bmg([b"x\0\0\0"], 2)
        self.assertEqual(A.classify(base, bmg([b"word\0"], 1), False, False), "importable")
        self.assertEqual(A.classify(base, bmg([b"word\0", b"other\0"], 1), False, False),
                         "message_index_mapping_required")

    def test_only_empty_string_tail_can_be_imported(self):
        base = bmg([b"x\0\0\0", b"y\0\0\0"], 2, 4)
        donor = bmg([b"one\0", b"two\0", b"\0"], 1, 4)
        self.assertTrue(L.empty_tail_compatible(base, donor))
        self.assertEqual(A.classify(base, donor, False, True), "importable_empty_string_tail")
        self.assertEqual(A.classify(base, donor, False, False), "message_index_mapping_required")
        self.assertIsNone(L.convert_bmg(base, donor, {}))
        result = L.convert_bmg(base, donor, {}, allow_empty_tail=True)
        size, count, entry = L.bmg_shape(result)
        self.assertEqual((count, entry), (2, 4))
        self.assertIn(b"o\0n\0e\0\0\0", result[32 + size + 8:])
        self.assertIn(b"t\0w\0o\0\0\0", result[32 + size + 8:])

    def test_never_trims_a_nonempty_extra_entry(self):
        base = bmg([b"x\0\0\0"], 2, 4)
        donor = bmg([b"one\0", b"needed\0"], 1, 4)
        self.assertFalse(L.empty_tail_compatible(base, donor))
        self.assertIsNone(L.convert_bmg(base, donor, {}, allow_empty_tail=True))

    def test_never_trims_dialogue_attributes_or_missing_donor_rows(self):
        self.assertFalse(L.empty_tail_compatible(bmg([b"x\0\0\0"], 2), bmg([b"one\0", b"\0"], 1)))
        self.assertFalse(L.empty_tail_compatible(bmg([b"x\0\0\0", b"y\0\0\0"], 2, 4), bmg([b"one\0"], 1, 4)))


if __name__ == "__main__":
    unittest.main()
