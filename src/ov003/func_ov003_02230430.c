/* func_ov003_02230430 @ 0x02230430, 0x80 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02230ce8(void *a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern void *func_0209d088(void *a);
extern void NNS_G3dMdlSetMdlAlpha(void *a, int b, int c);

void func_ov003_02230430(char *self)
{
    int t;
    if (*(signed char *) (self + 0x24d) == 0x1e) {
        func_ov003_02230ce8(self, 0, 0x28, 0x50, 0, 0, 0, 0, 4, 0);
    } else {
        func_ov003_02230ce8(self, 0, 0xdc, 0x3c, 0, 0, 0, 0, 1, 0);
    }
    *(short *) (self + 0x232) = 0x168;
    t = *(unsigned char *) (self + 0x251);
    if (t != 0xb && t != 0x10) {
        NNS_G3dMdlSetMdlAlpha(func_0209d088(self + 0x130), 0, 0);
    }
}
