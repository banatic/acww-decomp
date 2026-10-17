"""i386 entry wrappers for observing Native calls without changing the body ABI."""


def wrapper(name: str, index: int, prefix: str, extend: str | None = None) -> list[str]:
    """Use a table index, since overlay addresses and folded body addresses overlap.

    The return callback must use only integer registers: x87 can hold the body's
    result. pushal preserves both result registers even for a void declaration.
    Replacing the return address also preserves a body's hidden-result ret $4.
    """
    public = prefix + 'native_' + name
    body = prefix + 'native_body_' + name
    leave = public + '_guest_return'
    plain = public + '_untracked'
    lines = ['\t.p2align 4', f'\t.globl {public}', public + ':',
             f'\tcmpl $0, {prefix}native_guest_enter_hook', f'\tje {plain}',
             '\tpushal', '\tmovl %esp, %ebp', '\tandl $-16, %esp', '\tsubl $4, %esp',
             '\tleal 36(%ebp), %eax', '\tpushl %eax', '\tpushl 32(%ebp)', f'\tpushl ${index}',
             f'\tcall {prefix}native_guest_enter', '\tmovl %ebp, %esp', '\tpopal',
             f'\tmovl ${leave}, (%esp)', f'\tjmp {body}',
             # Reserve a live return slot before saving registers. A signal
             # may overwrite storage below ESP after popal; no red zone exists
             # in this ABI. ret consumes this slot, including after ret $4.
             leave + ':', f'\tpushl ${index}', '\tpushal', '\tmovl %esp, %ebp', '\tandl $-16, %esp',
             '\tsubl $12, %esp', f'\tpushl ${index}',
             f'\tcall {prefix}native_guest_return', '\tmovl %ebp, %esp',
             '\tmovl %eax, 32(%esp)', '\tpopal']
    if extend:
        lines.append('\t' + extend)
    lines += ['\tret', plain + ':']
    if extend:
        # Differential checks have no tracker. Preserve the existing widening
        # wrapper's sixteen-word argument capacity, with an aligned call site.
        lines += ['\tpushl %ebp', '\tmovl %esp, %ebp', '\tpushl %esi', '\tpushl %edi',
                  '\tandl $-16, %esp', '\tsubl $64, %esp', '\tleal 8(%ebp), %esi',
                  '\tmovl %esp, %edi', '\tmovl $16, %ecx', '\trep movsl',
                  f'\tcall {body}', '\t' + extend, '\tleal -8(%ebp), %esp',
                  '\tpopl %edi', '\tpopl %esi', '\tpopl %ebp', '\tret']
    else:
        lines.append('\tjmp ' + body)
    return lines
