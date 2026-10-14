/* func_ov004_0223ab7c @ 0x0223ab7c, 0x1c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *, int, int, void *);
extern void func_ov004_0223adb4();

void *func_ov004_0223ab7c(char *self)
{
    // DECLS
    // ENDDECLS
    __cxa_vec_cleanup(self + 0x4, 0x2, 0xa8, (void *) func_ov004_0223adb4);
    return self;
}
