"""Preserve registered Clean entry names while routing calls through ABI wrappers."""
from __future__ import annotations

from dataclasses import dataclass
import re
import struct

import native_profile
import objrewrite
import protos


def source_copy(text: str) -> str:
    """Keep public callees opaque before optimization, then wrap their bodies.

    Renaming an object after compilation is too late: a compiler can omit
    arguments that a visible callee ignores, although the runtime entry hook
    must observe those arguments or redirect the call to Reference instead.
    Give each registered definition its final body name in the PC copy; its
    public name remains an external declaration for calls and function pointers.
    """
    masked = protos.COMMENT.sub(lambda m: ''.join('\n' if c == '\n' else ' ' for c in m[0]), text)
    names = set(re.findall(r'^CLEAN_AS\(\w+,\s*(\w+)\)', masked, re.M))
    found = {}
    for match in protos.FUNC.finditer(masked):
        if match[2] in names and match[4] == '{':
            if match[2] in found or 'static' in match[1].split():
                raise ValueError('Ambiguous Clean entry definition: ' + match[2])
            found[match[2]] = match
    if names != found.keys():
        raise ValueError('Missing Clean entry definitions: ' + ', '.join(sorted(names - found.keys())))
    for match in sorted(found.values(), key=lambda m: m.start(), reverse=True):
        header = text[match.start(1):match.start(4)].rstrip()
        text = (text[:match.start(1)] + header + ';\n' + text[match.start(1):match.start(2)]
                + 'native_body_' + text[match.start(2):])
    return text


@dataclass(frozen=True)
class Entry:
    name: str
    index: int
    extend: str | None = None
    alias: bool = True


def definitions(data: bytes, prefix: str) -> list[tuple[str, bool]]:
    """The symbols an i386 COFF or ELF object defines, static ones included, as (plain name,
    external); COFF names without `prefix` (sections, labels) are left out."""
    found = []
    if data[:4] == b'\x7fELF':
        shoff, = struct.unpack_from('<I', data, 0x20)
        shentsize, shnum = struct.unpack_from('<HH', data, 0x2E)
        sections = [struct.unpack_from('<10I', data, shoff + i * shentsize) for i in range(shnum)]
        symtab = next(s for s in sections if s[1] == 2)
        strtab = sections[symtab[6]][4]
        for at in range(symtab[4], symtab[4] + symtab[5], 16):
            name, _, _, info, _, shndx = struct.unpack_from('<IIIBBH', data, at)
            if shndx not in (0, 0xFFF1) and info & 15 in (0, 1, 2):  # not a section or file symbol
                end = data.index(b'\0', strtab + name)
                found.append((data[strtab + name:end].decode('latin-1'), info >> 4 != 0))
        return found
    _, _, _, symptr, count, _, _ = struct.unpack_from('<HHIIIHH', data, 0)
    strings = symptr + 18 * count
    i = 0
    while i < count:
        raw = data[symptr + 18 * i:symptr + 18 * (i + 1)]
        if raw[:4] == b'\0\0\0\0':
            at = strings + struct.unpack_from('<I', raw, 4)[0]
            name = data[at:data.index(b'\0', at)].decode('latin-1')
        else:
            name = raw[:8].rstrip(b'\0').decode('latin-1')
        section, = struct.unpack_from('<h', raw, 12)
        if section > 0 and raw[16] in (2, 3) and name.startswith(prefix):  # external or static
            found.append((name[len(prefix):], raw[16] == 2))
        i += 1 + raw[17]
    return found


def captured(data: bytes, known: set[str], prefix: str, functions: set[str]) -> list[str]:
    """The names an object defines that the rewrite would bind to something else: it sends
    every reference to a symbol-table name or a registered Clean function to that (objrewrite),
    whether the object's own symbol is static or not, so clean/main/villager_letter.c's static
    `send` became overlay 65's socket send. A registered function's own definition is the one
    exception: it becomes that function's body."""
    return sorted({name for name, external in definitions(data, prefix)
                   if name in known - functions or (name in functions and not external)})


def rewrite(data: bytes, known: set[str], native: set[str], prefix: str,
            functions: set[str]) -> tuple[bytes, set[str]]:
    """Absolute Clean pointers retain their name, an alias to the public wrapper.

    Game references still follow the usual DS/Native rules. Restore BODY so
    other users of objrewrite in this process cannot inherit Clean renaming.
    An object that defines a name the rewrite would capture (captured) is refused.
    """
    taken = captured(data, known, prefix, functions)
    if taken:
        raise ValueError('defines ' + ', '.join(taken) + ', named like a game symbol or a Clean function: '
                         'the rewrite would bind its uses to that one instead; rename it')
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
