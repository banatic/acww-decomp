/* func_020736f4 @ 0x020736f4, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_020ccf94;
extern int func_02073744(unsigned int);
extern int func_02073768(unsigned int);
extern void func_0207374c(unsigned int, int);
extern void MI_CpuCopy8(int, int, int);

int func_020736f4(int a, int p1, int p2)
{
    int len = func_02073744(data_020ccf94);
    if ((unsigned int) (0x91a - len) >= (unsigned int) p2) {
        int g = data_020ccf94;
        int base = func_02073768(g);
        MI_CpuCopy8(p1, base + len, p2);
        func_0207374c(g, len + p2);
        return 1;
    }
    return 0;
}
