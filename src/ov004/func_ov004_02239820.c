/* func_ov004_02239820 @ 0x02239820, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02054cac(void *, int, int, int, int, int, int);
extern int NNS_G3dGetJntAnmSet(int, int);
extern int func_02107b44(int, int);

int func_ov004_02239820(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    return func_02054cac(self + 0x64, func_02107b44(NNS_G3dGetJntAnmSet(*(int *) (self + (a1 << 2) + 0x54), a1), 0x0), 0x2,
                         0x0, 0x1000, 0x0, 0x0);
}
