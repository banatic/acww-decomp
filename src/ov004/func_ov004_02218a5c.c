/* func_ov004_02218a5c @ 0x02218a5c, 0x40 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0220cfec(void *, int);
extern void func_ov004_0221041c(void *, int, int, int, int);

int func_ov004_02218a5c(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0220cfec(self + 0x764, 0x0);
    if (*(int *) (self + 0x780) == 0x9 || *(int *) (self + 0x780) == 0x2c) {
        func_ov004_0221041c(self, 0x0, 0x0, 0x1000, 0x0);
    }
    return 0x1;
}
