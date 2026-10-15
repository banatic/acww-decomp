/* func_ov004_02221850 @ 0x02221850, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *const data_ov004_02253fd4[];
extern void *func_ov004_02221994(void *p);
extern void *func_0202e5e0(void *p);

void *func_ov004_02221850(char *self)
{
    *(const void **) self = data_ov004_02253fd4;
    func_ov004_02221994(self + 0x89c);
    func_0202e5e0(self);
    return self;
}
