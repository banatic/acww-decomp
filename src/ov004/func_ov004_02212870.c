/* func_ov004_02212870 @ 0x02212870, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *const data_ov004_02250e5c[];
extern void *const data_ov004_02250f08[];
extern void func_ov004_022110e4(void *p);
extern void func_020b9e58(void *p);

void *func_ov004_02212870(char *self)
{
    func_ov004_022110e4(self);
    *(const void **) (self) = data_ov004_02250e5c;
    *(const void **) (self + 0xec) = data_ov004_02250f08;
    func_020b9e58(self + 0x848);
    return self;
}
