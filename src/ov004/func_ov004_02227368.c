/* func_ov004_02227368 @ 0x02227368, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_02010d64(void *);
extern void func_ov004_0222626c(void *, int, int);
extern int func_ov004_0222738c(void *);
extern void func_ov004_022273ec(void *);

int func_ov004_02227368(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_022273ec(self);
    func_ov004_0222626c(self, 0x1f, 0x6);
    func_02010d64(self);
    return func_ov004_0222738c(self);
}
