/* func_ov096_022a03e4 @ 0x022a03e4, 0xc0 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206f56c(void);
extern void func_ov096_0229c4ec(unsigned char *p);
extern void func_ov096_0229c514(unsigned char *p);
extern void func_ov096_0229c2ec(unsigned char *p, int arg);
extern int func_0208e4bc(unsigned char *p);
extern int func_ov002_0220b5ec(unsigned char *p, int arg);
extern int func_ov002_0220b59c(unsigned char *p, int arg);
extern void func_ov002_0220a0b4(unsigned char *p, int a, int b);
extern void func_ov002_0220a374(unsigned char *p, int arg);
extern int func_ov002_02208014(void);
extern void func_ov096_0229ddd8(unsigned char *p);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov002_0220a1dc(unsigned char *p);
extern unsigned short data_021fbe40[2];

void func_ov096_022a03e4(unsigned char *self)
{
    int a, b, v1, v2, flags;

    a = func_0206f56c();
    if (a != 0) {
        func_ov096_0229c4ec(self);
        return;
    }

    b = func_0206f56c();
    if (b != 0) {
        func_ov096_0229c514(self);
        func_ov096_0229c2ec(self, 0x20000);
        return;
    }

    if (func_0208e4bc(self + 0x2500) == 0) {
        v1 = func_ov002_0220b5ec(self + 0x2d9c, 1);
        v2 = func_ov002_0220b59c(self + 0x2d9c, 1);
        func_ov002_0220a0b4(self + 0x2500, v1, v2);
        func_ov002_0220a374(self + 0x2500, 1);
    }

    // clang-format off
    asm {
        mov r0, self
    }
    // clang-format on
    if (func_ov002_02208014())
    {
        func_ov096_0229ddd8(self);
        func_ov002_02208098((void *) (self), 7);
        return;
    }

    flags = data_021fbe40[1];
    if ((flags & 1) != 0 || (flags & 2) != 0) {
        func_ov002_0220a1dc(self + 0x2500);
        func_ov002_02208098((void *) (self), 0x18);
    }
}
