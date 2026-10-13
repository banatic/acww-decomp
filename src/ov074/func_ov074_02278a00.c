/* func_ov074_02278a00 @ 0x02278a00, 0x34 bytes, Thumb, module ov074
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov074_02278b1c(char *);
extern void func_ov074_02278fe4(char *);
extern void func_0202ee5c(char *);
extern char data_ov074_02279c68;

char *func_ov074_02278a00(char *self)
{
    *(char **) self = &data_ov074_02279c68;
    func_ov074_02278b1c(self + 0x714);
    func_ov074_02278fe4(self + 0x658);
    func_0202ee5c(self);
    return self;
}
