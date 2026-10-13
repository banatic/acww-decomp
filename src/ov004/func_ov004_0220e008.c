/* func_ov004_0220e008 @ 0x0220e008, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_02032564(void *self);
extern void func_ov004_0220dfe0(void *self);
extern char data_ov004_0224fe0c;

void *func_ov004_0220e008(void *self)
{
    func_02032564(self);
    *(void **) self = (void *) &data_ov004_0224fe0c;
    func_ov004_0220dfe0(self);
    return self;
}
