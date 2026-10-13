/* func_02055d0c @ 0x02055d0c, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int NNS_G3dGetResultMtx(void *ptr, int a, int b, int c);
extern int NNS_G3dGlbGetInvV(void);
extern int MTX_Concat43(int a, int b, int c);

int func_02055d0c(char *a, int b, int c)
{
    if (!NNS_G3dGetResultMtx(a + 8, b, 0, c)) {
        return 0;
    }
    MTX_Concat43(b, NNS_G3dGlbGetInvV(), b);
    return 1;
}
