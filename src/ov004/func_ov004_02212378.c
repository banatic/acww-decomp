/* func_ov004_02212378 @ 0x02212378, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *const data_ov004_022509ac[];
extern void *const data_ov004_02250a58[];
extern void func_ov004_022110e4(void *p);
extern void func_ov004_0220d110(void *p);

void *func_ov004_02212378(char *self)
{
    func_ov004_022110e4(self);
    *(const void **) (self) = data_ov004_022509ac;
    *(const void **) (self + 0xec) = data_ov004_02250a58;
    func_ov004_0220d110(self + 0x844);
    return self;
}
