/* func_ov004_0223ab98 @ 0x0223ab98, 0x48 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_02138d6c();
extern void func_ov004_0223adb4();
extern void func_ov004_0223adc8();

void *func_ov004_0223ab98(char *self)
{
    func_02138d6c(self + 0x4, 0x2, 0xa8, (void *) func_ov004_0223adc8, (void *) func_ov004_0223adb4);
    *(short *) (self) = -1;
    *(int *) (self + 0x154) = 0x0;
    *(int *) (self + 0x158) = 0x0;
    *(int *) (self + 0x15c) = 0x0;
    return self;
}
