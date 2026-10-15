/* func_ov128_0229c2a0 @ 0x0229c2a0, 0x5c bytes, Thumb, module ov128
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov127_0229a04c(void *self, int a);
extern void func_ov127_02299fd4(void *self, unsigned char value);
extern void func_020b177c(void *self, int a);
extern void func_ov127_02299f90(void);
extern void func_ov002_0220b36c(void *self, const void *data, int a, int b);
extern int func_ov002_0220b338(void *self, int a);
extern void func_ov128_0229bb20(void *self);
extern const unsigned char data_ov128_0229cb38[];

void func_ov128_0229c2a0(void *self)
{
    func_ov127_0229a04c((char *) self + 0x4a4, 3);
    // clang-format off
    asm {
        ldr r0, =0x4a4
        add r0, self, r0
        mov r1, #6
        mov r2, #0
        bl func_ov127_02299fd4
    }
    // clang-format on
    func_020b177c((char *) self + 0x174, 3);
    // clang-format off
    asm {
        ldr r0, =0x4a4
        add r0, self, r0
    }
    // clang-format on
    func_ov127_02299f90();
    func_ov002_0220b36c((char *) self + 0x94, data_ov128_0229cb38, 6, 2);
    func_ov002_0220b338((char *) self + 0x94, 0x69);
    func_ov128_0229bb20(self);
}
