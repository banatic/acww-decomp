/* func_ov103_0229c444 @ 0x0229c444, 0xb8 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov103_0229cce8(unsigned char *self, int value);
extern int func_0206fe54(int value);
extern int func_02065ec0(int value);
extern int func_02065f18(int value);
extern void func_ov002_02208d30(unsigned char *base, int arg);
extern void func_ov002_02208d4c(unsigned char *base, int arg1, int arg2);
extern void func_ov002_02207d24(unsigned char *base, int arg);
extern void func_ov103_0229c7ec(unsigned char *self);
extern void func_ov103_0229c52c(unsigned char *self);

void func_ov103_0229c444(unsigned char *self, int value)
{
    int r6;
    int r4_val;

    self[0x2da5] = value;
    func_ov002_02208d30(self + 0x26c0, 3);

    r6 = func_ov103_0229cce8(self, value);

    if (func_0206fe54(r6) != 0) {
        func_ov002_02208d4c(self + 0x26c0, 0, 0);
    }

    r4_val = func_02065ec0(r6);

    if (r4_val != 0) {
        if (r4_val == 7) {
            func_ov002_02208d4c(self + 0x26c0, 0x17, 1);
        } else {
            func_ov002_02208d4c(self + 0x26c0, 0x14, 1);
        }
    }

    if ((func_02065f18(r6) != 0xfff1 && r4_val == 3) || r4_val == 6 || r4_val == 1) {
        func_ov002_02208d4c(self + 0x26c0, 0x15, 2);
    }

    func_ov002_02208d4c(self + 0x26c0, 2, 3);

    func_ov103_0229c7ec(self);
    func_ov002_02207d24(self + 0x218c, 1);
    func_ov103_0229c52c(self);
}
