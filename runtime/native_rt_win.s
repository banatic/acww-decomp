# __alloca: the stack probe that code compiled for i686-pc-windows-gnu calls before a frame
# larger than a page. eax holds the size; every page of the new frame is touched in order so
# Windows grows the stack, then esp moves down by eax and execution returns to the caller.

	.text
	.globl	__alloca
__alloca:
	pushl	%ecx
	movl	%esp, %ecx
	addl	$8, %ecx
1:
	cmpl	$0x1000, %eax
	jb	2f
	subl	$0x1000, %ecx
	orl	$0, (%ecx)
	subl	$0x1000, %eax
	jmp	1b
2:
	subl	%eax, %ecx
	orl	$0, (%ecx)
	movl	%esp, %eax
	movl	%ecx, %esp
	movl	(%eax), %ecx
	pushl	4(%eax)
	ret
