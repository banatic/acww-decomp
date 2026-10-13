/* func_ov004_022129c8 @ 0x022129c8, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *const data_ov004_022511e0[];
extern void *const data_ov004_0225128c[];
extern void func_ov004_022110e4(void *p);
extern void func_020b9e58(void *p);

void *func_ov004_022129c8(char *self)
{
    func_ov004_022110e4(self);
    *(const void **) (self) = data_ov004_022511e0;
    *(const void **) (self + 0xec) = data_ov004_0225128c;
    func_020b9e58(self + 0x848);
    return self;
}
