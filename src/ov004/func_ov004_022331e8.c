/* func_ov004_022331e8 @ 0x022331e8, 0x7c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_020324c4(void *);
extern void func_020551e0(void *);
extern void func_020ee62c(void *);
extern void __cxa_vec_cleanup(void *, int, int, void *);
extern void func_ov004_022322ec(void *);
extern void func_ov004_02232470(void *);
extern void func_ov004_0223273c(void *);
extern void func_ov004_022329c8(void *);
extern void func_ov004_022324d8();
extern void *data_020da13c;
extern void *data_ov004_02255ac8;

void *func_ov004_022331e8(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_02255ac8;
    func_ov004_022322ec(self + 0x34fc);
    func_020324c4(self + 0x3460);
    func_ov004_02232470(self + 0x3328);
    func_ov004_0223273c(self + 0x1228);
    func_ov004_022329c8(self + 0x128);
    __cxa_vec_cleanup(self + 0x108, 0x1, 0x20, (void *) func_ov004_022324d8);
    func_020551e0(self + 0x50);
    *(void **) (self) = &data_020da13c;
    func_020ee62c(self);
    return self;
}
