/* func_ov004_0222269c @ 0x0222269c, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_022226d4(void);

void func_ov004_0222269c(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    if (a1 == 0x4) {
        func_ov004_022226d4();
        *(int *) ((char *) *(int *) (self + 0x40) + 0x8) = 0x1;
    }
}
