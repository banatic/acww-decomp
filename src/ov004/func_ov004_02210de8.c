/* func_ov004_02210de8 @ 0x02210de8, 0xfc bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203f080(void *);
extern void func_02054e18(void *);
extern void func_02066994(void *);
extern void func_0209d340(void *);
extern void func_020b82d0(void *);
extern void __cxa_vec_cleanup(void *, int, int, void *);
extern void func_ov004_0220d028(void *);
extern void func_ov004_0220d258(void *);
extern void func_ov004_0220d388(void *);
extern void func_ov004_0220d3b4(void *);
extern void func_ov004_0220d4d8(void *);
extern void func_ov004_0220d824(void *);
extern void func_ov004_0220dff0(void *);
extern void func_ov004_0220e458(void *);
extern void func_ov004_02211518(void *);
extern void func_ov004_0223b248(void *);
extern void func_ov004_0223cfb8(void *);
extern void func_020b7ed8();
extern void func_ov004_0220e4d4();
extern void *data_ov004_0224fe6c;
extern void *data_ov004_0224ff18;

void *func_ov004_02210de8(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_0224fe6c;
    *(void **) (self + 0xec) = &data_ov004_0224ff18;
    __cxa_vec_cleanup(self + 0x7c4, 0x4, 0x20, (void *) func_ov004_0220e4d4);
    func_ov004_0223cfb8(self + 0x798);
    func_ov004_0220d028(self + 0x764);
    func_ov004_0220d258(self + 0x748);
    func_ov004_0220d3b4(self + 0x742);
    func_ov004_0220d388(self + 0x740);
    func_ov004_0220e458(self + 0x6cc);
    func_ov004_0220dff0(self + 0x62c);
    func_02054e18(self + 0x538);
    func_020b82d0(self + 0x28c);
    func_ov004_0223b248(self + 0x250);
    __cxa_vec_cleanup(self + 0x1d0, 0x4, 0x20, (void *) func_020b7ed8);
    func_ov004_0220d824(self + 0x18c);
    func_ov004_0220d4d8(self + 0x17c);
    func_0209d340(self + 0x132);
    func_02066994(self + 0xec);
    func_0203f080(self);
    func_ov004_02211518(self);
    return self;
}
