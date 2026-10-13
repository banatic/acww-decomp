/* func_ov004_0222d0bc @ 0x0222d0bc, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_02055124(void *);
extern void func_02056ffc(void *);
extern int func_ov004_0222d30c(void *, int);

int func_ov004_0222d0bc(char *self)
{
    // DECLS
    // ENDDECLS
    func_02055124(self + 0xec);
    func_02056ffc(self + 0x290);
    *(int *) ((char *) *(int *) (self + 0x2a8)) = *(int *) (self + 0x298);
    return func_ov004_0222d30c(self, 0x0);
}
