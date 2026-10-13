/* func_0208520c @ 0x0208520c, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_021d232c;
extern unsigned int func_0207762c(int);
extern void MI_CpuCopy8(void *dst, const void *src, unsigned int size);

void func_0208520c(unsigned char *p0, int p1)
{
    unsigned int idx = p1 - 32;
    if (idx < 38) {
        unsigned int off = idx * 30;
        unsigned char *dst = (unsigned char *) &data_021d232c + off;
        dst[0] = 1;
        MI_CpuCopy8(dst, p0, func_0207762c(p1));
    }
}
