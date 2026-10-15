/* func_ov004_0222f028 @ 0x0222f028, 0x64 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_020edf54(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*callback3)(void *));
extern void *func_ov004_0222c7a0(void *);
extern void *func_020551e0(void *arg0);
extern void func_ov004_0222c394(void *element);
extern int func_ov004_0222c538(int arg0);
extern void *data_ov004_02254fc8;

void *func_ov004_0222f028(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_02254fc8;
    __cxa_vec_cleanup(self + 0xecc, 0x9, 0x4, ((void (*)(void *)) func_ov004_0222c394));
    __cxa_vec_cleanup(self + 0x908, 0x9, 0xa4, ((void (*)(void *)) func_ov004_0222c538));
    __cxa_vec_cleanup(self + 0x290, 0x9, 0xb8, ((void (*)(void *)) func_020551e0));
    func_ov004_0222c7a0(self);
    func_020edf54(self);
    return self;
}
