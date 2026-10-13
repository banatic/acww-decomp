/* func_ov004_02213378 @ 0x02213378, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *const data_ov004_02251690[];
extern void *const data_ov004_0225173c[];
extern void func_020f655c(void *p);
extern void func_ov004_02210cf0(void *p);

void *func_ov004_02213378(char *self)
{
    *(const void **) (self) = data_ov004_02251690;
    *(const void **) (self + 0xec) = data_ov004_0225173c;
    func_020f655c(self + 0x844);
    func_ov004_02210cf0(self);
    return self;
}
