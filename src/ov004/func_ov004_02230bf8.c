/* func_ov004_02230bf8 @ 0x02230bf8, 0x84 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_020565c8(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*callback3)(void *), void (*callback4)(void *));
extern void *func_ov004_0222c87c(void *);
extern void *func_020551e0(void *arg0);
extern void *func_02055210(void *arg0);
extern void func_ov004_0222c394(void *element);
extern void func_ov004_0222c398(void *arg0);
extern int func_ov004_0222c538(int arg0);
extern int func_ov004_0222c548(int arg0);
extern void *data_ov004_02255674;

void *func_ov004_02230bf8(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0222c87c(self);
    *(void **) (self) = &data_ov004_02255674;
    __cxa_vec_ctor(self + 0x290, 0x3, 0xb8, ((void (*)(void *)) func_02055210), ((void (*)(void *)) func_020551e0));
    __cxa_vec_ctor(self + 0x4b8, 0x3, 0xa4, ((void (*)(void *)) func_ov004_0222c548),
                   ((void (*)(void *)) func_ov004_0222c538));
    __cxa_vec_ctor(self + 0x6a4, 0x3, 0x4, ((void (*)(void *)) func_ov004_0222c398), ((void (*)(void *)) func_ov004_0222c394));
    func_020565c8(self + 0x6b4);
    return self;
}
