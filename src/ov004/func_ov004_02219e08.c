/* func_ov004_02219e08 @ 0x02219e08, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *const data_ov004_02251a14[];
extern void *const data_ov004_02251ac0[];
extern void func_ov004_022110e4(void *p);
extern void func_ov004_0220d110(void *p);

void *func_ov004_02219e08(char *self)
{
    func_ov004_022110e4(self);
    *(const void **) (self) = data_ov004_02251a14;
    *(const void **) (self + 0xec) = data_ov004_02251ac0;
    func_ov004_0220d110(self + 0x848);
    return self;
}
