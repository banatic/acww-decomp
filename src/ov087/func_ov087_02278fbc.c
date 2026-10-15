/* func_ov087_02278fbc @ 0x02278fbc, 0x20 bytes, Thumb, module ov087
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0202eb20(void *self);
extern void func_020edb3c(void *self);
extern char data_ov087_0227945c;

void *func_ov087_02278fbc(void *self)
{
    *(void **) self = (void *) &data_ov087_0227945c;
    func_0202eb20(self);
    func_020edb3c(self);
    return self;
}
