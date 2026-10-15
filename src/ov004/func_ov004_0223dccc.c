/* func_ov004_0223dccc @ 0x0223dccc, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_02004280(void *argument0);
extern int func_02055454(int argument0);

int func_ov004_0223dccc(char *self)
{
    // DECLS
    // ENDDECLS
    func_02055454((int) (self + 0x120));
    *(int *) (self + 0x110) = 0x4;
    *(int *) (self + 0x8) = 0xffff;
    func_02004280(self + 0x114);
    return 0x1;
}
