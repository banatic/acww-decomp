"""Check bridge extents, especially signatures where parameter counts are unsafe."""
from pathlib import Path
import re
import unittest

import common as C
import native_abi
from native_abi import word_arguments

ROOT = Path(__file__).resolve().parents[1]
MATH = [('FX_Div', 2), ('FX_MulFunc', 2), ('VEC_Add', 3)]


class WordArguments(unittest.TestCase):
    def test_register_and_stack_arguments(self):
        for count in range(9):
            params = ', '.join(f'int a{i}' for i in range(count)) or 'void'
            self.assertEqual(word_arguments(f'int sample({params}) {{ return 0; }}', 'sample'), count)

    def test_pointer_forms_and_members(self):
        source = 'void sample(const Vec *v, int (&a)[3], void (*cb)(int, int)) {}'
        self.assertEqual(word_arguments(source, 'sample'), 3)
        self.assertIsNone(word_arguments('int Object::sample(int n) { return n; }', 'sample'))
        self.assertIsNone(word_arguments('struct Object { int x; int sample(int n) { return n; } };', 'sample'))

    def test_unknown_abis_remain_unknown(self):
        sources = [
            'Vec sample(int n) {}',
            'int sample(Vec value) {}',
            'int sample(long long value) {}',
            'int sample(double value) {}',
            'int sample(int n, ...) {}',
            'int sample(int (Object::*method)(int)) {}',
            'int sample(int (Object:: *method)(int)) {}',
            'asm int sample(int n) {}',
            'int sample(Alias value) {}',
            'int sample(Vec value = *global) {}',
            'int sample(Vec value = make(&global)) {}',
            'int sample(Vec value = {1, 2}) {}',
            'int sample(void);',
            'int sample(void) {}\nint sample(int n) {}',
        ]
        for source in sources:
            with self.subTest(source=source):
                self.assertIsNone(word_arguments(source, 'sample'))

    def test_hidden_results_and_scalar_results(self):
        self.assertIsNone(word_arguments('struct Vec sample(void) {}', 'sample'))
        self.assertEqual(word_arguments('struct Vec *sample(void) {}', 'sample'), 0)
        self.assertEqual(word_arguments('long long sample(int n) {}', 'sample'), 1)

    @unittest.skipUnless((ROOT / 'libs/NitroSDK').is_dir(), 'no library sources (libs/README.md)')
    def test_actual_math_callees(self):
        for name, count in MATH:
            source = ROOT / 'libs/NitroSDK/itcm' / (name + '.c')
            self.assertEqual(word_arguments(source.read_text(), name), count)

    def test_kept_library_counts(self):
        # what tools/run.py uses in a checkout without the library sources
        kept = {}
        for line in (ROOT / 'runtime/library-arguments.txt').read_text().splitlines():
            _module, _address, name, _count, words = line.split()
            kept[name] = int(words)
        for name, count in MATH:
            self.assertEqual(kept.get(name), count)


CONDITIONS = '(eq|ne|cs|hs|cc|lo|mi|pl|vs|vc|hi|ls|ge|lt|gt|le|al)?'


def stays_off_the_stack(code: bytes, address: int, thumb: bool) -> bool:
    """Whether ROM code never names the stack pointer, calls nothing and branches only inside itself."""
    import capstone  # noqa: PLC0415 (only the audit needs it)
    md = capstone.Cs(capstone.CS_ARCH_ARM, capstone.CS_MODE_THUMB if thumb else capstone.CS_MODE_ARM)
    size = 0
    for ins in md.disasm(code, address):
        size += ins.size
        mnemonic = ins.mnemonic.split('.')[0]
        if re.search(r'\b(sp|r13)\b', ins.op_str) or re.fullmatch('blx?' + CONDITIONS, mnemonic):
            return False
        if re.fullmatch('b' + CONDITIONS, mnemonic) and not address <= int(ins.op_str.lstrip('#'), 16) < address + len(code):
            return False
    return size == len(code)


class StacklessAssembly(unittest.TestCase):
    def test_audited_code(self):
        mods = C.modules()
        syms = C.symbol_table(mods)
        for (module, address), (name, size, _sha) in native_abi.STACKLESS_ASM.items():
            with self.subTest(name=name):
                sym = syms.lookup(name, module)
                self.assertIsNotNone(sym)
                self.assertEqual((sym.address, sym.size), (address, size))
                start = address - mods[module]['base']
                code = C.module_image(module)[start:start + size]
                self.assertTrue(native_abi.stackless_asm(module, address, code))
                self.assertTrue(stays_off_the_stack(code, address, sym.thumb))
                with self.assertRaises(ValueError):
                    native_abi.stackless_asm(module, address, code[:-1] + bytes([code[-1] ^ 1]))

    @unittest.skipUnless((ROOT / 'libs/NitroSDK').is_dir(), 'no library sources (libs/README.md)')
    def test_every_stackless_assembly_function(self):
        mods = C.modules()
        syms = C.symbol_table(mods)
        found = set()
        for line in (ROOT / 'runtime/library-arguments.txt').read_text().splitlines():
            module, address, name, count, words = line.split()
            if words != '-1' or int(count) > 4:
                continue
            sources = list((ROOT / 'libs').rglob(name + '.c'))
            if len(sources) != 1 or not re.search(r'\basm\b', sources[0].read_text(errors='replace')):
                continue
            sym = syms.lookup(name, module)
            if sym is None:
                continue
            start = sym.address - mods[module]['base']
            if stays_off_the_stack(C.module_image(module)[start:start + sym.size], sym.address, sym.thumb):
                found.add((module, sym.address))
        self.assertEqual(found, set(native_abi.STACKLESS_ASM))


if __name__ == '__main__':
    unittest.main()
