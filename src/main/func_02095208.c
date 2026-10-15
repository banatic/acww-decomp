/* func_02095208 @ 0x02095208, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(void *dst, const void *src, unsigned int size);
extern int func_020642bc(void *a, void *b);

void func_02095208(char *a, char *b)
{
    MI_CpuCopy8(b + 0x10, a + 0x10, 0xc);
    *(unsigned short *) (a + 0xe) = *(unsigned short *) (b + 0xe);
    *(signed char *) (a + 0x1c) = *(signed char *) (b + 0x1c);
    func_020642bc(a, b);
}
