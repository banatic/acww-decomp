"""Block-scope statics at the ROM's addresses (tools/native_statics.py).

    python tools/test_native_statics.py

Checks that every pinned entry is still what the ROM and the mwccarm objects give (needs
MWCC_ROOT), that each PC copy names the DS storage and nothing of its own, that a changed
source, ROM literal, address, size or image rejects the copy, and then runs the ROM's owners
and their PC copies from the same memory (tests/native/rom_statics.c).
"""
from __future__ import annotations

import copy
import json
import os
import re
import subprocess
import sys
import unittest

import common as C
import diffcheck
import native
import native_pmf_boundary as boundary
import native_statics as statics


def pc_copy(relative: str, specs: dict | None = None) -> str:
    """The PC copy native.py compiles: the member boundary's (when the source has one), then the statics."""
    source = (C.SRC / relative).read_bytes().decode()
    text = source
    if relative in boundary.specifications():
        text = boundary.checked_copy(relative, source, C.ROOT, C.modules(), C.module_image)[0]
    return statics.translate(relative, source, text, specs=specs)


class StaticsCopy(unittest.TestCase):
    def test_every_copy_names_the_rom_storage(self):
        specs = statics.specifications()
        self.assertEqual(len(specs), 8)
        self.assertEqual(sum(len(e['statics']) for e in specs.values()), 8)
        for relative, spec in specs.items():
            text = pc_copy(relative)
            for name, item in spec['statics'].items():
                self.assertIn(f'#define {name} (*(', text)
                self.assertIn(f' 0x{item["address"]}u)\n', text)
                self.assertIn(f'#undef {name}\n', text)
                self.assertIsNone(re.search(r'\bstatic\s[^;{}()]*\b' + name + r'\s*[\[=;]', statics.masked(text)),
                                  relative)
                if 'guard' in item:
                    self.assertIn(f'(unsigned int *) 0x{item["guard"]}u;', text)
            self.assertNotIn('__cxa_guard', text)

    def test_the_eight_former_private_tables(self):
        specs = statics.specifications()
        for relative, address, guard in [
                ('ov003/func_ov003_0221a244.cpp', '0223c6c4', '0223c614'),
                ('ov090/func_ov090_02299470.cpp', '02299984', '02299968'),
                ('ov102/func_ov102_0229e5b8.cpp', '0229ec18', '0229ebc4'),
                ('ov116/func_ov116_0229e5e8.cpp', '0229e948', '0229e920'),
                ('ov121/func_ov121_0229bdc0.cpp', '0229c4c8', '0229c4a0'),
                ('ov126/func_ov126_022a1b4c.cpp', '022a2208', '022a21a0'),
                ('ov133/func_ov133_0229c58c.cpp', '0229c9a8', '0229c9a0'),
                ('ov146/func_ov146_0229b004.cpp', '0229b7c4', '0229b784')]:
            (item,) = specs[relative]['statics'].values()
            self.assertEqual((item['address'], item['guard']), (address, guard), relative)
            text = pc_copy(relative)
            # the ROM's two words for each method, no PC member pointer
            self.assertIn('NativeMember<', text)
            self.assertIsNone(boundary.METHOD.search(text), relative)

    def test_rom_checks(self):
        cases = ['ov003/func_ov003_0221a244.cpp', 'ov126/func_ov126_022a1b4c.cpp', 'ov146/func_ov146_0229b004.cpp']
        specs = statics.specifications()
        for relative in cases:
            for name, item in specs[relative]['statics'].items():
                for key, message in [('address', 'literal changed'), ('literals', 'literal changed'),
                                     ('guard', 'literal changed'), ('guard_literals', 'literal changed'),
                                     ('size', 'static size|literal changed|outside'),
                                     ('rom_data_sha256', 'data changed'), ('count', 'declaration changed|initializer changed')]:
                    if key not in item:
                        continue
                    changed = copy.deepcopy(specs)
                    entry = changed[relative]['statics'][name]
                    if key in ('literals', 'guard_literals'):
                        entry[key] = [f'{int(entry[key][0][:8], 16) + 4:08x}'] + entry[key][1:]
                    elif key in ('size', 'count'):
                        entry[key] += 1
                    elif key == 'rom_data_sha256':
                        entry[key] = '0' * 64
                    else:
                        entry[key] = f'{int(entry[key], 16) + 4:08x}'
                    if key == 'size' and item['section'] == 'bss':
                        # a wrong size is a different static, which the PC copy's assertion rejects
                        text = pc_copy(relative, changed)
                        self.assertIn(f'== {entry["size"]}, "ROM static size"', text)
                        continue
                    if key == 'size':
                        message = 'data changed'
                    with self.assertRaisesRegex(ValueError, message, msg=f'{relative} {name} {key}'):
                        pc_copy(relative, changed)
            changed = copy.deepcopy(specs)
            changed[relative]['rom_sha256'] = '0' * 64
            with self.assertRaisesRegex(ValueError, 'owner body changed'):
                pc_copy(relative, changed)
            source = (C.SRC / relative).read_bytes().decode()
            with self.assertRaisesRegex(ValueError, 'source changed'):
                statics.translate(relative, source + '\n', source)

    def test_declarations(self):
        text = 'void f() {\n    static int a[] = {1, 2, 3};\n    { static struct { int x; } b = {f()}; g(b.x); }\n' \
               '    h(a[2]);\n}\n'
        d = statics.declaration(text, 'a')
        self.assertEqual((d['type'], d['count'], d['elements'], d['init']), ('int', '', 3, '{1, 2, 3}'))
        self.assertEqual(text[d['block']:], '}\n')
        d = statics.declaration(text, 'b')
        self.assertEqual((d['type'], d['count'], d['init']), ('native_static_b', None, '{f()}'))
        self.assertEqual(d['definition'], 'struct native_static_b { int x; };')
        out = statics.placed(text, 'b', {'address': '02000000', 'size': 4, 'section': 'bss',
                                         'guard': '02000004'}, True)
        self.assertIn('#define b (*(native_static_b *) 0x02000000u)', out)
        self.assertIn('g(b.x); }\n#undef b\n', out)
        for bad in ['void f() { static int a; s.a = 1; }', 'void f() { static int a; static int a; }',
                    'static int a;', 'void f() { static int a, c; }']:
            with self.assertRaises(ValueError, msg=bad):
                statics.declaration(bad, 'a')
        with self.assertRaisesRegex(ValueError, 'guard changed'):
            statics.placed('void f() { static int a = 2; }', 'a', {'address': '02000000', 'size': 4,
                                                                  'section': 'bss'}, False)


# Arguments after the object (r1-r3, then the stack), default 0: a pointer where an owner writes,
# and a direction that reaches the table.
SCRATCH = 0x023d0000
ARGUMENTS = {'ov082/func_ov082_022791b0.c': (SCRATCH, 0, 0, 0),
             'ov004/func_ov004_0223b958.cpp': (SCRATCH, 0, 0x5000, 1)}
# Former private copies the fixture cannot tell from the ROM's owner, and why.
BASELINE_SAME = {
    'ov004/func_ov004_0223b574.cpp': 'returns before its table from the fixture state',
    'ov047/func_ov047_022610cc.cpp': 'returns at its name check, before its table',
    'ov077/func_ov077_022790c4.cpp': 'returns before its tables from the fixture state',
    'ov070/func_ov070_02279820.c': 'its static is read-only data equal to the image',
    'ov073/func_ov073_02278f4c.c': 'its static is read-only data equal to the image',
}
# Guard words a source declares extern (in the overlay's .bss too), cleared with its statics.
EXTERN_GUARDS = {'ov103/func_ov103_0229df14.cpp': ['0229e340']}


def fixture(relatives: list[str], baseline: bool = False) -> list[str]:
    """Run each owner's ROM body and PC copy through tests/native/rom_statics.c; the failures.

    With `baseline`, the PC copy is the one without the statics at the ROM's addresses (the
    member boundary's alone), which must fail.
    """
    host = 'windows' if os.name == 'nt' else 'linux'
    folder = C.BUILD / 'native-statics-check' / (host + ('-baseline' if baseline else ''))
    folder.mkdir(parents=True, exist_ok=True)
    flags = ['-std=c11', '-O2', '-Wall', '-Wextra', '-fwrapv', '-fno-strict-aliasing', '-D_CRT_SECURE_NO_WARNINGS',
             '-I' + str(C.ROOT / 'runtime')]
    if os.name == 'nt':
        link = ['-Wl,/SAFESEH:NO', '-Wl,/DYNAMICBASE:NO', '-Wl,/FIXED']
    else:
        flags.append('-D_DEFAULT_SOURCE')
        link = ['-no-pie', '-pthread', '-Wl,-z,noexecstack', '-Wl,-Ttext-segment=0x400000',
                '-Wl,--section-start=.heap_floor=0x10000000']
    harness = []
    for source in [C.ROOT / 'tests/native/rom_statics.c',
                   *[C.ROOT / 'runtime' / n for n in ('arm.c', 'memory.c', 'native_os.c')]]:
        obj = folder / (source.stem + '.o')
        subprocess.run([*diffcheck.compiler(), *flags, '-c', str(source), '-o', str(obj)], check=True)
        harness.append(str(obj))
    absolute = {}
    for line in (native.OUT / 'absolute.s').read_text().splitlines():
        m = re.match(r'\s*\.set\s+(\S+),\s*(0x[0-9a-f]+)', line)
        if m:
            absolute[m[1]] = int(m[2], 16)
    failures = []
    modules = C.modules()
    symbols = C.SymbolTable(modules)
    for relative in relatives:
        path = C.SRC / relative
        parsed = C.parse_source(path)
        spec = statics.specifications()[relative]
        work = folder / relative.replace('/', '_').rsplit('.', 1)[0]
        work.mkdir(exist_ok=True)
        source = path.read_bytes().decode()
        headers = {}
        if relative in boundary.specifications():
            text, headers = boundary.checked_copy(relative, source, C.ROOT, modules, C.module_image)
        else:
            text = source
        if not baseline:
            text = statics.translate(relative, source, text)
        body = work / ('body' + path.suffix)
        body.write_text(f'#line 1 "{path.as_posix()}"\n{text}', newline='\n')
        header_root = work / 'headers'
        for name, content in headers.items():
            (header_root / name).parent.mkdir(parents=True, exist_ok=True)
            (header_root / name).write_text(content, newline='\n')
        obj = work / 'body.o'
        subprocess.run([*native.compiler(), '-I' + str(header_root), *native.flags_for(path),
                        '-I' + str(C.ROOT / 'runtime'), '-iquote', str(path.parent), '-c', str(body), '-o', str(obj)],
                       check=True)
        _, undefined = native.nm(obj)
        prefix = native.PREFIX
        places = {}
        for name in undefined:
            plain = name[len(prefix):] if name.startswith(prefix) else name
            found = {s.address for s in symbols.by_name.get(plain, [])}
            if name in absolute:
                places[name] = absolute[name]
            elif len(found) == 1 and plain not in native.HOST_NAMES:
                places[name] = found.pop()  # a Native function the whole build calls directly
        asm = ''.join(f'.globl {name}\n.set {name},{address:#x}\n' for name, address in sorted(places.items()))
        asm += f'.data\n.globl {prefix}native_owner\n{prefix}native_owner:\n.long {prefix}{parsed.object_symbol}\n'
        if os.name != 'nt':
            asm += '.section .note.GNU-stack,"",@progbits\n'
        else:
            for name in ('__cxa_guard_acquire', '__cxa_guard_release'):
                if f'__imp_{prefix}{name}' in undefined:
                    asm += f'.globl __imp_{prefix}{name}\n__imp_{prefix}{name}:\n.long {prefix}{name}\n'
        (work / 'absolute.s').write_text(asm, newline='\n')
        subprocess.run([*diffcheck.compiler(), '-c', str(work / 'absolute.s'), '-o', str(work / 'absolute.o')],
                       check=True)
        exe = work / ('check.exe' if os.name == 'nt' else 'check')
        subprocess.run([*diffcheck.compiler(), *flags, *harness, str(obj), str(work / 'absolute.o'), *link,
                        '-o', str(exe)], check=True)
        storage = []
        for item in spec['statics'].values():
            storage.append(f"{item['address']}:{item['size']}:{item['section'][0]}")
            if 'guard' in item:
                storage.append(f"{item['guard']}:4:g")
        storage += [f'{guard}:4:g' for guard in EXTERN_GUARDS.get(relative, [])]
        # library functions the PC copy runs on the host (native.HOST_NAMES): the ROM's run in
        # the interpreter too, so that neither records them
        for name in sorted(undefined):
            name = name[len(prefix):] if name.startswith(prefix) else name
            if name in native.HOST_NAMES:
                (symbol,) = symbols.by_name[name]
                storage.append(f'{symbol.address:08x}:{symbol.size}:i')
                loaded = f"m={(C.ROM_DIR / f'{symbol.module}.bin').as_posix()}@{modules[symbol.module]['base']:08x}"
                if loaded not in storage:
                    storage.append(loaded)
        base = modules[parsed.module]['base']
        result = subprocess.run([str(exe), (C.ROM_DIR / f'{parsed.module}.bin').as_posix(), f'{base:08x}',
                                 f'{parsed.address:08x}', str(parsed.size), str(int(parsed.thumb)),
                                 *map(str, ARGUMENTS.get(relative, (0, 0, 0, 0))), *storage],
                                capture_output=True, text=True, timeout=60)
        line = f'{relative}: {result.returncode} {result.stdout.strip()}{result.stderr.strip()}'
        print(line, flush=True)
        if result.returncode != 0:
            failures.append(line)
    return failures


def coverage() -> None:
    """The pinned entries are what the ROM and the mwccarm objects give; the block-scope statics
    of the other Native sources are still in PC storage."""
    derived, members = statics.derive_all()
    pinned = statics.specifications()
    assert all(derived.get(k) == v for k, v in pinned.items()), 'runtime/native-rom-statics.json is not what the ROM gives'
    pending = sorted(derived.keys() - pinned.keys())
    assert len(pending) == 157 and len(members) == 81, (len(pending), len(members))
    specs = boundary.specifications()
    placed_by_boundary = sum(len(e.get(kind, {})) for e in specs.values() for kind in statics.BOUNDARY_KINDS)
    derived = pinned
    print(f'{len(derived)} sources with {sum(len(e["statics"]) for e in derived.values())} statics placed here, '
          f'{placed_by_boundary} by the member boundary; {len(pending)} sources keep them in PC storage')


if __name__ == '__main__':
    suite = unittest.defaultTestLoader.loadTestsFromTestCase(StaticsCopy)
    if not unittest.TextTestRunner().run(suite).wasSuccessful():
        raise SystemExit(1)
    coverage()
    owners = sorted(statics.specifications())
    failures = fixture(owners)
    assert not failures, '\n'.join(failures)
    passed = fixture(owners, baseline=True)
    passed = sorted(set(owners) - {line.split(':')[0] for line in passed})
    assert passed == sorted(set(BASELINE_SAME) & set(owners)), 'former private copies that pass: ' + ', '.join(passed)
    print(f'{len(owners)} owners agree with the ROM; {len(owners) - len(passed)} of their former private copies differ'
          + ''.join(f'; {k} does not: {BASELINE_SAME[k]}' for k in passed))
