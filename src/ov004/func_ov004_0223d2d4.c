/* func_ov004_0223d2d4 @ 0x0223d2d4, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *, int, int, void (*callback3)(void *));
extern void func_ov004_0223d2b0(void *);
extern void func_020051b0(void *arg0);

void *func_ov004_0223d2d4(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0223d2b0(self);
    __cxa_vec_cleanup(self + 0x8, 0x2, 0x2, ((void (*)(void *)) func_020051b0));
    return self;
}
