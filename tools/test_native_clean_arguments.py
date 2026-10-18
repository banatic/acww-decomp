"""Optimized Clean bodies must retain the public entry's physical arguments."""
from pathlib import Path
import json
import subprocess

import common as C
import diffcheck
import native
import native_clean_profile as profile


def main():
    folder = C.BUILD/'native-clean-arguments-check'
    folder.mkdir(parents=True, exist_ok=True)
    fixture = C.ROOT/'tests/native/clean_argument_calls.c'
    original = fixture.read_text()
    names = ['CleanUnused', 'CleanUnusedCaller', 'CleanUnusedTail']
    lines = profile.assembly([profile.Entry(name, i) for i, name in enumerate(names)], native.PREFIX)
    if not native.WINDOWS:
        lines += ['.section .note.GNU-stack,"",@progbits']
    assembly = folder/'wrappers.s'
    assembly.write_text('\n'.join(lines)+'\n', newline='\n')
    wrapper = folder/'wrappers.o'
    subprocess.run([*diffcheck.compiler(), '-c', str(assembly), '-o', str(wrapper)], check=True)
    flags = ['-std=c11', '-O2', '-ffunction-sections', '-fno-inline', '-I'+str(C.ROOT/'runtime')]
    driver = folder/'driver.o'
    subprocess.run([*diffcheck.compiler(), *flags, '-c', str(fixture), '-o', str(driver)], check=True)
    reports = []
    for mode, text in [('baseline', original), ('separated', profile.source_copy(original))]:
        source, obj = folder/(mode+'.c'), folder/(mode+'.o')
        source.write_text(text, newline='\n')
        subprocess.run([*diffcheck.compiler(), *flags, '-DPROFILE_BODIES', '-c', str(source), '-o', str(obj)], check=True)
        rewritten, _ = profile.rewrite(obj.read_bytes(), set(), set(), native.PREFIX, set(names))
        obj.write_bytes(rewritten)
        exe = folder/(mode+('.exe' if native.WINDOWS else ''))
        link = ['-Wl,/SAFESEH:NO'] if native.WINDOWS else ['-no-pie']
        subprocess.run([*diffcheck.compiler(), str(obj), str(wrapper), str(driver),
                        str(C.ROOT/'runtime/native_rt.c'), *link, '-o', str(exe)], check=True)
        result = subprocess.run([str(exe)], capture_output=True, text=True, timeout=30)
        report = {'mode': mode, 'exit': result.returncode, 'stdout': result.stdout, 'stderr': result.stderr}
        reports.append(report)
        print(json.dumps(report), flush=True)
        if mode == 'separated':
            assert result.returncode == 0 and '0 argument mismatches' in result.stdout
        elif native.WINDOWS:
            assert result.returncode == 2
        else:
            assert result.returncode in (0, 2)
    (folder/'results.json').write_text(json.dumps(reports, indent=2)+'\n')


if __name__ == '__main__':
    main()
