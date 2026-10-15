/* func_ov004_0223c7f4 @ 0x0223c7f4, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_ctor(void *, int, int, void (*callback3)(void *), void (*callback4)(void *));
extern void func_ov004_0223c7b8(void *);
extern void func_ov004_0223cbe0(void *element);
extern void func_ov004_0223cbe4(void *element);

void *func_ov004_0223c7f4(char *self)
{
    // DECLS
    // ENDDECLS
    __cxa_vec_ctor(self, 0x2, 0x40, ((void (*)(void *)) func_ov004_0223cbe4), ((void (*)(void *)) func_ov004_0223cbe0));
    func_ov004_0223c7b8(self);
    return self;
}
