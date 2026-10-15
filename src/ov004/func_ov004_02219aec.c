/* func_ov004_02219aec @ 0x02219aec, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *const data_ov004_022525cc[];
extern void *const data_ov004_02252678[];
extern void *func_ov004_022110e4(void *p);
extern void *func_ov004_0220d110(void *p);

void *func_ov004_02219aec(char *self)
{
    func_ov004_022110e4(self);
    *(const void **) (self) = data_ov004_022525cc;
    *(const void **) (self + 0xec) = data_ov004_02252678;
    func_ov004_0220d110(self + 0x84c);
    return self;
}
