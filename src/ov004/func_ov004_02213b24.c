/* func_ov004_02213b24 @ 0x02213b24, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *const data_ov004_02251ec4[];
extern void *const data_ov004_02251f70[];
extern void func_ov004_022110e4(void *p);
extern void func_020f5958(void *p);

void *func_ov004_02213b24(char *self)
{
    func_ov004_022110e4(self);
    *(const void **) (self) = data_ov004_02251ec4;
    *(const void **) (self + 0xec) = data_ov004_02251f70;
    func_020f5958(self + 0x848);
    return self;
}
