/* func_ov004_0222f0e8 @ 0x0222f0e8, 0x78 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_ctor(void *, int, int, void (*callback3)(void *), void (*callback4)(void *));
extern void *func_ov004_0222c87c(void *);
extern void *func_020551e0(void *arg0);
extern void *func_02055210(void *arg0);
extern void func_ov004_0222c394(void *element);
extern void func_ov004_0222c398(void *arg0);
extern int func_ov004_0222c538(int arg0);
extern int func_ov004_0222c548(int arg0);
extern void *data_ov004_02254fc8;

void *func_ov004_0222f0e8(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0222c87c(self);
    *(void **) (self) = &data_ov004_02254fc8;
    __cxa_vec_ctor(self + 0x290, 0x9, 0xb8, ((void (*)(void *)) func_02055210), ((void (*)(void *)) func_020551e0));
    __cxa_vec_ctor(self + 0x908, 0x9, 0xa4, ((void (*)(void *)) func_ov004_0222c548),
                   ((void (*)(void *)) func_ov004_0222c538));
    __cxa_vec_ctor(self + 0xecc, 0x9, 0x4, ((void (*)(void *)) func_ov004_0222c398), ((void (*)(void *)) func_ov004_0222c394));
    return self;
}
