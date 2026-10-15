/* func_ov004_02233fd8 @ 0x02233fd8, 0x1c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *, int, int, void (*callback3)(void *));
extern void *func_ov004_02233ff4(char *arg0);

void *func_ov004_02233fd8(char *self)
{
    // DECLS
    // ENDDECLS
    __cxa_vec_cleanup(self, 0xf, 0x94, ((void (*)(void *)) func_ov004_02233ff4));
    return self;
}
