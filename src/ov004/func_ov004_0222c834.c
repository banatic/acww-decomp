/* func_ov004_0222c834 @ 0x0222c834, 0x48 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0203f080(void *);
extern void *func_020551e0(void *);
extern int func_ov004_0222c31c(void *);
extern void func_ov004_0222c394(void *);
extern int func_ov004_0222c538(void *);
extern void *data_ov004_02254b28;

void *func_ov004_0222c834(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_02254b28;
    func_ov004_0222c31c(self + 0x250);
    func_ov004_0222c394(self + 0x248);
    func_ov004_0222c538(self + 0x1a4);
    func_020551e0(self + 0xec);
    func_0203f080(self);
    return self;
}
