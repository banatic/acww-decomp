/* func_02048824 @ 0x02048824, 0x46 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(int p1, char *p2, int p3);
extern int func_0203fc78(int p1, char *p2, int p3);
extern void func_0204886c(int p1, int p2, int p3, int p4);

void func_02048824(int a, int b, int c, int d)
{
    char buf[8];
    int cond;

    MI_CpuCopy8(c, buf, 8);
    cond = (func_0203fc78(14, buf, 0) == 2) ? 0 : 1;
    if (cond != 0) {
        if (d > 7) {
            d = 7;
        }
        func_0204886c(a, b, 0, d);
    }
}
