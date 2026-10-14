/* func_ov004_0223248c @ 0x0223248c, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_ctor(void *, int, int, void *, void *);
extern void func_020324c4();
extern void func_020324fc();

void *func_ov004_0223248c(char *self)
{
    // DECLS
    // ENDDECLS
    __cxa_vec_ctor(self, 0x2, 0x9c, (void *) func_020324fc, (void *) func_020324c4);
    return self;
}
