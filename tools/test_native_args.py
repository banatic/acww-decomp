"""Check tools/native_args.py: the short declarations it lets run as Native, and its ROM facts."""
import pathlib
import sys
import unittest

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import common as C  # noqa: E402
import native_args  # noqa: E402
import protos  # noqa: E402

SYMS = C.SymbolTable(C.modules())


class Harmless(unittest.TestCase):
    def test_library_result(self):
        # declared with a result, defined void: harmless for library code only
        self.assertTrue(native_args.harmless(SYMS, "main", "FX_InvA", 1, 0, True, False, "libs/NitroSDK/itcm/FX_InvA.c"))
        self.assertTrue(native_args.harmless(SYMS, "main", "FX_InvA", 1, 0, True, False, "libs"))
        self.assertFalse(native_args.harmless(SYMS, "main", "func_020ecf20", 0, 0, True, False, "src/autoload_2/x.c"))

    def test_unread_registers(self):
        # NNS_G3dGetVisAnmSet never reads r1-r3, but reads r0
        self.assertTrue(native_args.harmless(SYMS, "main", "NNS_G3dGetVisAnmSet", 1, 4, True, True, "libs"))
        self.assertFalse(native_args.harmless(SYMS, "main", "NNS_G3dGetVisAnmSet", 0, 4, True, True, "libs"))
        # no fact: kept
        self.assertFalse(native_args.harmless(SYMS, "main", "func_020778b0", 0, 2, False, False, "src/main/x.c"))
        # stack arguments are never covered
        self.assertFalse(native_args.harmless(SYMS, "main", "NNS_G3dGetVisAnmSet", 1, 5, True, True, "libs"))

    def test_entries_are_functions_and_used(self):
        used = set()
        for rel, callee, n, dn, ret, dret, drel in protos.disagreements():
            if n is None or dn is None or n >= dn:
                continue
            src = C.parse_source(C.ROOT / rel)
            sym = SYMS.lookup(callee, src.module)
            if sym is not None:
                used.add((sym.module, sym.address))
        for key in native_args.UNREAD:
            with self.subTest(entry=key):
                self.assertIsNotNone(SYMS.function(*key))
                self.assertIn(key, used, "an entry no short declaration needs")


class Audit(unittest.TestCase):
    def test_rom_facts(self):
        try:
            rom = native_args.Rom()
        except ImportError:
            self.skipTest("capstone is not installed: the ROM facts are not derived again")
        for (module, address), mask in native_args.UNREAD.items():
            with self.subTest(module=module, address=f"{address:08x}"):
                sym = SYMS.function(module, address)
                read = rom.reads(module, address | int(sym.thumb))
                self.assertEqual(mask, sum(1 << k for k in range(4) if k not in read))

    def test_reads(self):
        try:
            rom = native_args.Rom()
        except ImportError:
            self.skipTest("capstone is not installed")
        # func_020778b0 (varargs) stores r0-r3; NNSi_G3dGetBinaryBlockFromFile takes three
        for name, expected in (("func_020778b0", {0, 1, 2, 3}), ("NNSi_G3dGetBinaryBlockFromFile", {0, 1, 2}),
                               ("func_ov090_022990b8", {0})):
            sym = SYMS.by_name[name][0]
            self.assertEqual(set(rom.reads(sym.module, sym.address | int(sym.thumb))), expected, name)


class Copies(unittest.TestCase):
    def test_copies_apply_and_guard(self):
        for relative in sorted(native_args.paths()):
            with self.subTest(source=relative):
                text = (C.SRC / relative).read_bytes().decode("utf-8")
                copy = native_args.translate(relative, text)
                self.assertNotEqual(copy, text)
                with self.assertRaises(ValueError):
                    native_args.translate(relative, text + "\n")

    def test_passed_arguments(self):
        for relative, (_digest, callee, names) in native_args.PASSED.items():
            with self.subTest(source=relative):
                copy = native_args.translate(relative, (C.SRC / relative).read_bytes().decode("utf-8"))
                extra = ", ".join(f"(unsigned int) ({n})" for n in names)
                self.assertIn(extra + ")", copy)
                self.assertRegex(copy, r"extern [^;]*" + callee + r"\([^;]*unsigned int\);")

    def test_others_unchanged(self):
        self.assertIsNone(native_args.translate("main/func_02008748.c", "int x;"))


if __name__ == "__main__":
    unittest.main()
