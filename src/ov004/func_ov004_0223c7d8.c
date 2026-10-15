/* func_ov004_0223c7d8 @ 0x0223c7d8, 0x1c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *, int, int, void (*callback3)(void *));
extern void func_ov004_0223cbe0(void *element);

void *func_ov004_0223c7d8(char *self)
{
    // DECLS
    // ENDDECLS
    __cxa_vec_cleanup(self, 0x2, 0x40, ((void (*)(void *)) func_ov004_0223cbe0));
    return self;
}
