/* func_ov004_02231ab8 @ 0x02231ab8, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *const data_ov004_02255a38[];
extern void *const data_020da13c[];
extern void func_020ee62c(void *p);
extern void func_020edf54(void *p);

void *func_ov004_02231ab8(const void **self)
{
    *self = data_ov004_02255a38;
    *self = data_020da13c;
    func_020ee62c(self);
    func_020edf54(self);
    return self;
}
