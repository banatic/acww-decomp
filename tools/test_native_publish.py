"""Guard publication copies and exercise the production recorder/replay boundary."""
import os
import subprocess
import unittest

import common as C
import diffcheck
import native
import native_publish as publish
import run


class PublicationGuards(unittest.TestCase):
    def test_rom_and_mutation(self):
        image = C.module_image('main')
        for address, size, _sha in publish.ROM_SITES:
            offset = address - C.modules()['main']['base']
            code = image[offset:offset + size]
            publish.validate_rom(code, address)
            with self.assertRaises(ValueError):
                publish.validate_rom(bytes([code[0] ^ 1]) + code[1:], address)

    def test_both_source_copies(self):
        for relative, path in [(publish.SOURCE, C.SRC / publish.SOURCE),
                               (publish.SHIFT_SOURCE, C.SRC / publish.SHIFT_SOURCE),
                               (publish.CLEAN_SOURCE, C.ROOT / publish.CLEAN_SOURCE)]:
            text = path.read_bytes().decode()
            copy = publish.translate(relative, text)
            self.assertEqual(copy.count('native_publish_word('), 2 if relative == publish.CLEAN_SOURCE else 1)
            with self.assertRaises(ValueError):
                publish.translate(relative, text + '\n')
        self.assertIsNone(publish.translate('unknown.c', ''))


def fixture():
    folder = C.BUILD / 'native-publication-check'
    folder.mkdir(parents=True, exist_ok=True)
    clean_original = C.ROOT / publish.CLEAN_SOURCE
    clean_copy = folder / 'sky.c'
    clean_copy.write_text(publish.translate(publish.CLEAN_SOURCE, clean_original.read_bytes().decode()), newline='\n')
    # u32 is unsigned long on these game headers, whereas uint32_t is unsigned
    # int on the Linux toolchain. Compile the actual Clean copy, not a typedef
    # substitute that could conceal an incompatible publication pointer.
    subprocess.run([*diffcheck.compiler(), '-std=c11', '-O2', '-Wall', '-Wextra',
                    '-Werror=incompatible-pointer-types', '-fwrapv', '-fno-strict-aliasing',
                    '-I', str(C.INCLUDE), '-I', str(C.ROOT / 'clean'), '-I', str(C.ROOT / 'runtime'),
                    '-iquote', str(clean_original.parent), '-c', str(clean_copy),
                    '-o', str(folder / 'sky.o')], check=True)
    print('Actual Clean publication copy compiles with strict pointer types')
    objects = []
    for name, relative in [('gradient', publish.SOURCE), ('shift', publish.SHIFT_SOURCE)]:
        source = folder / f'{name}.c'
        source.write_text(publish.translate(relative, (C.SRC / relative).read_bytes().decode()), newline='\n')
        obj = folder / f'{name}.o'
        subprocess.run([*native.compiler(), *native.flags_for(C.SRC / relative),
                        '-I', str(C.ROOT / 'runtime'), '-c', str(source), '-o', str(obj)], check=True)
        objects.append(str(obj))
    prefix = '_' if os.name == 'nt' else ''
    lines = ['\t.globl ' + prefix + name + '\n\t.set ' + prefix + name + ', ' + hex(address)
             for name, address in [('data_021f6f70', 0x021f6f70), ('data_021f6f74', 0x021f6f74),
                                   ('data_021f7270', 0x021f7270), ('data_021f8ab0', 0x021f8ab0),
                                   ('data_021f8b48', 0x021f8b48)]]
    if os.name != 'nt':
        lines.append('\t.section .note.GNU-stack,"",@progbits')
    absolute = folder / 'globals.s'
    absolute.write_text('\n'.join(lines) + '\n', newline='\n')
    globals_obj = folder / 'globals.o'
    subprocess.run([*diffcheck.compiler(), '-c', str(absolute), '-o', str(globals_obj)], check=True)
    runtime = C.ROOT / 'runtime'
    sources = [runtime / name for name in run.SOURCES if name not in ('run.c', 'native_run.c')]
    sources += [runtime / 'native_rt.c', C.ROOT / 'tests/native/publication_clock.c',
                C.ROOT / 'tests/native/publication_calls.c']
    flags = ['-std=c11', '-O2', '-Wall', '-Wextra', '-fwrapv', '-fno-strict-aliasing',
             '-D_CRT_SECURE_NO_WARNINGS', '-D_CRT_NONSTDC_NO_WARNINGS', '-I', str(runtime)]
    if os.name == 'nt':
        link = ['-Wl,/SAFESEH:NO', '-Wl,/DYNAMICBASE:NO', '-Wl,/FIXED']
    else:
        flags += ['-D_DEFAULT_SOURCE']
        link = ['-no-pie', '-Wl,-z,noexecstack', '-Wl,-Ttext-segment=0x400000',
                '-Wl,--section-start=.heap_floor=0x10000000']
    exe = folder / ('publication.exe' if os.name == 'nt' else 'publication')
    subprocess.run([*diffcheck.compiler(), *flags, *map(str, sources), *objects, str(globals_obj),
                    *link, '-o', str(exe)], check=True)
    subprocess.run([str(exe)], check=True, timeout=30)
    for case in ('value', 'width', 'order', 'pc', 'destination', 'missing', 'late'):
        result = subprocess.run([str(exe), case], capture_output=True, text=True, timeout=30)
        assert result.returncode == 7, (case, result.returncode, result.stdout, result.stderr)
        assert 'Rejected before publishing or copying the expected value' in result.stderr
    result = subprocess.run([str(exe), 'old-boundary'], capture_output=True, text=True, timeout=30)
    assert result.returncode == 2, (result.returncode, result.stdout, result.stderr)
    result = subprocess.run([str(exe), 'old-shift'], capture_output=True, text=True, timeout=30)
    assert result.returncode == 2 and 'irq_shift_expected' in result.stderr, (result.returncode, result.stderr)
    print('Rejected seven invalid/late publication events, old boundary ordering and a late line-shift selector')


if __name__ == '__main__':
    result = unittest.main(exit=False)
    if not result.result.wasSuccessful():
        raise SystemExit(1)
    fixture()
