/* func_ov004_02232470 @ 0x02232470, 0x1c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *, int, int, void (*callback3)(void *));
extern void *func_020324c4(void *arg0);

void *func_ov004_02232470(char *self)
{
    // DECLS
    // ENDDECLS
    __cxa_vec_cleanup(self, 0x2, 0x9c, ((void (*)(void *)) func_020324c4));
    return self;
}
