"""Sources of several functions (common.UNIT_HEADER).

    python tools/test_units.py

Reads a unit's header and a one-function header, checks that tools/lint.py's rules for units
hold for every unit in src/ (its functions last address first, one ISA, one module, each declared
before it is used), that tools/regroup.py adds the prototype a call to a function defined
further down needs, and how it settles what the files declare differently, or refuses to; and
that tools/native.py compiles a unit for the PC with each call to one of its functions going to
that function's entry (none folded into its caller), and reads the unit as declared.
"""
from __future__ import annotations

import pathlib
import re
import subprocess
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
        # a call that starts an indented line of a condition is not the definition
        body = ("\nint g(int a);\n\nint f(int a)\n{\n    if (a != 0 ||\n        g(a) != 0 || g(a + 1) != 0) {\n"
                "        return 1;\n    }\n    return 0;\n}\n\nint g(int a)\n{\n    return a;\n}\n")
        self.assertEqual(C.unit_definition(body, "g").start(), body.index("int g(int a)\n{"))
        self.assertEqual(C.function_span(body, "g")[0], body.index("int g(int a)\n{"))

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

    def test_declared_name(self):
        for decl, name in [("extern void (*data_02100000[])(int);", "data_02100000"),
                           ("extern BOOL (*hook)(u32 size);", "hook"), ("extern void (Obj::*__ptmf_null)();", "__ptmf_null"),
                           ("int f(void (*cb)(int));", "f"), ("extern u8 data_02100000[4];", "data_02100000")]:
            self.assertEqual(regroup.declared_name(decl), name, decl)

    def test_several_declarators(self):
        self.assertEqual(regroup.split_declarators("extern struct S *a, b, c[4];\n"),
                         ["extern struct S *a;\n", "extern struct S b;\n", "extern struct S c[4];\n"])
        for kept in ("int a, b;\n", "extern int a = 1, b;\n", "extern int f(int), g;\n",
                     "extern int a, b; // the pair\n", 'extern "C" int a, b;\n'):
            self.assertIsNone(regroup.split_declarators(kept), kept)
        text, _ = self.settle([
            one(0x022a2900, "extern int data_02100000, data_02100004;\n\nint func_ov097_022a2900(void)\n{\n"
                            "    return data_02100000 + data_02100004;\n}\n"),
            one(0x022a2910, "extern int data_02100004;\n\nint func_ov097_022a2910(void)\n{\n    return data_02100004;\n}\n"),
        ])
        self.assertEqual(text.count("extern int data_02100004;\n"), 1)
        self.assertIn("extern int data_02100000;\n", text)

    def test_c_function_in_cpp(self):
        # C++: a C function declared with other pointer types is one function, cast to as in C;
        # one declared with another number type is refused
        text, edited = self.settle([
            one(0x022a2900, 'extern "C" int func_02000000(struct A *a);\n\nextern "C" int func_ov097_022a2900(struct A *a)\n'
                            "{\n    return func_02000000(a);\n}\n", ".cpp"),
            one(0x022a2910, 'extern "C" int func_02000000(struct B *);\n\nextern "C" int func_ov097_022a2910(struct B *b)\n'
                            "{\n    return func_02000000(b);\n}\n", ".cpp"),
            one(0x022a2920, 'extern "C" int func_02000000(struct A *);\n\nextern "C" int func_ov097_022a2920(struct A *a)\n'
                            "{\n    return func_02000000(a);\n}\n", ".cpp"),
        ])
        self.assertIn("return func_02000000((struct A *) b);", text)
        self.assertEqual(edited, ["func_ov097_022a2910"])
        with self.assertRaises(regroup.Refused):
            self.settle([
                one(0x022a2900, 'extern "C" int func_02000000(int a);\n\nextern "C" int func_ov097_022a2900(void)\n'
                                "{\n    return func_02000000(1);\n}\n", ".cpp"),
                one(0x022a2910, 'extern "C" int func_02000000(char a);\n\nextern "C" int func_ov097_022a2910(void)\n'
                                "{\n    return func_02000000(1);\n}\n", ".cpp"),
            ])

    def test_runs_end_at_a_gap(self):
        # 0x022a2920-0x022a2930 is code no source defines: the run ends before it
        with tempfile.TemporaryDirectory() as d:
            (pathlib.Path(d) / "ov097").mkdir()
            for address in (0x022a2900, 0x022a2910, 0x022a2930, 0x022a2940):
                name, text = one(address, f"int func_ov097_{address:08x}(void)\n{{\n    return 0;\n}}\n")
                (pathlib.Path(d) / "ov097" / name).write_text(text, newline="\n")
            old, C.SRC = C.SRC, pathlib.Path(d)
            try:
                found = [[s.address for s in r] for r in regroup.runs("ov097")]
            finally:
                C.SRC = old
        self.assertEqual(found, [[0x022a2900, 0x022a2910], [0x022a2930, 0x022a2940]])

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



# A unit compiled for the PC (tools/native.py): each function called through its entry
NATIVE_UNIT = {".c": """/* sample_unit: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02000050 @ 0x02000050, 0x10 bytes, Thumb
 * func_02000040 @ 0x02000040, 0x10 bytes, Thumb
 * func_02000030 @ 0x02000030, 0x10 bytes, Thumb
 * func_02000020 @ 0x02000020, 0x10 bytes, Thumb
 * func_02000010 @ 0x02000010, 0x10 bytes, Thumb
 * func_02000000 @ 0x02000000, 0x10 bytes, Thumb
 */

int func_02000000(int unused, int b);
int func_02000010(void);
int func_02000030(unsigned short *p);

int func_02000050(int a, int b)
{
    return func_02000000(a, b) + 1;
}

void func_02000040(unsigned short *p)
{
    func_02000030(p);
}

int func_02000030(unsigned short *p)
{
    return *p == 0x1000;
}

int func_02000020(void)
{
    return func_02000010() + 1;
}

int func_02000010(void)
{
    return 3;
}

int func_02000000(int unused, int b)
{
    return b;
}
""", ".cpp": """/* sample_unit: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02000020 @ 0x02000020, 0x10 bytes, Thumb
 * func_02000010 @ 0x02000010, 0x10 bytes, Thumb, emits _ZN3Obj13func_02000010Ev
 */

struct Obj {
    int func_02000010();
};

extern "C" int func_02000020(Obj *o)
{
    return o->func_02000010() + 1;
}

int Obj::func_02000010()
{
    return 3;
}
"""}


class NativeUnit(unittest.TestCase):
    def calls(self, suffix: str) -> dict[str, set[str]]:
        """The names each function of the sample unit's Native object refers to in its code."""
        import native
        with tempfile.TemporaryDirectory() as d:
            path = pathlib.Path(d) / f"sample_unit{suffix}"
            path.write_text(NATIVE_UNIT[suffix], newline="\n")
            obj = path.with_suffix(".o")
            subprocess.run([*native.compiler(), "-c", *native.flags_for(path), str(path), "-o", str(obj)], check=True)
            tool = str(native.LLVM / "llvm-objdump.exe") if native.WINDOWS else "objdump"
            out = subprocess.run([tool, "-dr", str(obj)], capture_output=True, text=True, check=True).stdout
        found: dict[str, set[str]] = {}
        here = None
        for line in out.splitlines():
            m = re.match(r"^[0-9a-f]+ <(\S+)>:$", line)
            if m:
                here = found.setdefault(m.group(1)[len(native.PREFIX):], set())
            elif here is not None and (r := re.search(r"(?:IMAGE_REL_I386|R_386)_\w+\s+(\S+)$", line)):
                here.add(r.group(1)[len(native.PREFIX):])
        return found

    def test_calls_in_a_unit_go_to_the_callee(self):
        # The runtime may send any of these functions to its Reference or Clean code (at its
        # entry): a caller must not have taken in what its callee computes. A void function
        # that tests a value leaves the result in r0 for a caller through a pointer; a call to a
        # function that returns a constant is still a call.
        calls = self.calls(".c")
        self.assertIn("func_02000030", calls["func_02000040"])
        self.assertIn("func_02000010", calls["func_02000020"])
        self.assertIn("func_02000000", calls["func_02000050"])
        calls = self.calls(".cpp")
        self.assertIn("_ZN3Obj13func_02000010Ev", calls["func_02000020"])

    def test_struct_results(self):
        # the functions that return a structure by value (Native keeps their callers Reference)
        import native
        text = ("typedef struct {\n    int x;\n} S;\n\nS g(void);\nint k(int);\n\nint f(int a)\n{\n"
                "    if (a) {\n        a++;\n    }\n    return;\n}\n\nint h(void)\n{\n    return k(1);\n}\n\nint n(void)\n{\n"
                "    return k(2);\n}\n")
        self.assertEqual(native.struct_results(text), [])
        self.assertEqual(native.struct_results(text + "\nint m(void)\n{\n    return g().x;\n}\n"), ["g"])


if __name__ == "__main__":
    unittest.main()
