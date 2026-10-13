/* func_ov004_02215f40 @ 0x02215f40, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *const data_ov004_02251438[];
extern void *const data_ov004_022514e4[];
extern void func_ov004_022110e4(void *p);
extern void func_ov004_0220d268(void *p);

void *func_ov004_02215f40(char *self)
{
    func_ov004_022110e4(self);
    *(const void **) (self) = data_ov004_02251438;
    *(const void **) (self + 0xec) = data_ov004_022514e4;
    func_ov004_0220d268(self + 0x848);
    return self;
}
