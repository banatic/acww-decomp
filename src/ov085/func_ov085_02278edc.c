/* func_ov085_02278edc @ 0x02278edc, 0x20 bytes, Thumb, module ov085
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0202eb20(void *p);
extern void func_020edb3c(void *p);

extern unsigned char data_ov085_0227945c[];

void *func_ov085_02278edc(void *self)
{
    *(void **) self = (void *) data_ov085_0227945c;
    func_0202eb20(self);
    func_020edb3c(self);
    return self;
}
