/* func_ov004_02233ad4 @ 0x02233ad4, 0x3c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b6660(int);
extern void func_0204f538(void *, unsigned short *, int, int, int);
extern void *data_021c80bc;

void func_ov004_02233ad4(int a0, int a1, unsigned short a2, int a3)
{
    void *g;
    func_020b6660(a0);
    g = data_021c80bc;
    if (g != 0) {
        volatile unsigned short t = 0xfff1;
        t = a2;
        func_0204f538(g, (unsigned short *) &t, a0, a1, a3);
    }
}
