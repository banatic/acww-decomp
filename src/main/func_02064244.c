/* func_02064244 @ 0x02064244, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020642e0(void *a);
extern unsigned short func_0206426c(void *a);
extern void MI_CpuCopy8(void *dest, const void *src, unsigned int n);

void func_02064244(void *a, void *b)
{
    func_020642e0(a);
    MI_CpuCopy8(b, (char *) a + 2, 12);
    *(unsigned short *) a = func_0206426c(a);
}
