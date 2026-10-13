/* func_ov004_0221ffc4 @ 0x0221ffc4, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *const data_ov004_02253e10[];
extern void func_ov004_02220d24(void *p);
extern void func_0202e5e0(void *p);

void *func_ov004_0221ffc4(char *self)
{
    *(const void **) self = data_ov004_02253e10;
    func_ov004_02220d24(self + 0x918);
    func_0202e5e0(self);
    return self;
}
