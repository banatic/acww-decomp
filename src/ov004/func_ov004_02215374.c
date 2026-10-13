/* func_ov004_02215374 @ 0x02215374, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_022150b8(void *);

int func_ov004_02215374(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_022150b8(self);
    *(void **) (self + 0x85c) = (char *) *(int *) (self + 0x85c) + 0x1;
    return 0x1;
}
