/* func_ov107_0229d2d8 @ 0x0229d2d8, 0x44 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov107_0229d388(unsigned int unused0, unsigned int unused1);
extern int func_ov107_0229d36c(int a, int b);
extern void func_ov094_0229aa14(int a, int b, int c, int d);
extern void func_ov094_0229a9b4(int a, int b);

void func_ov107_0229d2d8(int a, int b, int c, int d)
{
    int e;
    if (func_ov107_0229d388(a, b)) {
        e = func_ov107_0229d36c(a, b);
        func_ov094_0229aa14(a + 0x10c, e, c, d);
        func_ov094_0229a9b4(a + 0x10c, e);
    }
}
