/* func_ov004_02239d34 @ 0x02239d34, 0x74 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209d2b8(void *);
extern void *func_020ee660(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*callback3)(void *), void (*callback4)(void *));
extern void *func_ov004_02239c40(void *);
extern void *func_020b82d0(void *arg0);
extern void *func_020b82ec(void *arg0);
extern int func_ov004_02239c5c(int arg0);
extern int func_ov004_02239da8(int arg0);
extern void *data_020da13c;
extern void *data_ov004_02255ebc;

void *func_ov004_02239d34(char *self)
{
    // DECLS
    // ENDDECLS
    func_020ee660(self);
    *(void **) (self) = &data_020da13c;
    *(void **) (self) = &data_ov004_02255ebc;
    __cxa_vec_ctor(self + 0x50, 0x5, 0x64, ((void (*)(void *)) func_ov004_02239da8), ((void (*)(void *)) func_ov004_02239c5c));
    func_ov004_02239c40(self + 0x244);
    __cxa_vec_ctor(self + 0x2a8, 0x2, 0x2a8, ((void (*)(void *)) func_020b82ec), ((void (*)(void *)) func_020b82d0));
    func_0209d2b8(self + 0x7f8);
    return self;
}
