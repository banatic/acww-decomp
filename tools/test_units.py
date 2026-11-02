"""Sources of several functions (common.UNIT_HEADER).

    python tools/test_units.py

Reads a unit's header and a one-function header, checks that tools/lint.py's rules for units
hold for every unit in src/ (its functions last address first, one ISA, one module, each declared
before it is used), and that tools/regroup.py adds the prototype a call to a function defined
further down needs.
"""
from __future__ import annotations

import pathlib
import tempfile
import unittest

import common as C
import regroup

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
            text = p.read_text(encoding="utf-8")
            self.assertEqual(C.undeclared_uses(text[C.header_end(text):], [s.name for s in srcs]), [], p)

    def test_used_before_declared(self):
        body = "\nvoid f2(void)\n{\n    g1(0);\n}\n\nint g1(int a)\n{\n    return a;\n}\n"
        self.assertEqual(C.undeclared_uses(body, ["f2", "g1"]), ["g1"])
        self.assertEqual(C.undeclared_uses("\nint g1(int a);\n" + body, ["f2", "g1"]), [])
        self.assertEqual(C.undeclared_uses("\nextern int g1(int a);\n" + body, ["f2", "g1"]), [])

    def test_regroup_adds_the_prototype(self):
        # the caller is at the higher address, so it comes first and calls a function below it
        files = {
            "func_ov097_022a2954.c": ("/* func_ov097_022a2954 @ 0x022a2954, 0x90 bytes, Thumb, module ov097\n"
                                      " * mwccarm 1.2/base -O4,s\n */\n\nvoid func_ov097_022a2954(void *self)\n"
                                      "{\n    func_ov097_022a27c0(self);\n}\n"),
            "func_ov097_022a27c0.c": ("/* func_ov097_022a27c0 @ 0x022a27c0, 0x3c bytes, Thumb, module ov097\n"
                                      " * mwccarm 1.2/base -O4,s\n */\n\nint func_ov097_022a27c0(void *self)\n"
                                      "{\n    return self != 0;\n}\n"),
        }
        with tempfile.TemporaryDirectory() as d:
            (pathlib.Path(d) / "ov097").mkdir()
            paths = []
            for name, text in files.items():
                paths.append(pathlib.Path(d) / "ov097" / name)
                paths[-1].write_text(text, newline="\n")
            old, C.SRC = C.SRC, pathlib.Path(d)
            try:
                dest, problems = regroup.regroup("ov097", "sample_unit", paths)
            finally:
                C.SRC = old
            text = dest.read_text()
            names = ["func_ov097_022a2954", "func_ov097_022a27c0"]
            self.assertEqual(problems, [])
            self.assertIn("\nint func_ov097_022a27c0(void *self);\n", text)
            self.assertLess(text.index("int func_ov097_022a27c0(void *self);"), text.index("void func_ov097_022a2954"))
            self.assertEqual(C.undeclared_uses(text[C.header_end(text):], names), [])
            # the Native tables pin each function by its own text, which regrouping keeps
            for name in names:
                self.assertEqual(C.function_sha256(text, name), C.function_sha256(files[name + ".c"], name))
            changed = C.function_changed(text, names[1])
            self.assertNotEqual(C.function_sha256(changed, names[1]), C.function_sha256(text, names[1]))
            self.assertEqual(C.function_sha256(changed, names[0]), C.function_sha256(text, names[0]))

    def test_function_span(self):
        text = ("/* f @ 0x02000000, 0x4 bytes, Thumb, module main\n * mwccarm 1.2/base -O4,s\n */\n\n"
                "int g(int);\n/* f(x) { in a comment */\nint f(int a)\n{\n    if (g(a)) {\n"
                "        return \"}\"[0];\n    }\n    return 0;\n}\n")
        start, end = C.function_span(text, "f")
        self.assertTrue(text[start:].startswith("int f(int a)\n{"))
        self.assertTrue(text[:end].endswith("    return 0;\n}"))
        self.assertIsNone(C.function_span(text, "h"))

    def test_tables_name_functions(self):
        # every Native table entry is a function of a source, pinned by its current text
        import native_tables
        for table, key, digest in native_tables.pinned():
            src = C.function_source(key)
            self.assertIsNotNone(src, (table, key))
            if digest is not None:
                self.assertEqual(C.pinned_sha256(key, src.path.read_text(encoding="utf-8")), digest, (table, key))


if __name__ == "__main__":
    unittest.main()
