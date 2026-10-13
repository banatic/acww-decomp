/* func_ov078_02278a00 @ 0x02278a00, 0x28 bytes, Thumb, module ov078
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov078_02279b2c[];
extern void func_ov078_02278fe4(void *);
extern void func_0202ee5c(void *);

void *func_ov078_02278a00(void *self)
{
    *(void **) self = &data_ov078_02279b2c;
    func_ov078_02278fe4((char *) self + 0x658);
    func_0202ee5c(self);
    return self;
}
