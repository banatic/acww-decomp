/* func_ov004_0223d2d4 @ 0x0223d2d4, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_02138c48(void *, int, int, void *);
extern void func_ov004_0223d2b0(void *);
extern void func_020051b0();

void *func_ov004_0223d2d4(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0223d2b0(self);
    func_02138c48(self + 0x8, 0x2, 0x2, (void *) func_020051b0);
    return self;
}
