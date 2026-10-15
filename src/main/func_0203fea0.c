/* func_0203fea0 @ 0x0203fea0, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(void *src, void *dst, unsigned int len);
extern int func_0203feec(int a, void *b, int c, int d);

int func_0203fea0(int param1, void *param2)
{
    char buf[8];
    MI_CpuCopy8(param2, buf, 8);
    return func_0203feec(param1, buf, 1, 0);
}
