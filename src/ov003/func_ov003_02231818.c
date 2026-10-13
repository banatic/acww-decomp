/* func_ov003_02231818 @ 0x02231818, 0x84 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02233e4c(void *a, void *b);
extern void func_ov003_02230f60(void *a);
extern void *func_0209d088(void *a);
extern void NNS_G3dMdlSetMdlAlpha(void *a, int b, int c);

void func_ov003_02231818(char *self, short *out)
{
    int t[4];
    if (*(unsigned char *) (self + 0x254) == 0xfe) {
        *(char *) (self + 0x251) = 8;
    } else {
        func_ov003_02233e4c(self, t);
        if (t[0] != 0) {
            int a = (short) (0x1f * (*(unsigned char *) (self + 0x255) - *(unsigned char *) (self + 0x254)) /
                             *(unsigned char *) (self + 0x255));
            if (a <= 0) {
                func_ov003_02230f60(self);
                *(char *) (self + 0x24a) = 1;
                *out = 0;
            } else {
                if (a > 0x1f) {
                    a = 0x1f;
                }
                NNS_G3dMdlSetMdlAlpha(func_0209d088(self + 0x130), 0, a);
            }
        }
    }
}
