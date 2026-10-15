/* func_ov085_02278a28 @ 0x02278a28, 0x2c bytes, Thumb, module ov085
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov085_02278efc(void *p);
extern void *func_0202ee5c(void *p);
extern void func_020edf54(void *p);

extern unsigned char data_ov085_022794f0[];

void *func_ov085_02278a28(void *self)
{
    *(unsigned int *) self = (unsigned int) data_ov085_022794f0;
    func_ov085_02278efc((char *) self + 0x658);
    func_0202ee5c(self);
    func_020edf54(self);
    return self;
}
