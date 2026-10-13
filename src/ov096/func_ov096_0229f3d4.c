/* func_ov096_0229f3d4 @ 0x0229f3d4, 0x8c bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_0229f3bc(void);
extern int func_ov096_0229f39c(int, int, int);
extern int func_ov096_0229c2fc(int, int);
extern int func_ov096_0229c2dc(int, int);

int func_ov096_0229f3d4(int a, int b, int c)
{
    int r0;
    int r5 = b;
    int r4 = c;
    int r6 = a;

    if (func_ov096_0229f3bc() != 0) {
        return 0x24;
    }

    if (r5 > 0x6c && r5 < 0xc4 && r4 > 0x50 && r4 < 0x68) {
        if (r5 < 0x98) {
            return 0x22;
        } else {
            return 0x23;
        }
    }

    r0 = func_ov096_0229f39c(r6, r5, r4);
    if (r0 != 0) {
        if (func_ov096_0229c2fc(r6, 0x4000) != 0) {
            return 0x26;
        } else {
            return 0x25;
        }
    }

    if (r5 > 0x30 && r5 < 0x60 && r4 > 0x50 && r4 < 0x60) {
        if (func_ov096_0229c2fc(r6, 0x4000) != 0) {
            return 0x26;
        } else {
            return 0x25;
        }
    }

    func_ov096_0229c2dc(r6, 0x4000);
    return 0x26;
}
