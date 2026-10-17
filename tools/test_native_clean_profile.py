"""Execute rewritten Clean entries through their original public aliases."""
from __future__ import annotations

import subprocess

import common as C
import diffcheck
import native
import native_clean_profile as profile
import objrewrite
from test_native_profile import signal_returns


def main() -> None:
    names = ['probe_' + name for name in ['args', 'wide', 'void', 'signed', 'unsigned',
                                         'double', 'struct', 'recurse', 'tail', 'tail_target']]
    entries = [profile.Entry(name, index,
                             {'probe_signed': 'movsbl %al, %eax', 'probe_unsigned': 'movzwl %ax, %eax'}.get(name),
                             alias=name != 'probe_wide') for index, name in enumerate(names)]
    folder = C.BUILD / 'native-clean-profile-check'
    folder.mkdir(parents=True, exist_ok=True)
    fixture = C.ROOT / 'tests/native/clean_profile_calls.c'
    flags = ['-std=c11', '-ffunction-sections', '-fno-inline', '-fno-optimize-sibling-calls',
             '-I', str(C.ROOT / 'runtime')]
    original, rewritten = folder / 'original.o', folder / 'rewritten.o'
    subprocess.run([*diffcheck.compiler(), *flags, '-O0', '-DPROFILE_BODIES', '-c', str(fixture),
                    '-o', str(original)], check=True)
    saved = objrewrite.BODY
    data, to_ds = profile.rewrite(original.read_bytes(), set(), set(), native.PREFIX, set(names))
    assert objrewrite.BODY is saved
    assert to_ds <= set(names), to_ds
    rewritten.write_bytes(data)
    lines = profile.assembly(entries, native.PREFIX)
    if not native.WINDOWS:
        lines += ['\t.section .note.GNU-stack,"",@progbits']
    assembly = folder / 'wrappers.s'
    assembly.write_text('\n'.join(lines) + '\n', newline='\n')
    obj = folder / 'wrappers.o'
    subprocess.run([*diffcheck.compiler(), '-c', str(assembly), '-o', str(obj)], check=True)
    driver = folder / 'driver.o'
    aliases = [f'-Dnative_{entry.name}={entry.name}' for entry in entries if entry.alias]
    subprocess.run([*diffcheck.compiler(), *flags, *aliases, '-O2', '-c', str(fixture), '-o', str(driver)], check=True)
    exe = folder / ('clean-profile.exe' if native.WINDOWS else 'clean-profile')
    link_flags = ['-Wl,/SAFESEH:NO'] if native.WINDOWS else ['-no-pie']
    subprocess.run([*diffcheck.compiler(), '-O2', str(driver), str(rewritten), str(obj),
                    str(C.ROOT / 'runtime/native_rt.c'), *link_flags, '-o', str(exe)], check=True)
    subprocess.run([str(exe)], check=True)
    if not native.WINDOWS:
        signal_assembly = folder / 'signal-wrappers.s'
        signal_assembly.write_text('\n'.join(signal_returns(lines)) + '\n', newline='\n')
        signal_obj = folder / 'signal-wrappers.o'
        subprocess.run([*diffcheck.compiler(), '-c', str(signal_assembly), '-o', str(signal_obj)], check=True)
        signal_driver = folder / 'signal-driver.o'
        subprocess.run([*diffcheck.compiler(), *flags, *aliases, '-O2', '-D_GNU_SOURCE',
                        '-DPROFILE_SIGNAL_CHECK', '-c', str(fixture), '-o', str(signal_driver)], check=True)
        signal_exe = folder / 'signal-clean-profile'
        subprocess.run([*diffcheck.compiler(), '-O2', str(signal_driver), str(rewritten), str(signal_obj),
                        str(C.ROOT / 'runtime/native_rt.c'), *link_flags, '-o', str(signal_exe)], check=True)
        subprocess.run([str(signal_exe)], check=True)
        print('Clean returns survive 16007 signals after register restoration')


if __name__ == '__main__':
    main()
