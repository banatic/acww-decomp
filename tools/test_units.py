"""Sources of several functions (common.UNIT_HEADER).

    python tools/test_units.py

Reads a unit's header and a one-function header, and checks that tools/lint.py's rules for
units hold for every unit in src/ (its functions last address first, one ISA, one module).
"""
from __future__ import annotations

import pathlib
import tempfile
import unittest

import common as C

UNIT = """/* sample_unit: 2 functions, module ov097
 * mwccarm 1.2/base -O4,s
 * func_ov097_022a2954 @ 0x022a2954, 0x90 bytes, Thumb, emits _ZN3Obj4stepEv
 * func_ov097_022a27c0 @ 0x022a27c0, 0x3c bytes, Thumb
 */

void Obj::step() {}
int func_ov097_022a27c0(void *self) { return 0; }
"""


class Units(unittest.TestCase):
    def test_header(self):
        with tempfile.TemporaryDirectory() as d:
            path = pathlib.Path(d) / "sample_unit.cpp"
            path.write_text(UNIT, newline="\n")
            srcs = C.parse_sources(path)
            self.assertEqual([s.address for s in srcs], [0x022a2954, 0x022a27c0])
            self.assertEqual([s.object_symbol for s in srcs], ["_ZN3Obj4stepEv", "func_ov097_022a27c0"])
            self.assertEqual({(s.module, s.drop, s.opt, s.thumb) for s in srcs}, {("ov097", "1.2/base", "-O4,s", True)})
            self.assertEqual(C.parse_source(path), srcs[0])
            self.assertTrue(UNIT[C.header_end(UNIT):].startswith("\n\nvoid Obj::step"))

    def test_one_function_header(self):
        path = next(p for p in sorted((C.SRC / "main").glob("func_*.c")) if C.parse_sources(p))
        self.assertEqual(len(C.parse_sources(path)), 1)

    def test_units_in_the_tree(self):
        units = [p for p in C.SRC.glob("*/*.c*") if C.UNIT_HEADER.match(p.read_text(encoding="utf-8"))]
        self.assertTrue(units)
        for p in units:
            srcs = C.parse_sources(p)
            self.assertGreater(len(srcs), 1, p)
            self.assertEqual([s.address for s in srcs], sorted((s.address for s in srcs), reverse=True), p)
            self.assertEqual(len({s.thumb for s in srcs}), 1, p)
            self.assertEqual({s.module for s in srcs}, {p.parent.name}, p)


if __name__ == "__main__":
    unittest.main()
