/* func_02019a84 @ 0x02019a84, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02077978(unsigned char *dst, int a, int b);
extern void MI_CpuCopy8(unsigned char *dst, int a, int b);

void func_02019a84(int a, int b, int c, int d, int e, short *f, unsigned char *p)
{
    func_02077978(p, a, b);
    func_02077978(p + 5, c, d);
    MI_CpuCopy8(p + 10, e, 2);
    *f = p[12];
}
