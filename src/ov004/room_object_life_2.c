/* room_object_life_2: 6 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022111ec @ 0x022111ec, 0x4 bytes, Thumb
 * func_ov004_022110e4 @ 0x022110e4, 0x108 bytes, Thumb
 * func_ov004_02210fdc @ 0x02210fdc, 0x108 bytes, Thumb
 * func_ov004_02210ee4 @ 0x02210ee4, 0xf8 bytes, Thumb
 * func_ov004_02210de8 @ 0x02210de8, 0xfc bytes, Thumb
 * func_ov004_02210cf0 @ 0x02210cf0, 0xf8 bytes, Thumb
 */

extern void *func_0203f130(void *);
extern void *func_02054e54(void *);
extern void *func_02066a30(void *);
extern void func_0209d34c(void *);
extern void *func_020b82ec(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*callback3)(void *), void (*callback4)(void *));
extern void func_ov004_0220d02c(void *);
extern char *func_ov004_0220d268(void *);
extern void func_ov004_0220d38c(void *);
extern void func_ov004_0220d3b8(void *);
extern void func_ov004_0220d4dc(void *);
extern void *func_ov004_0220d840(void *);
extern void *func_ov004_0220e008(void *);
extern void *func_ov004_0220e474(void *);
extern void func_ov004_0223b250(void *);
extern void func_ov004_0223cfbc(void *);
extern int func_020b7ed8(int arg0);
extern void *func_020b7ee8(void *arg0);
extern void *func_ov004_0220e4d4(void *arg0);
extern void *func_ov004_0220e4ec(void *arg0);
extern void *data_ov004_0224fe6c;
extern void *data_ov004_0224ff18;
extern void *func_0203f080(void *);
extern void *func_02054e18(void *);
extern void *func_02066994(void *);
extern void func_0209d340(void *);
extern void *func_020b82d0(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*callback3)(void *));
extern void func_ov004_0220d028(void *);
extern int func_ov004_0220d258(void *);
extern void func_ov004_0220d388(void *);
extern void func_ov004_0220d3b4(void *);
extern void func_ov004_0220d4d8(void *);
extern void *func_ov004_0220d824(void *);
extern void *func_ov004_0220dff0(void *);
extern void *func_ov004_0220e458(void *);
extern void func_ov004_0223b248(void *);
extern void func_ov004_0223cfb8(void *);
extern void func_ov004_02211518(void *);

int func_ov004_022111ec(void)
{
    return 1;
}

void *func_ov004_022110e4(char *self)
{
    // DECLS
    // ENDDECLS
    func_0203f130(self);
    func_02066a30(self + 0xec);
    *(void **) (self) = &data_ov004_0224fe6c;
    *(void **) (self + 0xec) = &data_ov004_0224ff18;
    func_0209d34c(self + 0x132);
    func_ov004_0220d4dc(self + 0x17c);
    func_ov004_0220d840(self + 0x18c);
    __cxa_vec_ctor(self + 0x1d0, 0x4, 0x20, ((void (*)(void *)) func_020b7ee8), ((void (*)(void *)) func_020b7ed8));
    func_ov004_0223b250(self + 0x250);
    func_020b82ec(self + 0x28c);
    func_02054e54(self + 0x538);
    func_ov004_0220e008(self + 0x62c);
    func_ov004_0220e474(self + 0x6cc);
    func_ov004_0220d38c(self + 0x740);
    func_ov004_0220d3b8(self + 0x742);
    func_ov004_0220d268(self + 0x748);
    func_ov004_0220d02c(self + 0x764);
    func_ov004_0223cfbc(self + 0x798);
    __cxa_vec_ctor(self + 0x7c4, 0x4, 0x20, ((void (*)(void *)) func_ov004_0220e4ec),
                   ((void (*)(void *)) func_ov004_0220e4d4));
    return self;
}

void *func_ov004_02210fdc(char *self)
{
    // DECLS
    // ENDDECLS
    func_0203f130(self);
    func_02066a30(self + 0xec);
    *(void **) (self) = &data_ov004_0224fe6c;
    *(void **) (self + 0xec) = &data_ov004_0224ff18;
    func_0209d34c(self + 0x132);
    func_ov004_0220d4dc(self + 0x17c);
    func_ov004_0220d840(self + 0x18c);
    __cxa_vec_ctor(self + 0x1d0, 0x4, 0x20, ((void (*)(void *)) func_020b7ee8), ((void (*)(void *)) func_020b7ed8));
    func_ov004_0223b250(self + 0x250);
    func_020b82ec(self + 0x28c);
    func_02054e54(self + 0x538);
    func_ov004_0220e008(self + 0x62c);
    func_ov004_0220e474(self + 0x6cc);
    func_ov004_0220d38c(self + 0x740);
    func_ov004_0220d3b8(self + 0x742);
    func_ov004_0220d268(self + 0x748);
    func_ov004_0220d02c(self + 0x764);
    func_ov004_0223cfbc(self + 0x798);
    __cxa_vec_ctor(self + 0x7c4, 0x4, 0x20, ((void (*)(void *)) func_ov004_0220e4ec),
                   ((void (*)(void *)) func_ov004_0220e4d4));
    return self;
}

void *func_ov004_02210ee4(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_0224fe6c;
    *(void **) (self + 0xec) = &data_ov004_0224ff18;
    __cxa_vec_cleanup(self + 0x7c4, 0x4, 0x20, ((void (*)(void *)) func_ov004_0220e4d4));
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
    __cxa_vec_cleanup(self + 0x1d0, 0x4, 0x20, ((void (*)(void *)) func_020b7ed8));
    func_ov004_0220d824(self + 0x18c);
    func_ov004_0220d4d8(self + 0x17c);
    func_0209d340(self + 0x132);
    func_02066994(self + 0xec);
    func_0203f080(self);
    return self;
}

void *func_ov004_02210de8(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_0224fe6c;
    *(void **) (self + 0xec) = &data_ov004_0224ff18;
    __cxa_vec_cleanup(self + 0x7c4, 0x4, 0x20, ((void (*)(void *)) func_ov004_0220e4d4));
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
    __cxa_vec_cleanup(self + 0x1d0, 0x4, 0x20, ((void (*)(void *)) func_020b7ed8));
    func_ov004_0220d824(self + 0x18c);
    func_ov004_0220d4d8(self + 0x17c);
    func_0209d340(self + 0x132);
    func_02066994(self + 0xec);
    func_0203f080(self);
    func_ov004_02211518(self);
    return self;
}

void *func_ov004_02210cf0(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_0224fe6c;
    *(void **) (self + 0xec) = &data_ov004_0224ff18;
    __cxa_vec_cleanup(self + 0x7c4, 0x4, 0x20, ((void (*)(void *)) func_ov004_0220e4d4));
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
    __cxa_vec_cleanup(self + 0x1d0, 0x4, 0x20, ((void (*)(void *)) func_020b7ed8));
    func_ov004_0220d824(self + 0x18c);
    func_ov004_0220d4d8(self + 0x17c);
    func_0209d340(self + 0x132);
    func_02066994(self + 0xec);
    func_0203f080(self);
    return self;
}
