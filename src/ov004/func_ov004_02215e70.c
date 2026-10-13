/* func_ov004_02215e70 @ 0x02215e70, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *const data_ov004_02251438[];
extern void *const data_ov004_022514e4[];
extern void func_ov004_0220d258(void *p);
extern void func_ov004_02210cf0(void *p);

void *func_ov004_02215e70(char *self)
{
    *(const void **) (self) = data_ov004_02251438;
    *(const void **) (self + 0xec) = data_ov004_022514e4;
    func_ov004_0220d258(self + 0x848);
    func_ov004_02210cf0(self);
    return self;
}
