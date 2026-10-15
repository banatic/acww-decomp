/* native_trampoline: Native code calling the DS's code (native_run.h).
 *
 * The fault handler (or a patched Native entry) arrives here with eax = the DS address that
 * was called and the stack as the caller set it up for the callee: the return address at
 * [esp], the arguments above it, and `this` in ecx for a thiscall (C++ member functions on
 * 32-bit Windows). native_call_reference runs the callee in the interpreter and returns its
 * r0:r1 in eax:edx, and leaves in native_pop_bytes how many argument bytes the callee would
 * have popped (a thiscall callee pops its stack parameters; cdecl ones pop nothing), and in
 * native_return_floating whether the result is a float (1) or a double (2), which the PC
 * returns in st(0). The registers the caller expects kept (ebx, esi, edi, ebp) are kept by
 * the C function.
 */
#ifdef _WIN32
#define SYM(x) _##x
/* The object has no exception handlers: it declares itself compatible with /SAFESEH, which
 * the MSVC-target link of the runtime asks of every object. */
	.def	@feat.00
	.scl	3
	.type	0
	.endef
	.globl	@feat.00
	.set	@feat.00, 1
#else
#define SYM(x) x
#endif

	.text
	.globl	SYM(native_trampoline)
SYM(native_trampoline):
	pushl	%ebp
	movl	%esp, %ebp
	/* the C function may assume the System V i386 16-byte alignment at its call */
	andl	$-16, %esp
	subl	$4, %esp
	pushl	%ecx		/* this */
	leal	8(%ebp), %edx
	pushl	%edx		/* the arguments */
	pushl	%eax		/* the DS address */
	call	SYM(native_call_reference)
	/* a floating-point result goes to st(0), from r0 (float) or r0:r1 (double) */
	movl	SYM(native_return_floating), %ecx
	testl	%ecx, %ecx
	jz	2f
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	cmpl	$1, %ecx
	jne	3f
	flds	(%esp)
	jmp	2f
3:
	fldl	(%esp)
2:
	movl	SYM(native_pop_bytes), %ecx
	movl	%ebp, %esp
	popl	%ebp
	testl	%ecx, %ecx
	jnz	1f
	ret
1:
	/* pop the parameters: move the return address up over them, then return from there */
	pushl	%eax
	movl	4(%esp), %eax
	movl	%eax, 4(%esp,%ecx)
	popl	%eax
	addl	%ecx, %esp
	ret

#ifndef _WIN32
	.section .note.GNU-stack,"",@progbits
#endif
