/* func_ov004_022274a0 @ 0x022274a0, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_02010d64(void *);
extern void func_ov004_0222626c(void *, int, int);
extern int func_ov004_022274c4(void *);
extern void func_ov004_02227524(void *);

int func_ov004_022274a0(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_02227524(self);
    func_ov004_0222626c(self, 0x1f, 0x6);
    func_02010d64(self);
    return func_ov004_022274c4(self);
}
