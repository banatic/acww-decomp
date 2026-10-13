/* func_ov003_02232598 @ 0x02232598, 0x3c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0209d088(void *a);
extern int NNS_G3dMdlGetMdlAlpha(void *a, int b);
extern void NNS_G3dMdlSetMdlAlpha(void *a, int b, int c);

int func_ov003_02232598(char *self, int d)
{
    char *m = self + 0x130;
    int a = NNS_G3dMdlGetMdlAlpha(func_0209d088(m), 0);
    if (a > 7) {
        NNS_G3dMdlSetMdlAlpha(func_0209d088(m), 0, a - d);
    } else {
        return 1;
    }
    return 0;
}
