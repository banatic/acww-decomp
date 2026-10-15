/* func_ov004_0220d824 @ 0x0220d824, 0x1c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *, int, int, void (*callback3)(void *));
extern void func_ov004_0220d9a0(void *element);

void *func_ov004_0220d824(char *self)
{
    // DECLS
    // ENDDECLS
    __cxa_vec_cleanup(self + 0x4, 0x4, 0x10, ((void (*)(void *)) func_ov004_0220d9a0));
    return self;
}
