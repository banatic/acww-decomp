/* func_ov096_0229f5e0 @ 0x0229f5e0, 0x70 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_0229f830(void);
extern int func_ov096_0229f7ac(int p0, int p1);
extern int func_ov096_0229f820(int p0, int p1);
extern int func_ov096_0229f054(int p0, int p1);
extern void func_ov096_0229e0a8(int p0, int p1);
extern void func_ov094_0229aa14(int p0, int p1, int p2, int p3);
extern void func_ov094_0229a9b4(int p0, int p1);
extern void func_02065ed0(int p0, int p1, int p2);

void func_ov096_0229f5e0(int a0, int a1, int a2, int a3)
{
    if (func_ov096_0229f830()) {
        int ret = func_ov096_0229f7ac(a0, a1);
        func_ov094_0229aa14(a0 + 0x358, ret, a2, a3);
        func_ov094_0229a9b4(a0 + 0x358, ret);
    } else {
        if (func_ov096_0229f820(a0, a1)) {
            int ret2 = func_ov096_0229f054(a0, a1);
            func_02065ed0(ret2, a2, a3);
        } else {
            if (a1 == 0x25) {
                func_ov096_0229e0a8(a0, a2);
            }
        }
    }
}
