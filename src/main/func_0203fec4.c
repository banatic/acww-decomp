/* func_0203fec4 @ 0x0203fec4, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203feec(void *dst, void *src, int param, void *param2);
extern void MI_CpuCopy8(void *dst, const void *src, unsigned int size);

int func_0203fec4(void *a, void *b, void *c)
{
    unsigned char buf[8];
    MI_CpuCopy8(b, buf, 8);
    return func_0203feec(a, buf, 0, c);
}
