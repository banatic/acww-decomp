/* rmo_object_slots_5: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222c7a0 @ 0x0222c7a0, 0x48 bytes, Thumb
 * func_ov004_0222c774 @ 0x0222c774, 0x2c bytes, Thumb
 */

extern void *func_0203f080(void *);
extern void *func_020551e0(void *);
extern int func_ov004_0222c31c(void *);
extern void func_ov004_0222c394(void *);
extern int func_ov004_0222c538(void *);
extern void *data_ov004_02254b28;
extern int func_0203f030(char *self);
extern void func_0203efb0(char *self, int a);
extern void func_ov004_0222c314(char *p);

void *func_ov004_0222c7a0(char *self)
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

int func_ov004_0222c774(char *self)
{
    int r;
    if (func_0203f030(self) == 0) {
        r = 0;
    } else {
        func_0203efb0(self, 0);
        func_ov004_0222c314(self + 0x250);
        r = 1;
    }
    return r;
}
