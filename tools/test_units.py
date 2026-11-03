"""Sources of several functions (common.UNIT_HEADER).

    python tools/test_units.py

Reads a unit's header and a one-function header, checks that tools/lint.py's rules for units
hold for every unit in src/ (its functions last address first, one ISA, one module, each declared
before it is used), that tools/regroup.py adds the prototype a call to a function defined
further down needs, and how it settles what the files declare differently, or refuses to.
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


def one(address: int, body: str, suffix: str = ".c", emits: str | None = None) -> tuple[str, str]:
    """(file name, text) of a source of one function of ov097."""
    name = f"func_ov097_{address:08x}"
    head = (f"/* {name} @ 0x{address:08x}, 0x10 bytes, Thumb, module ov097\n * mwccarm 1.2/base -O4,s\n"
            + (f" * compiler-emitted symbol: {emits}\n" if emits else "") + " */\n\n")
    return name + suffix, head + body


class Settle(unittest.TestCase):
    """tools/regroup.py's settling of what the files declare: one declaration per name, casts
    where a file's own differed, a refusal where it would have to guess."""

    def settle(self, files: list[tuple[str, str]], pinned: frozenset = frozenset()) -> tuple[str, list[str]]:
        with tempfile.TemporaryDirectory() as d:
            (pathlib.Path(d) / "ov097").mkdir()
            srcs = []
            for name, text in files:
                path = pathlib.Path(d) / "ov097" / name
                path.write_text(text, newline="\n")
                srcs += C.parse_sources(path)
            return regroup.settle("ov097", "sample_unit", srcs, set(pinned))

    def test_one_declaration_and_casts(self):
        # two files take func_02000000's argument as an int, one as a byte: the unit declares
        # it as most did, and the third file's call converts as its own declaration did
        text, edited = self.settle([
            one(0x022a2900, "extern int func_02000000(int a);\nextern u16 data_02100000;\n\n"
                            "int func_ov097_022a2900(int x)\n{\n    return func_02000000(x) + data_02100000;\n}\n"),
            one(0x022a2910, "extern int func_02000000(int);\n\nint func_ov097_022a2910(int x)\n{\n"
                            "    return func_02000000(x + 1);\n}\n"),
            one(0x022a2920, "extern int func_02000000(unsigned char a);\nextern unsigned short data_02100000[];\n\n"
                            "int func_ov097_022a2920(int x)\n{\n    return x && func_02000000(x) & data_02100000[1];\n}\n"),
        ])
        body = text[C.header_end(text):]
        self.assertEqual(body.count("func_02000000("), 4)  # one declaration, three calls
        self.assertIn("extern int func_02000000(int);\n", body)
        self.assertIn("extern unsigned short data_02100000[];\n", body)
        self.assertIn("x && func_02000000((unsigned char) x) & data_02100000[1]", body)
        self.assertIn("func_02000000(x) + (*(u16 *) data_02100000)", body)
        self.assertEqual(sorted(edited), ["func_ov097_022a2900", "func_ov097_022a2920"])

    def test_struct_by_value(self):
        # a struct passed by value that another file names otherwise: no cast converts one
        # struct type to another, so the argument object is read as the unit's type
        callee = one(0x022a2900, "typedef struct {\n    int a;\n    int b;\n} Pair;\n\n"
                                 "void func_ov097_022a2900(int *d, Pair p)\n{\n    d[0] = p.a;\n}\n")
        text, edited = self.settle([
            callee,
            one(0x022a2910, "struct S {\n    int a;\n    int b;\n};\nextern void func_ov097_022a2900(int *d, struct S p);\n"
                            "extern struct S data_02100000;\n\nvoid func_ov097_022a2910(int *d, struct S *s)\n{\n"
                            "    func_ov097_022a2900(d, *s);\n    func_ov097_022a2900(d, data_02100000);\n}\n"),
        ])
        self.assertIn("func_ov097_022a2900(d, *(Pair *) &(*s));", text)
        self.assertIn("func_ov097_022a2900(d, *(Pair *) &data_02100000);", text)
        self.assertEqual(edited, ["func_ov097_022a2910"])
        self.assertEqual(regroup.aggregate_typedefs({"Pair": "typedef struct { int a; } Pair;",
                                                     "PairP": "typedef struct { int a; } *PairP;",
                                                     "Num": "typedef int Num;"}), {"Pair"})
        with self.assertRaises(regroup.Refused) as e:
            self.settle([callee, one(0x022a2910, "extern void func_ov097_022a2900(int *d, int p);\n\n"
                                                 "void func_ov097_022a2910(int *d)\n{\n    func_ov097_022a2900(d, 1);\n}\n")])
        self.assertIn("takes Pair, its file said int", str(e.exception))

    def test_types_renamed_in_c(self):
        # a type of one name defined two ways: the later file's (the lower address) is renamed
        text, _ = self.settle([
            one(0x022a2900, "typedef struct {\n    int a;\n} Obj;\n\nint func_ov097_022a2900(Obj *o)\n{\n    return o->a;\n}\n"),
            one(0x022a2910, "typedef struct {\n    char a;\n} Obj;\n\nint func_ov097_022a2910(Obj *o)\n{\n    return o->a;\n}\n"),
        ])
        self.assertIn("} Obj_022a2900;", text)
        self.assertIn("int func_ov097_022a2900(Obj_022a2900 *o)", text)
        self.assertIn("int func_ov097_022a2910(Obj *o)", text)

    def test_refusals(self):
        plain = one(0x022a2900, "int func_ov097_022a2900(void)\n{\n    return 1;\n}\n")
        cases = {
            "applies to the whole file": [plain, one(0x022a2910, "#pragma opt_propagation off\n\n"
                                                                "int func_ov097_022a2910(void)\n{\n    return 2;\n}\n")],
            "a Native table pins it": [one(0x022a2900, "extern int func_02000000(int);\n\nint func_ov097_022a2900(void)\n"
                                                       "{\n    return func_02000000(1);\n}\n"),
                                       one(0x022a2910, "extern int func_02000000(char *);\n\nint func_ov097_022a2910(void)\n"
                                                       "{\n    return 0;\n}\n"),
                                       one(0x022a2920, "extern int func_02000000(char *);\n\nint func_ov097_022a2920(void)\n"
                                                       "{\n    return 0;\n}\n")],
            "unlike another file (C++)": [one(0x022a2900, 'extern "C" int func_02000000(int);\n\nextern "C" int '
                                                          "func_ov097_022a2900(void)\n{\n    return func_02000000(1);\n}\n", ".cpp"),
                                          one(0x022a2910, 'extern "C" int func_02000000(char *);\n\nextern "C" int '
                                                          "func_ov097_022a2910(void)\n{\n    return 0;\n}\n", ".cpp")],
            "defines as a macro": [one(0x022a2900, "#define N 4\n\nint func_ov097_022a2900(void)\n{\n    return N;\n}\n"),
                                   one(0x022a2910, "int func_ov097_022a2910(int N)\n{\n    return N;\n}\n")],
        }
        for why, files in cases.items():
            with self.assertRaises(regroup.Refused, msg=why) as e:
                self.settle(files, frozenset({"ov097/func_ov097_022a2900"}))
            self.assertIn(why, str(e.exception))

    def test_cpp_unit(self):
        # C++: extern "C" blocks keep their linkage, a member function keeps its emitted name in
        # the header, and a C function whose definition does not say extern "C" gets a prototype
        # that does
        text, edited = self.settle([
            one(0x022a2900, '#include "cpp/ov097/Obj.h"\n\nextern "C" {\nextern int func_02000000(void *);\n}\n\n'
                            "void Obj::func_ov097_022a2900()\n{\n    func_02000000(this);\n}\n",
                ".cpp", "_ZN3Obj19func_ov097_022a2900Ev"),
            one(0x022a2910, 'extern "C" {\nextern int func_02000000(void *);\nint func_ov097_022a2910(int);\n}\n\n'
                            "int func_ov097_022a2910(int a)\n{\n    return func_02000000(0) + a;\n}\n", ".cpp"),
        ])
        self.assertEqual(edited, [])
        self.assertIn(", emits _ZN3Obj19func_ov097_022a2900Ev\n", text)
        self.assertEqual(text.count("int func_02000000(void *);"), 1)
        self.assertIn('extern "C" {\nint func_ov097_022a2910(int a);\n}\n', text)


if __name__ == "__main__":
    unittest.main()
