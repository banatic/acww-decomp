/* func_ov004_0222f08c @ 0x0222f08c, 0x5c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_02138c48(void *, int, int, void *);
extern void func_ov004_0222c7a0(void *);
extern void func_020551e0();
extern void func_ov004_0222c394();
extern void func_ov004_0222c538();
extern void *data_ov004_02254fc8;

void *func_ov004_0222f08c(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_02254fc8;
    func_02138c48(self + 0xecc, 0x9, 0x4, (void *) func_ov004_0222c394);
    func_02138c48(self + 0x908, 0x9, 0xa4, (void *) func_ov004_0222c538);
    func_02138c48(self + 0x290, 0x9, 0xb8, (void *) func_020551e0);
    func_ov004_0222c7a0(self);
    return self;
}
