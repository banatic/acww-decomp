/* func_ov048_02262738 @ 0x02262738, 0x44 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern void func_020161ac(void *self);
extern void func_02072dbc(void *sub);
extern void func_0203f674(void *sub);
extern void func_0203f5e0(void *sub);
extern void func_02088274(void *sub);
extern char data_ov048_02264208;

void *func_ov048_02262738(void *self)
{
    func_020161ac(self);
    *(void **) self = (void *) &data_ov048_02264208;
    func_02072dbc((char *) self + 0xbc);
    func_0203f674((char *) self + 0x3f0);
    func_0203f5e0((char *) self + 0x504);
    func_02088274((char *) self + 0x5d8);
    return self;
}
