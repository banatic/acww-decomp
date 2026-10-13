/* func_ov004_0223f9c8 @ 0x0223f9c8, 0x48 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209d180(void *, int, int, int, int, void *, void *, int);
extern void func_ov004_0223ef1c(void *);
extern void func_0205c978();
extern void func_0205c994();

int func_ov004_0223f9c8(char *self)
{
    // DECLS
    // ENDDECLS
    func_0209d180(self + 0x180, 0x20, 0x400, 0x40, 0x9c4, (void *) func_0205c994, (void *) func_0205c978, 0x0);
    func_ov004_0223ef1c(self);
    return 0x1;
}
