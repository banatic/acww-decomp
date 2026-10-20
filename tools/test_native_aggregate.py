"""Actual ROM bodies through both production aggregate dispatch directions."""
import os
import subprocess

import common as C
import diffcheck
import native
import native_aggregate
import run


def caller_guards():
    """Each audited caller copy applies, and a changed source is rejected."""
    for relative, (_digest, callees, changes) in native_aggregate.CALLERS.items():
        text = (C.SRC / relative).read_bytes().decode()
        copy = native_aggregate.caller_copy(relative, text)
        assert callees and native_aggregate.handled(relative) == set(callees), relative
        assert (copy is None) == (not changes), relative
        try:
            native_aggregate.caller_copy(relative, text + '\n')
        except ValueError:
            pass
        else:
            raise AssertionError('changed source accepted: ' + relative)
    for relative in native_aggregate.CLEAN_CALLERS:
        text = (C.ROOT / relative).read_bytes().decode()
        assert native_aggregate.clean_caller_copy(relative, text) != text, relative
        try:
            native_aggregate.clean_caller_copy(relative, text + '\n')
        except ValueError:
            pass
        else:
            raise AssertionError('changed Clean source accepted: ' + relative)
    assert native_aggregate.returns_word('main/func_020401b8.c')
    print(f'{len(native_aggregate.CALLERS)} audited aggregate caller copies and '
          f'{len(native_aggregate.CLEAN_CALLERS)} Clean ones apply and reject changed sources')


def main():
    caller_guards()
    folder = C.BUILD / 'native-aggregate-check'
    folder.mkdir(parents=True, exist_ok=True)
    runtime = C.ROOT / 'runtime'
    objects, arrays, names = [], [], []
    image = C.module_image('main')
    base = C.modules()['main']['base']
    for index, (relative, spec) in enumerate(native_aggregate.SPECS.items()):
        path = C.SRC / relative
        assert native_aggregate.return_kind(path) == spec['kind'] == index + 8
        source = C.parse_source(path)
        body = image[source.address-base:source.address-base+source.size]
        name = f'aggregate_rom_{index}'
        names.append(name)
        arrays.append(f'static const unsigned char {name}[] = {{' + ','.join(hex(b) for b in body) + '};')
        obj = folder / (path.stem + '.o')
        subprocess.run([*native.compiler(), *native.flags_for(path), '-c', str(path), '-o', str(obj)], check=True)
        objects.append(obj)
    (folder/'aggregate_rom.h').write_text('\n'.join(arrays) + '\nstatic const unsigned char *aggregate_rom[] = {' +
                                        ','.join(names) + '};\n', newline='\n')
    caller = C.ROOT/'tests/native/aggregate_caller.c'
    obj = folder/'caller.o'
    subprocess.run([*native.compiler(), *native.flags_for(caller), '-I'+str(runtime),
                    '-c', str(caller), '-o', str(obj)], check=True)
    objects.append(obj)
    scalar_source = C.SRC / native_aggregate.SCALAR_CALLER
    scalar_copy = folder/'scalar-caller.cpp'
    scalar_copy.write_text(native_aggregate.caller_copy(native_aggregate.SCALAR_CALLER,
                                                       scalar_source.read_bytes().decode()), newline='\n')
    subprocess.run([*native.compiler(), *native.flags_for(scalar_source), '-iquote', str(scalar_source.parent),
                    '-c', str(scalar_copy), '-o', str(folder/'scalar-caller.o')], check=True)
    # Compile the exact injected declaration/extractor with the Native C++ ABI.
    scalar_fixture = folder/'scalar-fixture.cpp'
    scalar_fixture.write_text('extern "C" {\n' + native_aggregate.SCALAR_DECLARATION +
                              'unsigned int aggregate_scalar_date_caller(void *p) { return native_aggregate_date_word(p); }\n}\n',
                              newline='\n')
    scalar_obj = folder/'scalar-fixture.o'
    subprocess.run([*native.compiler(), *native.flags_for(scalar_source), '-c', str(scalar_fixture),
                    '-o', str(scalar_obj)], check=True)
    objects.append(scalar_obj)
    clean_original = C.ROOT / native_aggregate.CLEAN_SOURCE
    clean_copy = folder/'clean-abi.c'
    clean_copy.write_text(native_aggregate.clean_copy(clean_original.read_bytes().decode()), newline='\n')
    subprocess.run([*diffcheck.compiler(), '-std=c11', '-O2', '-I'+str(C.INCLUDE),
                    '-I'+str(C.ROOT/'clean'), '-iquote', str(clean_original.parent),
                    '-c', str(clean_copy), '-o', str(folder/'clean-abi.o')], check=True)
    prefix = '_' if os.name == 'nt' else ''
    absolute = folder/'absolute.s'
    absolute.write_text(''.join(f'.globl {prefix}{name}\n.set {prefix}{name},{value:#x}\n' for name,value in
                               [('data_021dc7a8',0x021dc7a8),('data_021d1330',0x021d1330),('__ptmf_null',0x0213dd98)]) +
                        ('.section .note.GNU-stack,"",@progbits\n' if os.name != 'nt' else ''), newline='\n')
    obj = absolute.with_suffix('.o')
    subprocess.run([*diffcheck.compiler(), '-c', str(absolute), '-o', str(obj)], check=True)
    objects.append(obj)
    loop = folder/'loop.c'
    loop.write_text('#define main aggregate_game_main\n#include "'+(runtime/'run.c').as_posix()+'"\n', newline='\n')
    sources = [runtime/name for name in run.SOURCES if name not in ('run.c','native_run.c')]
    sources += [runtime/'native_rt.c', loop, C.ROOT/'tests/native/aggregate_dispatch.c']
    flags = ['-std=c11','-O2','-Wall','-Wextra','-fwrapv','-fno-strict-aliasing',
             '-D_CRT_SECURE_NO_WARNINGS','-D_CRT_NONSTDC_NO_WARNINGS','-I'+str(runtime),'-I'+str(folder)]
    if os.name == 'nt':
        link = ['-Wl,/SAFESEH:NO','-Wl,/DYNAMICBASE:NO','-Wl,/FIXED']
    else:
        flags += ['-D_DEFAULT_SOURCE']
        link = ['-no-pie','-Wl,-z,noexecstack','-Wl,-Ttext-segment=0x400000',
                '-Wl,--section-start=.heap_floor=0x10000000']
    exe = folder/('aggregate.exe' if os.name == 'nt' else 'aggregate')
    for mode in range(5):
        subprocess.run([*diffcheck.compiler(), *flags, f'-DAGG_TEST_CLEAN={mode}',
                        *map(str,sources), *map(str,objects), *link, '-o',str(exe)], check=True)
        subprocess.run([str(exe)], check=True, timeout=30)


if __name__ == '__main__':
    main()
