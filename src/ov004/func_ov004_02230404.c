/* func_ov004_02230404 @ 0x02230404, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O1,s
 */

extern int func_ov004_0222c340(void *, void *);
extern void func_ov004_0222c3d4(void *, int, void *);

int func_ov004_02230404(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    func_ov004_0222c3d4(self + 0x4b8 + (0xa4 * a1), (0xa4 * a1), self + 0x4b8);
    return func_ov004_0222c340(self + 0x6a4 + (a1 << 2), self + 0x6a4);
}
