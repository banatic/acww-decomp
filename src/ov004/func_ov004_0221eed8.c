/* func_ov004_0221eed8 @ 0x0221eed8, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *const data_ov004_02253bb4[];
extern void func_ov004_0221f848(void *p);
extern void func_0202e5e0(void *p);

void *func_ov004_0221eed8(char *self)
{
    *(const void **) self = data_ov004_02253bb4;
    func_ov004_0221f848(self + 0x8a8);
    func_0202e5e0(self);
    return self;
}
