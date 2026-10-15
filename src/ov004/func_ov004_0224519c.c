/* func_ov004_0224519c @ 0x0224519c, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int __cxa_vec_cleanup(void *, int, int, void (*callback3)(void *));
extern void *func_ov004_0223ecc8(char *arg0);
extern void *data_ov004_02259a34;

int func_ov004_0224519c(char *self)
{
    // DECLS
    // ENDDECLS
    return __cxa_vec_cleanup(&data_ov004_02259a34, 0x20, 0x2d8, ((void (*)(void *)) func_ov004_0223ecc8));
}
