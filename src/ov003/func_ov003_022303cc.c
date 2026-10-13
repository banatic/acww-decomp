/* func_ov003_022303cc @ 0x022303cc, 0x54 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02230ce8(void *a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern void *func_0209d088(void *a);
extern void NNS_G3dMdlSetMdlAlpha(void *a, int b, int c);

void func_ov003_022303cc(char *self)
{
    if (*(unsigned char *) (self + 0x251) == 0x13) {
        NNS_G3dMdlSetMdlAlpha(func_0209d088(self + 0x130), 0, 0);
    }
    func_ov003_02230ce8(self, 0, 0x5a, 0x3c, 0, 0, 2, 0, 0, 0);
    *(int *) (self + 0x21c) = 0;
}
