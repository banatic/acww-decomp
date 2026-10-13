/* func_ov004_0221230c @ 0x0221230c, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *const data_ov004_022509ac[];
extern void *const data_ov004_02250a58[];
extern void func_ov004_0220d0f4(void *p);
extern void func_ov004_02210cf0(void *p);
extern void func_ov004_02211518(void *p);

void *func_ov004_0221230c(char *self)
{
    *(const void **) (self) = data_ov004_022509ac;
    *(const void **) (self + 0xec) = data_ov004_02250a58;
    func_ov004_0220d0f4(self + 0x844);
    func_ov004_02210cf0(self);
    func_ov004_02211518(self);
    return self;
}
