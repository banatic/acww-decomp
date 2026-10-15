/* func_ov004_0220ff4c @ 0x0220ff4c, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0220ff74(void *, int, int);
extern void *data_ov004_0224fe10;

void func_ov004_0220ff4c(char *self, int a1, int a2)
{
    // DECLS
    // ENDDECLS
    func_ov004_0220ff74(self, a1,
                        (*(int *) ((char *) &data_ov004_0224fe10 + (*(int *) (self + 0x784) << 2)) + (0xc * (a2 & 0x3))));
}
