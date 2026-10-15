/* func_ov004_02213af0 @ 0x02213af0, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *const data_ov004_02251ec4[];
extern void *const data_ov004_02251f70[];
extern void func_020f5948(void *p);
extern void *func_ov004_02210cf0(void *p);

void *func_ov004_02213af0(char *self)
{
    *(const void **) (self) = data_ov004_02251ec4;
    *(const void **) (self + 0xec) = data_ov004_02251f70;
    func_020f5948(self + 0x848);
    func_ov004_02210cf0(self);
    return self;
}
