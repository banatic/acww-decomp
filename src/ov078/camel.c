/* camel: 2 functions, module ov078
 * mwccarm 1.2/base -O4,s
 * func_ov078_02278a28 @ 0x02278a28, 0x2c bytes, Thumb
 * func_ov078_02278a00 @ 0x02278a00, 0x28 bytes, Thumb
 */

extern void *func_ov078_02278fe4(void *);
extern void *func_0202ee5c(void *);
extern void func_020edf54(void *);
extern char data_ov078_02279b2c[];

void *func_ov078_02278a28(void *arg)
{
    *(void **) arg = ((char *) data_ov078_02279b2c);
    func_ov078_02278fe4((char *) arg + 0x658);
    func_0202ee5c(arg);
    func_020edf54(arg);
    return arg;
}

void *func_ov078_02278a00(void *self)
{
    *(void **) self = &data_ov078_02279b2c;
    func_ov078_02278fe4((char *) self + 0x658);
    func_0202ee5c(self);
    return self;
}
