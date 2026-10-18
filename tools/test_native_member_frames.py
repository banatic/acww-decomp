"""Execute the original scheduler bodies to check every audited call-site SP."""
import json
import os
import subprocess

import common as C
import diffcheck
import native_stack


OWNERS = [
    ('autoload_2', 0x020ee834),
    ('autoload_2', 0x020ee934),
    ('autoload_2', 0x020ee964),
    ('autoload_2', 0x020ee9a0),
    ('autoload_2', 0x020eea4c),
    ('itcm', 0x01ffd14c),
    ('itcm', 0x01ffd44c),
]


def main():
    host = 'windows' if os.name == 'nt' else 'linux'
    folder = C.BUILD/'native-member-frames-check'/host
    folder.mkdir(parents=True, exist_ok=True)
    modules = C.modules()
    symbols = C.SymbolTable(modules)
    lines = ['struct Owner { unsigned address, size, extent; const unsigned char *code; };']
    entries = []
    for index, (module, address) in enumerate(OWNERS):
        spec = native_stack.FRAMES[module, address]
        fn = symbols.function(module, address)
        assert fn is not None and fn.size == spec.size
        offset = address-modules[module]['base']
        code = C.module_image(module)[offset:offset+spec.size]
        extent = native_stack.frame_extent(module, address, code)
        assert extent is not None
        lines.append(f'static const unsigned char code_{index}[] = {{'
                     + ','.join(hex(byte) for byte in code) + '};')
        entries.append(f'{{{address:#x}, {spec.size}, {extent}, code_{index}}}')
    lines.append('static const struct Owner owners[] = {' + ','.join(entries) + '};')
    (folder/'member_frames_rom.h').write_text('\n'.join(lines)+'\n', newline='\n')
    exe = folder/('probe.exe' if os.name == 'nt' else 'probe')
    link = ['-Wl,/SAFESEH:NO', '-Wl,/DYNAMICBASE:NO', '-Wl,/FIXED'] if os.name == 'nt' else ['-no-pie']
    subprocess.run([*diffcheck.compiler(), '-std=c11', '-O2',
                    '-I'+str(C.ROOT/'runtime'), '-I'+str(folder),
                    str(C.ROOT/'tests/native/member_frames.c'),
                    str(C.ROOT/'runtime/arm.c'), str(C.ROOT/'runtime/memory.c'),
                    *link, '-o', str(exe)], check=True)
    result = subprocess.run([str(exe)], capture_output=True, text=True, timeout=30)
    report = {'host': host, 'exit': result.returncode, 'stdout': result.stdout,
              'stderr': result.stderr, 'rejected_wrong_extents': []}
    assert result.returncode == 0, report
    # A different wrong extent for each owner must fail at an actual ARM call.
    # This detects an accidentally unused frame expectation in the fixture.
    for index, (module, address) in enumerate(OWNERS):
        wrong = subprocess.run([str(exe), str(index)], capture_output=True, text=True, timeout=30)
        assert wrong.returncode == 2 and 'cpu->r[13]' in wrong.stderr, wrong
        assert f'owner {address:08x}' in wrong.stderr, wrong.stderr
        report['rejected_wrong_extents'].append(f'{module}:{address:08x}')
    (folder/'result.json').write_text(json.dumps(report, indent=2)+'\n', newline='\n')
    print(result.stdout, end='')
    print('All seven deliberately wrong call-site extents rejected')


if __name__ == '__main__':
    main()
