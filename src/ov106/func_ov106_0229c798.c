/* func_ov106_0229c798 @ 0x0229c798, 0xd0 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov106_0229c344(void *self, int param);
extern void func_ov002_02208d30(void *ptr, int val);
extern int func_ov106_0229d20c(void *self, int a);
extern int func_0206fe54(void);
extern int func_02065ec0(int x);
extern int func_02065f18(int x);
extern int func_ov002_02208d4c(void *ptr, int val1, int val2);
extern void func_ov106_0229cc50(void *self);
extern int func_ov002_02207d24(void *ptr, int val);
extern void func_ov106_0229c894(void *self, int b);

void func_ov106_0229c798(unsigned char *self, int a, int b)
{
    int x, y;

    func_ov106_0229c344(self, 0x10000);
    self[0xb9] = (unsigned char) a;
    func_ov002_02208d30(self + 0x26ec, 4);
    x = func_ov106_0229d20c(self, a);
    if (func_0206fe54()) {
        func_ov002_02208d4c(self + 0x26ec, 0, 0);
    }
    y = func_02065ec0(x);
    if (y != 0) {
        if (y == 7) {
            func_ov002_02208d4c(self + 0x26ec, 0x17, 1);
        } else {
            func_ov002_02208d4c(self + 0x26ec, 0x14, 1);
        }
    }
    if (func_02065f18(x) == 0xfff1) {
        if (y == 3 || y == 6 || y == 1 || y == 4) {
            func_ov002_02208d4c(self + 0x26ec, 0x15, 3);
        }
    }
    func_ov002_02208d4c(self + 0x26ec, 2, 4);
    func_ov106_0229cc50(self);
    if (b == 0) {
        func_ov002_02207d24(self + 0x21b8, 1);
    }
    func_ov106_0229c894(self, b);
}
