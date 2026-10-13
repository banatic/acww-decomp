/* func_ov095_0229be18 @ 0x0229be18, 0xa4 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov095_022999b0(void *a, int b);
extern void func_ov095_022999a8(void *a, int b);
extern int func_02051c8c_unk(void *a, int b);
extern int func_02051d08(void *a, int b);
extern int func_02051d30(void *a);

int func_ov095_0229be18(void *a0, unsigned short *a1, void *a2, int a3, int a4, int a5)
{
    if (a4 == a3) {
        if (func_ov095_022999b0(a0, 0x100) == 0) {
            func_ov095_022999a8(a0, 0x40);
        }
        return 0;
    } else {
        int res;
        int r1;
        int r2;

        res = func_02051c8c_unk(a1, a4);
        if (res == a4 && a1[res - 1] != 0x3000) {
            if (func_ov095_022999b0(a0, 0x100) == 0) {
                func_ov095_022999a8(a0, 0x40);
            }
            return 0;
        }
        if (a5 < 0) {
            return 1;
        }
        r1 = func_02051d08(a1, a4);
        r2 = func_02051d30(a2);
        if (r1 + r2 > a5) {
            if (func_ov095_022999b0(a0, 0x100) == 0) {
                func_ov095_022999a8(a0, 0x80);
            }
            return 0;
        }
        return 1;
    }
}
