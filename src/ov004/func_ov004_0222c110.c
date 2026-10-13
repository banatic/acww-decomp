/* func_ov004_0222c110 @ 0x0222c110, 0x3c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02096718(int a);
extern int func_ov004_0222b9d4(void *self, int a, int b, int arg, short v);
extern void func_0200f234(void *p);

int func_ov004_0222c110(int a, int b)
{
    void *p = func_02096718(4);
    if (p != 0) {
        if (func_ov004_0222b9d4(p, a, b, 6, -1) != 0) {
            func_0200f234(p);
            return 1;
        }
    }
    return 0;
}
