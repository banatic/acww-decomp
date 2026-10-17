"""Compile, rewrite, link and execute the production Native call wrappers."""
from __future__ import annotations

import subprocess

import common as C
import diffcheck
import native
import native_profile
import objrewrite


def signal_returns(lines: list[str]) -> list[str]:
    """Trap after restores, while a resumed signal may reuse memory below ESP."""
    result, active, count = [], False, 0
    for line in lines:
        result.append(line)
        if line.endswith('_guest_return:') or line == 'native_clean_profile_return:':
            active = True
        elif active and line == '\tpopal':
            result.append('\tint3')
            active = False
            count += 1
    assert count > 0
    return result


def main() -> None:
    names = ['args', 'wide', 'void', 'signed', 'unsigned', 'double', 'struct',
             'recurse', 'tail', 'tail_target']
    names = ['probe_' + name for name in names]
    folder = C.BUILD / 'native-profile-check'
    folder.mkdir(parents=True, exist_ok=True)
    fixture = C.ROOT / 'tests/native/profile_calls.c'
    original, rewritten = folder / 'original.o', folder / 'rewritten.o'
    subprocess.run([*native.compiler(), *native.flags_for(fixture), '-O0',
                    '-fno-optimize-sibling-calls', '-DPROFILE_BODIES', '-c', str(fixture),
                    '-o', str(original)], check=True)
    saved = objrewrite.BODY
    try:
        objrewrite.BODY = set(names)
        data, to_ds = objrewrite.rewrite(original.read_bytes(), set(names), set(names), native.PREFIX)
    finally:
        objrewrite.BODY = saved
    assert not to_ds, to_ds
    rewritten.write_bytes(data)
    lines = ['\t.text']
    for index, name in enumerate(names):
        extend = {'probe_signed': 'movsbl %al, %eax', 'probe_unsigned': 'movzwl %ax, %eax'}.get(name)
        lines += native_profile.wrapper(name, index, native.PREFIX, extend)
    if not native.WINDOWS:
        lines += ['\t.section .note.GNU-stack,"",@progbits']
    assembly = folder / 'wrappers.s'
    assembly.write_text('\n'.join(lines) + '\n', newline='\n')
    obj = folder / 'wrappers.o'
    subprocess.run([*native.compiler(), '-c', str(assembly), '-o', str(obj)], check=True)
    # Compile both sides of aggregate calls with the Native ABI, including the
    # Itanium target on Windows. Link using the normal runtime toolchain.
    driver = folder / 'driver.o'
    subprocess.run([*native.compiler(), *native.flags_for(fixture), '-O2',
                    '-I', str(C.ROOT / 'runtime'), '-c', str(fixture), '-o', str(driver)], check=True)
    exe = folder / ('profile.exe' if native.WINDOWS else 'profile')
    link_flags = ['-Wl,/SAFESEH:NO'] if native.WINDOWS else ['-no-pie']
    subprocess.run([*diffcheck.compiler(), '-O2', str(driver), str(rewritten), str(obj),
                    str(C.ROOT / 'runtime/native_rt.c'), *link_flags, '-o', str(exe)], check=True)
    subprocess.run([str(exe)], check=True)
    if not native.WINDOWS:
        signal_assembly = folder / 'signal-wrappers.s'
        signal_assembly.write_text('\n'.join(signal_returns(lines)) + '\n', newline='\n')
        signal_obj = folder / 'signal-wrappers.o'
        subprocess.run([*native.compiler(), '-c', str(signal_assembly), '-o', str(signal_obj)], check=True)
        signal_driver = folder / 'signal-driver.o'
        subprocess.run([*native.compiler(), *native.flags_for(fixture), '-O2',
                        '-D_GNU_SOURCE', '-DPROFILE_SIGNAL_CHECK', '-I', str(C.ROOT / 'runtime'),
                        '-c', str(fixture), '-o', str(signal_driver)], check=True)
        signal_exe = folder / 'signal-profile'
        subprocess.run([*diffcheck.compiler(), '-O2', str(signal_driver), str(rewritten), str(signal_obj),
                        str(C.ROOT / 'runtime/native_rt.c'), *link_flags, '-o', str(signal_exe)], check=True)
        subprocess.run([str(signal_exe)], check=True)
        print('Native returns survive 16000 signals after register restoration')


if __name__ == '__main__':
    main()
