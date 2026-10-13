/* func_ov003_0221b668 @ 0x0221b668, 0x6c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f5948(void *);
extern void func_ov003_0221b75c(void *);
extern void func_02032c50(void *);
extern void func_02055764(void *);
extern void func_02066994(void *);
extern void func_0203f080(void *);

extern unsigned char data_ov003_022382ac[];
extern unsigned char data_ov003_02238314[];

void *func_ov003_0221b668(void *self)
{
    *(void **) self = (void *) data_ov003_022382ac;
    *(void **) ((char *) self + 0xec) = (void *) data_ov003_02238314;
    func_020f5948((char *) self + 0x328);
    func_ov003_0221b75c((char *) self + 0x2a4);
    func_02032c50((char *) self + 0x274);
    func_02055764((char *) self + 0x1d0);
    func_02055764((char *) self + 0x134);
    func_02066994((char *) self + 0xec);
    func_0203f080(self);
    return self;
}
