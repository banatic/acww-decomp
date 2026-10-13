/* func_ov004_02230b20 @ 0x02230b20, 0x70 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_020565b0(void *);
extern void func_020edf54(void *);
extern void func_02138c48(void *, int, int, void *);
extern void func_ov004_0222c7a0(void *);
extern void func_020551e0();
extern void func_ov004_0222c394();
extern void func_ov004_0222c538();
extern void *data_ov004_02255674;

void *func_ov004_02230b20(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_02255674;
    func_020565b0(self + 0x6b4);
    func_02138c48(self + 0x6a4, 0x3, 0x4, (void *) func_ov004_0222c394);
    func_02138c48(self + 0x4b8, 0x3, 0xa4, (void *) func_ov004_0222c538);
    func_02138c48(self + 0x290, 0x3, 0xb8, (void *) func_020551e0);
    func_ov004_0222c7a0(self);
    func_020edf54(self);
    return self;
}
