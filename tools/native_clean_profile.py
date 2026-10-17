"""Preserve registered Clean entry names while routing calls through ABI wrappers."""
from __future__ import annotations

from dataclasses import dataclass

import native_profile
import objrewrite


@dataclass(frozen=True)
class Entry:
    name: str
    index: int
    extend: str | None = None
    alias: bool = True


def rewrite(data: bytes, known: set[str], native: set[str], prefix: str,
            functions: set[str]) -> tuple[bytes, set[str]]:
    """Absolute Clean pointers retain their name, an alias to the public wrapper.

    Game references still follow the usual DS/Native rules. Restore BODY so
    other users of objrewrite in this process cannot inherit Clean renaming.
    """
    saved = objrewrite.BODY
    try:
        objrewrite.BODY = functions
        return objrewrite.rewrite(data, known | functions, native | functions, prefix)
    finally:
        objrewrite.BODY = saved


def assembly(entries: list[Entry], prefix: str) -> list[str]:
    assert len({entry.name for entry in entries}) == len(entries)
    base = entries[0].index if entries else 0
    assert [entry.index for entry in entries] == list(range(base, base + len(entries)))
    lines = ['\t.text']
    enter = prefix + 'native_clean_profile_enter'
    leave = prefix + 'native_clean_profile_return'
    # Compact entries share the register-preserving plumbing. Each stub has
    # two forced five-byte jumps, so its return entry is always public + 10.
    # Narrow-result entries keep the existing widening wrapper, including its
    # untracked path. Keeping the bulk compact prevents host data from moving
    # into the runtime's DS-address classification range.
    lines += ['\t.p2align 4', enter + ':', '\tpushal', '\tmovl %esp, %ebp',
              f'\tcmpl $0, {prefix}native_guest_enter_hook', f'\tje {enter}_plain',
              '\tandl $-16, %esp', '\tsubl $4, %esp', '\tleal 40(%ebp), %eax',
              '\tpushl %eax', '\tpushl 36(%ebp)', '\tpushl 32(%ebp)',
              f'\tcall {prefix}native_guest_enter', '\tmovl %ebp, %esp',
              '\tmovl 32(%esp), %eax', f'\tsubl ${base}, %eax',
              f'\tmovl {prefix}clean_bodies+4(,%eax,8), %edx', '\taddl $10, %edx',
              '\tmovl %edx, 36(%esp)', f'\tjmp {enter}_body',
              enter + '_plain:', '\tmovl 32(%esp), %eax', f'\tsubl ${base}, %eax',
              enter + '_body:', f'\tmovl {prefix}clean_bodies(,%eax,8), %eax',
              '\tmovl %eax, 32(%esp)', '\tpopal', '\tret',
              leave + ':', '\tpushal', '\tmovl %esp, %ebp', '\tandl $-16, %esp',
              '\tsubl $12, %esp', '\tpushl 32(%ebp)', f'\tcall {prefix}native_guest_return',
              # Replace the stub's index with the caller PC. It stays above
              # ESP throughout register restoration, even during a signal.
              '\tmovl %ebp, %esp', '\tmovl %eax, 32(%esp)', '\tpopal', '\tret']
    for entry in entries:
        if entry.extend:
            lines += native_profile.wrapper(entry.name, entry.index, prefix, entry.extend)
        else:
            public = prefix + 'native_' + entry.name
            lines += ['\t.p2align 2', f'\t.globl {public}', public + ':', '\t.byte 0x68', f'\t.long {entry.index}',
                      '\t.byte 0xe9', f'\t.long {enter} - . - 4',
                      '\t.byte 0x68', f'\t.long {entry.index}', '\t.byte 0xe9', f'\t.long {leave} - . - 4']
        if entry.alias:
            lines += [f'\t.globl {prefix}{entry.name}',
                      f'\t.set {prefix}{entry.name}, {prefix}native_{entry.name}']
    lines += ['\t.data', '\t.p2align 2', f'\t.globl {prefix}clean_bodies', f'{prefix}clean_bodies:']
    lines += [f'\t.long {prefix}native_body_{entry.name}, {prefix}native_{entry.name}'
              for entry in entries] or ['\t.long 0, 0']
    lines += [f'\t.globl {prefix}clean_body_count', f'{prefix}clean_body_count:', f'\t.long {len(entries)}']
    return lines
