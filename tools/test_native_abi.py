"""Check bridge extents, especially signatures where parameter counts are unsafe."""
from pathlib import Path
import unittest

from native_abi import word_arguments


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

    def test_actual_math_callees(self):
        root = Path(__file__).resolve().parents[1]
        for name, count in [('FX_Div', 2), ('FX_MulFunc', 2), ('VEC_Add', 3)]:
            source = root / 'libs/NitroSDK/itcm' / (name + '.c')
            self.assertEqual(word_arguments(source.read_text(), name), count)


if __name__ == '__main__':
    unittest.main()
