/* func_ov004_022133ac @ 0x022133ac, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *const data_ov004_02251690[];
extern void *const data_ov004_0225173c[];
extern void *func_ov004_022110e4(void *p);
extern void func_020f6560(void *p);

void *func_ov004_022133ac(char *self)
{
    func_ov004_022110e4(self);
    *(const void **) (self) = data_ov004_02251690;
    *(const void **) (self + 0xec) = data_ov004_0225173c;
    func_020f6560(self + 0x844);
    return self;
}
