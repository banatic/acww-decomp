/* func_ov112_0229f488 @ 0x0229f488, 0xe4 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov095_0229bc00(unsigned char *p1, unsigned char *p2, int v1, unsigned char *p3, int v2, int v3, int v4, int v5,
                               int v6, int v7);
extern void func_ov095_0229ce84(unsigned char *base, int code);
extern void func_ov095_0229cef4(unsigned char *base, int code);
extern void func_ov095_0229bee4(unsigned char *base);
extern void func_ov095_0229bed8(void *receiver, int value);
extern int func_ov112_0229f900(unsigned char *self);
extern int func_ov112_0229fe70(unsigned char *self, int param);
extern int func_ov112_0229f6b8(unsigned char *self);

void func_ov112_0229f488(unsigned char *self)
{
    if (func_ov095_0229bc00(self + 0x384, self + 0xc4, 0xa, self + 0xbd, 0x60, 0x10, 6, 0xa0, 1, 1) != 0) {
        func_ov095_0229ce84(self + 0x384, 0);
    } else {
        func_ov095_0229cef4(self + 0x384, 0);
    }

    if (func_ov112_0229f900(self)) {
        func_ov095_0229ce84(self + 0x384, 0xb);
    } else {
        func_ov095_0229cef4(self + 0x384, 0xb);
    }

    if (func_ov112_0229fe70(self, 0x200)) {
        func_ov095_0229ce84(self + 0x384, 0xc);
    } else {
        func_ov095_0229cef4(self + 0x384, 0xc);
    }

    if (func_ov112_0229f900(self)) {
        func_ov095_0229bee4(self + 0x384);
        func_ov095_0229ce84(self + 0x384, 6);
    } else {
        if (self[0xbd] <= self[0xc0]) {
            func_ov095_0229bee4(self + 0x384);
        } else {
            int ret = func_ov112_0229f6b8(self);
            func_ov095_0229bed8(self + 0x384, ret);
        }
    }
}
