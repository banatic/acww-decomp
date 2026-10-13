/* func_ov076_02278a00 @ 0x02278a00, 0x28 bytes, Thumb, module ov076
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov076_022797d4[];
extern void func_ov076_02278e78(void *);
extern void func_0202ee5c(void *);

void *func_ov076_02278a00(void *self)
{
    *(void **) self = data_ov076_022797d4;
    func_ov076_02278e78((char *) self + 0x658);
    func_0202ee5c(self);
    return self;
}
