/* func_ov004_0221a4e4 @ 0x0221a4e4, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *const data_ov004_02252f2c[];
extern void *const data_ov004_02252fd8[];
extern void *func_ov004_0220d0f4(void *p);
extern void *func_ov004_02210cf0(void *p);

void *func_ov004_0221a4e4(char *self)
{
    *(const void **) (self) = data_ov004_02252f2c;
    *(const void **) (self + 0xec) = data_ov004_02252fd8;
    func_ov004_0220d0f4(self + 0x848);
    func_ov004_02210cf0(self);
    return self;
}
