"""Test remaining member-pointer copy mechanics and the actual ARM Pair caller."""
import hashlib
import copy
import os
import re
import subprocess
import unittest
from unittest.mock import patch
from pathlib import Path

import common as C
import diffcheck
import native
import native_pmf_boundary as boundary


class BoundaryCopy(unittest.TestCase):
    def test_retained_storage_requires_original_owner_literals(self):
        relative = 'ov147/func_ov147_0229a634.cpp'
        source = (C.SRC/relative).read_bytes().decode()
        specs = boundary.specifications()
        for key in ('address', 'guard_address', 'table_literal', 'guard_literal'):
            changed = copy.deepcopy(specs)
            entry = changed[relative]['retained_storage']['PMFs']
            entry[key] = f'{int(entry[key], 16) + 4:08x}'
            with self.assertRaisesRegex(ValueError, 'storage literal changed'):
                boundary.checked_copy(relative, source, C.ROOT, C.modules(), C.module_image, specs=changed)
        changed = copy.deepcopy(specs)
        changed[relative]['retained_storage']['PMFs']['count'] = 4
        with self.assertRaisesRegex(ValueError, 'array size changed'):
            boundary.checked_copy(relative, source, C.ROOT, C.modules(), C.module_image, specs=changed)
        changed = copy.deepcopy(specs)
        changed[relative]['retained_storage']['PMFs']['pointer_literals'] = ['0229a698']
        with self.assertRaisesRegex(ValueError, 'Invalid shared member storage'):
            boundary.checked_copy(relative, source, C.ROOT, C.modules(), C.module_image, specs=changed)

    def test_keyed_tables_require_rom_data_and_exact_layout(self):
        relative = 'ov051/func_ov051_022604a8.cpp'
        source = (C.SRC/relative).read_bytes().decode()
        specs = boundary.specifications()
        for key, value, error in [('address', '02261890', 'table literal changed'),
                                  ('count', 13, 'Invalid keyed member table'),
                                  ('stride', 16, 'Invalid keyed member table')]:
            changed = copy.deepcopy(specs)
            changed[relative]['keyed_tables']['table'][key] = value
            with self.assertRaisesRegex(ValueError, error):
                boundary.checked_copy(relative, source, C.ROOT, C.modules(), C.module_image, specs=changed)
        changed = copy.deepcopy(specs)
        changed[relative]['keyed_tables']['table']['keys'][0] ^= 1
        with self.assertRaisesRegex(ValueError, 'ROM keys changed'):
            boundary.checked_copy(relative, source, C.ROOT, C.modules(), C.module_image, specs=changed)
        data = bytearray(C.module_image('ov051'))
        offset = 0x0226188c - C.modules()['ov051']['base']
        data[offset] ^= 1
        with self.assertRaisesRegex(ValueError, 'ROM data changed'):
            boundary.checked_copy(relative, source, C.ROOT, C.modules(), lambda module: bytes(data), specs=specs)

    def test_shared_storage_requires_rom_aliases_and_exact_declarations(self):
        relative = 'ov147/func_ov147_0229942c.cpp'
        source = (C.SRC/relative).read_bytes().decode()
        specs = boundary.specifications()
        for key in ('address', 'guard_address'):
            changed = copy.deepcopy(specs)
            entry = changed[relative]['shared_storage']['t0']
            entry[key] = f'{int(entry[key], 16) + 4:08x}'
            with self.assertRaisesRegex(ValueError, 'storage literal changed'):
                boundary.checked_copy(relative, source, C.ROOT, C.modules(), C.module_image, specs=changed)
        changed = copy.deepcopy(specs)
        changed[relative]['shared_storage']['t0']['count'] += 1
        with self.assertRaisesRegex(ValueError, 'array size changed'):
            boundary.checked_copy(relative, source, C.ROOT, C.modules(), C.module_image, specs=changed)
        data = bytearray(C.module_image('ov147'))
        at = int(specs[relative]['shared_storage']['t0']['pointer_literals'][0], 16) - C.modules()['ov147']['base']
        data[at] ^= 4
        with self.assertRaisesRegex(ValueError, 'alias changed'):
            boundary.checked_copy(relative, source, C.ROOT, C.modules(), lambda module: bytes(data), specs=specs)

    def test_rom_tables_and_constants_require_rom_literals_and_data(self):
        relative = 'main/func_02005338.cpp'
        source = (C.SRC/relative).read_bytes().decode()
        specs = boundary.specifications()
        boundary.checked_copy(relative, source, C.ROOT, C.modules(), C.module_image, specs=specs)
        for key, value, error in [('table_literal', '02005440', 'table literal changed'),
                                  ('guard_literal', '02005448', 'guard literal changed'),
                                  ('count', 3, 'declaration changed'),
                                  ('address', '021c0010', 'Invalid ROM member table')]:
            changed = copy.deepcopy(specs)
            changed[relative]['rom_tables']['data_021c0008'][key] = value
            with self.assertRaisesRegex(ValueError, error):
                boundary.checked_copy(relative, source, C.ROOT, C.modules(), C.module_image, specs=changed)
        changed = copy.deepcopy(specs)
        changed[relative]['rom_constants']['data_020d747c']['words'][1] = 2
        with self.assertRaisesRegex(ValueError, 'ROM member constant changed'):
            boundary.checked_copy(relative, source, C.ROOT, C.modules(), C.module_image, specs=changed)
        changed = copy.deepcopy(specs)
        changed[relative]['rom_constants']['data_020d7480'] = {'words': [0, 0]}
        with self.assertRaisesRegex(ValueError, 'constant declaration changed'):
            boundary.checked_copy(relative, source, C.ROOT, C.modules(), C.module_image, specs=changed)
        data = bytearray(C.module_image('main'))
        data[0x020d747c - C.modules()['main']['base']] ^= 2
        with self.assertRaisesRegex(ValueError, 'ROM member constant changed'):
            boundary.checked_copy(relative, source, C.ROOT, C.modules(), lambda module: bytes(data), specs=specs)

    def test_written_keys_must_equal_rom_keys(self):
        relative = 'ov049/func_ov049_02261848.cpp'
        source = (C.SRC/relative).read_bytes().decode()
        changed = source.replace('{0x04, data_ov049_022631d0}', '{0x05, data_ov049_022631d0}')
        self.assertNotEqual(changed, source)
        specs = copy.deepcopy(boundary.specifications())
        specs[relative]['source_sha256'] = hashlib.sha256(changed.encode()).hexdigest()
        with self.assertRaisesRegex(ValueError, 'initializer rows changed'):
            boundary.checked_copy(relative, changed, C.ROOT, C.modules(), C.module_image, specs=specs)

    def test_all_audited_inputs_and_copies(self):
        specs = boundary.specifications()
        self.assertEqual(len(specs), 261)
        headers = 0
        for relative in specs:
            original = (C.SRC / relative).read_bytes().decode()
            translated, copies = boundary.checked_copy(relative, original, C.ROOT, C.modules(),
                                                       C.module_image, specs=specs)
            self.assertNotIn('::*', translated)
            if not copies:
                self.assertNotEqual(original, translated)
            headers += bool(copies)
            with self.assertRaisesRegex(ValueError, 'source changed'):
                boundary.checked_copy(relative, original + '\n', C.ROOT, C.modules(), C.module_image, specs=specs)
        self.assertEqual(headers, 3)

    def test_body_header_and_literal_changes_are_rejected(self):
        specs = boundary.specifications()
        relative = 'main/func_02027460.cpp'
        spec = specs[relative]
        original = (C.SRC/relative).read_bytes().decode()
        data = bytearray(C.module_image('main'))
        offset = int(spec['address'], 16) - C.modules()['main']['base']
        data[offset] ^= 1
        with self.assertRaisesRegex(ValueError, 'ROM body changed'):
            boundary.checked_copy(relative, original, C.ROOT, C.modules(), lambda module: bytes(data), specs=specs)
        data[offset] ^= 1
        constant = next(iter(spec['constants'].values()))
        offset = int(constant['literal_addresses'][0], 16) - C.modules()['main']['base']
        data[offset] ^= 1
        with self.assertRaisesRegex(ValueError, 'ROM constant changed'):
            boundary.checked_copy(relative, original, C.ROOT, C.modules(), lambda module: bytes(data), specs=specs)
        actual_read = Path.read_bytes
        def modified(path):
            raw = actual_read(path)
            return raw + b'\n' if path.name == 'Base_02027460.h' else raw
        with patch.object(Path, 'read_bytes', modified):
            with self.assertRaisesRegex(ValueError, 'header changed'):
                boundary.checked_copy(relative, original, C.ROOT, C.modules(), C.module_image, specs=specs)

    def test_named_and_multiple_declarations(self):
        source = ('typedef int (Object::*Read)(int index);\n'
                  'typedef void (Object::*Write)(unsigned short *item);\n'
                  'extern void (Object::*table[3])();\n'
                  'auto p = reinterpret_cast<void (Object::**)()>(data);\n')
        copy = boundary.copy(source, {})
        self.assertIn('NativeMember<Object, int, int> Read', copy)
        self.assertIn('NativeMember<Object, void, unsigned short *> Write', copy)
        self.assertIn('NativeMember<Object, void> table[3]', copy)
        self.assertIn('reinterpret_cast<NativeMember<Object, void> *>(data)', copy)

    def test_constants_require_exact_inventory(self):
        source = 'typedef void (Object::*Callback)(); Callback a = &Object::method;'
        with self.assertRaisesRegex(ValueError, 'Missing audited'):
            boundary.copy(source, {})
        with self.assertRaisesRegex(ValueError, 'Unused audited'):
            boundary.copy(source, {'Object::method': (0x02012341, -32), 'Object::other': (4, 1)})
        self.assertIn('NativeMember<Object, void>{0x02012341u, -32}',
                      boundary.copy(source, {'Object::method': (0x02012341, -32)}))

    def test_no_implicit_aggregate_abi(self):
        with self.assertRaisesRegex(ValueError, 'Missing ARM Pair-return'):
            boundary.copy('Pair (UnkStruct_02013948::*cb)(void *, int);', {})
        with self.assertRaisesRegex(ValueError, 'Aggregate member result'):
            boundary.copy('Pair (Other::*cb)();', {})

    def test_array_call_must_be_explicit(self):
        source = 'void f(void (Object::*pmf)()) { (self->arr[i].*pmf)(); }'
        with self.assertRaisesRegex(ValueError, 'Untranslated object'):
            boundary.copy(source, {})
        self.assertIn('((&self->arr[i])->*pmf)()', boundary.copy(source, {}, array_receiver=True))


def pair_fixture():
    folder = C.BUILD / 'native-member-pair-check'
    folder.mkdir(parents=True, exist_ok=True)
    source = C.SRC / 'main/func_02013948.cpp'
    raw = source.read_bytes()
    assert hashlib.sha256(raw).hexdigest() == 'd9d32c706f7f0db217bdc8630e8802fc9f047735cc94e3f9a18a57d236a98183'
    parsed = C.parse_source(source)
    image = C.module_image('main')
    base = C.modules()['main']['base']
    rom = image[parsed.address-base:parsed.address-base+parsed.size]
    assert hashlib.sha256(rom).hexdigest() == '7a90b3cade5073b7da2a8cd35322cdf9df5fc489283705294ae4f010c9ea363f'
    # The consumer's literal is the RAM table, not a ROM table to read directly.
    assert int.from_bytes(rom[-4:], 'little') == 0x021c1914
    initializer_raw = (C.SRC / 'main/__sinit_020c4270.c').read_bytes()
    assert hashlib.sha256(initializer_raw).hexdigest() == 'a3628a170cb7d415762be90123859de8262b3f98e0d31404e26f4ee5357f7e55'
    initializer = initializer_raw.decode()
    assignments = {}
    for match in re.finditer(r'data_([0-9a-f]{8})\[(\d+)\] = data_([0-9a-f]{8});', initializer):
        assignments[int(match[1], 16) + 8 * int(match[2])] = int(match[3], 16)
    targets = [0x02012a4d, 0x020129c1, 0x020128cd, 0x02012879, 0x02012749, 0x020126d1, 0x020125bd]
    for index, target in enumerate(targets):
        at = assignments[0x021c1914 + index * 0x40 + 8] - base
        assert image[at:at+8] == target.to_bytes(4, 'little') + bytes(4)
    header = folder / 'member_pair_rom.h'
    header.write_text('static const unsigned char member_pair_rom[] = {' +
                      ','.join(hex(b) for b in rom) + '};\n'
                      'static const unsigned int member_pair_targets[] = {' +
                      ','.join(hex(t) for t in targets) + '};\n', newline='\n')
    copy = folder / 'caller.cpp'
    translated, headers = boundary.checked_copy('main/func_02013948.cpp', raw.decode(), C.ROOT,
                                               C.modules(), C.module_image)
    assert not headers
    copy.write_text(translated +
                    '\nstatic_assert(sizeof(Entry)==0x40,"ROM table stride");\n'
                    'static_assert(__builtin_offsetof(Entry,pmf)==8,"ROM member offset");\n'
                    'static_assert(sizeof(Pair)==8,"ROM hidden result");\n', newline='\n')
    obj = copy.with_suffix('.o')
    subprocess.run([*native.compiler(), *native.flags_for(source), '-I'+str(C.ROOT/'runtime'),
                    '-c', str(copy), '-o', str(obj)], check=True)
    prefix = '_' if os.name == 'nt' else ''
    absolute = folder / 'absolute.s'
    absolute.write_text(f'.globl {prefix}data_021c1914\n.set {prefix}data_021c1914,0x021c1914\n' +
                        ('.section .note.GNU-stack,"",@progbits\n' if os.name != 'nt' else ''), newline='\n')
    absolute_obj = absolute.with_suffix('.o')
    subprocess.run([*diffcheck.compiler(), '-c', str(absolute), '-o', str(absolute_obj)], check=True)
    flags = ['-std=c11', '-O2', '-Wall', '-Wextra', '-fwrapv', '-fno-strict-aliasing',
             '-D_CRT_SECURE_NO_WARNINGS', '-I'+str(C.ROOT/'runtime'), '-I'+str(folder)]
    if os.name == 'nt':
        link = ['-Wl,/SAFESEH:NO', '-Wl,/DYNAMICBASE:NO', '-Wl,/FIXED']
    else:
        flags += ['-D_DEFAULT_SOURCE']
        link = ['-no-pie', '-pthread', '-Wl,-z,noexecstack', '-Wl,-Ttext-segment=0x400000',
                '-Wl,--section-start=.heap_floor=0x10000000']
    exe = folder / ('pair.exe' if os.name == 'nt' else 'pair')
    subprocess.run([*diffcheck.compiler(), *flags, str(C.ROOT/'tests/native/member_pair.c'),
                    *[str(C.ROOT/'runtime'/p) for p in ('arm.c', 'memory.c', 'native_os.c')],
                    str(obj), str(absolute_obj), *link, '-o', str(exe)], check=True)
    subprocess.run([str(exe)], check=True, timeout=30)


def register_fixture():
    folder = C.BUILD / 'native-member-register-check'
    folder.mkdir(parents=True, exist_ok=True)
    relative = 'main/func_0201f40c.cpp'
    source = C.SRC / relative
    translated, headers = boundary.checked_copy(relative, source.read_bytes().decode(), C.ROOT,
                                               C.modules(), C.module_image)
    assert not headers
    copy = folder / 'caller.cpp'
    copy.write_text(translated + '\nstatic_assert(sizeof(UnkStruct_0201f40c)==0x130,"ROM object size");\n',
                    newline='\n')
    objects = []
    for path, original, extra in [(copy, source, []), (C.SRC/'main/func_020819bc.c',
                                   C.SRC/'main/func_020819bc.c', ['-Dfunc_020819bc=native_flag_body'])]:
        obj = folder / (path.stem + '.o')
        subprocess.run([*native.compiler(), *native.flags_for(original), '-I'+str(C.ROOT/'runtime'),
                        *extra, '-c', str(path), '-o', str(obj)], check=True)
        objects.append(obj)
    image = C.module_image('main')
    base = C.modules()['main']['base']
    arrays = []
    for path, name in [(source, 'member_register_rom'), (C.SRC/'main/func_020819bc.c', 'member_flag_rom')]:
        parsed = C.parse_source(path)
        body = image[parsed.address-base:parsed.address-base+parsed.size]
        arrays.append(f'static const unsigned char {name}[] = {{' + ','.join(hex(b) for b in body) + '};')
    (folder/'member_register_rom.h').write_text('\n'.join(arrays)+'\n', newline='\n')
    prefix = '_' if os.name == 'nt' else ''
    absolute = folder/'absolute.s'
    absolute.write_text(''.join(f'.globl {prefix}data_{value:08x}\n.set {prefix}data_{value:08x},{value:#x}\n'
                                for value in (0x021c252c, 0x021c255c, 0x021c258c, 0x021c2544)) +
                        ('.section .note.GNU-stack,"",@progbits\n' if os.name != 'nt' else ''), newline='\n')
    obj = absolute.with_suffix('.o')
    subprocess.run([*diffcheck.compiler(), '-c', str(absolute), '-o', str(obj)], check=True)
    objects.append(obj)
    flags = ['-std=c11', '-O2', '-Wall', '-Wextra', '-fwrapv', '-fno-strict-aliasing',
             '-D_CRT_SECURE_NO_WARNINGS', '-I'+str(C.ROOT/'runtime'), '-I'+str(folder)]
    if os.name == 'nt':
        link = ['-Wl,/SAFESEH:NO', '-Wl,/DYNAMICBASE:NO', '-Wl,/FIXED']
    else:
        flags += ['-D_DEFAULT_SOURCE']
        link = ['-no-pie', '-pthread', '-Wl,-z,noexecstack', '-Wl,-Ttext-segment=0x400000',
                '-Wl,--section-start=.heap_floor=0x10000000']
    exe = folder / ('register.exe' if os.name == 'nt' else 'register')
    subprocess.run([*diffcheck.compiler(), *flags, str(C.ROOT/'tests/native/member_register.c'),
                    *[str(C.ROOT/'runtime'/p) for p in ('arm.c', 'memory.c', 'native_os.c')],
                    *map(str, objects), *link, '-o', str(exe)], check=True)
    subprocess.run([str(exe)], check=True, timeout=30)


if __name__ == '__main__':
    suite = unittest.defaultTestLoader.loadTestsFromTestCase(BoundaryCopy)
    if not unittest.TextTestRunner().run(suite).wasSuccessful():
        raise SystemExit(1)
    pair_fixture()
    register_fixture()
