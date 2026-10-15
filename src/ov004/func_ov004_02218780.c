/* func_ov004_02218780 @ 0x02218780, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *const data_ov004_02253058[];
extern void *const data_ov004_02253104[];
extern void *func_ov004_0220d0f4(void *p);
extern void *func_ov004_02210cf0(void *p);
extern void func_ov004_02211518(void *p);

void *func_ov004_02218780(char *self)
{
    *(const void **) (self) = data_ov004_02253058;
    *(const void **) (self + 0xec) = data_ov004_02253104;
    func_ov004_0220d0f4(self + 0x860);
    func_ov004_02210cf0(self);
    func_ov004_02211518(self);
    return self;
}
