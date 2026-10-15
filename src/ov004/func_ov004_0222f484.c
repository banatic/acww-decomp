/* func_ov004_0222f484 @ 0x0222f484, 0x5c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020321bc(void *, int, int, int, void *, int, int);
extern int func_020b6590(void);
extern int func_020b7dc8(int, void *, void *, int, int, int, int, int, int);

int func_ov004_0222f484(char *self)
{
    // DECLS
    // ENDDECLS
    return func_020b7dc8(
        ((void) (func_020321bc(self + 0x2d8, 0x2000, 0x4000, 0x2000, self + 0x5c, 0x0, 0x0)), func_020b6590()), self + 0x374,
        self + 0x5c, 0x2000, 0x4000, 0x2000, 0x0, 0xc, 0xff);
}
