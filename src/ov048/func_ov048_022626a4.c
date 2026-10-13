/* func_ov048_022626a4 @ 0x022626a4, 0x4c bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern void func_02088264(void *);
extern void func_0203f5dc(void *);
extern void func_0203f664(void *);
extern void func_02072da4(void *);
extern void func_0201615c(void *);
extern void func_020edb3c(void *);

extern unsigned char data_ov048_02264208[];

void *func_ov048_022626a4(void *self)
{
    *(void **) self = (void *) data_ov048_02264208;
    func_02088264((char *) self + 0x5d8);
    func_0203f5dc((char *) self + 0x504);
    func_0203f664((char *) self + 0x3f0);
    func_02072da4((char *) self + 0xbc);
    func_0201615c(self);
    func_020edb3c(self);
    return self;
}
