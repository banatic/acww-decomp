/* otter: 2 functions, module ov076
 * mwccarm 1.2/base -O4,s
 * func_ov076_02278a28 @ 0x02278a28, 0x2c bytes, Thumb
 * func_ov076_02278a00 @ 0x02278a00, 0x28 bytes, Thumb
 */

extern void *func_ov076_02278e78(void *);
extern void *func_0202ee5c(void *);
extern void func_020edf54(void *);
extern char data_ov076_022797d4[];

void *func_ov076_02278a28(void *obj)
{
    *(void **) obj = (void *) ((char *) data_ov076_022797d4);
    func_ov076_02278e78((char *) obj + 0x658);
    func_0202ee5c(obj);
    func_020edf54(obj);
    return obj;
}

void *func_ov076_02278a00(void *self)
{
    *(void **) self = data_ov076_022797d4;
    func_ov076_02278e78((char *) self + 0x658);
    func_0202ee5c(self);
    return self;
}
