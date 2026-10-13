/* func_ov004_022177d8 @ 0x022177d8, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *const data_ov004_0225211c[];
extern void *const data_ov004_022521c8[];
extern void func_ov004_0220d258(void *p);
extern void func_ov004_02210cf0(void *p);

void *func_ov004_022177d8(char *self)
{
    *(const void **) (self) = data_ov004_0225211c;
    *(const void **) (self + 0xec) = data_ov004_022521c8;
    func_ov004_0220d258(self + 0x844);
    func_ov004_02210cf0(self);
    return self;
}
