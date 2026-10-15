/* func_ov087_02278a00 @ 0x02278a00, 0x28 bytes, Thumb, module ov087
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov087_02278fdc(void *);
extern void *func_0202ee5c(void *);

extern unsigned char data_ov087_022794ec[];

void *func_ov087_02278a00(void *self)
{
    *(void **) self = (void *) data_ov087_022794ec;
    func_ov087_02278fdc((char *) self + 0x658);
    func_0202ee5c(self);
    return self;
}
