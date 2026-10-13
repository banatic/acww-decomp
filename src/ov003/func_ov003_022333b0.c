/* func_ov003_022333b0 @ 0x022333b0, 0xac bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov003_022356ec(void *a);
extern int func_ov003_022353e0(void *a, void *b);
extern short func_0200322c(void *a, void *b);
extern void *func_0209d088(void *a);
extern void NNS_G3dMdlSetMdlAlpha(void *a, int b, int c);
extern int func_020ea990(void *a, void *b);
extern void func_ov003_022353a4(void *a, int b, int c);

void func_ov003_022333b0(char *self, short *out)
{
    int *v = (int *) (self + 0x204);
    char *o = (char *) func_ov003_022356ec(v);
    if (func_ov003_022353e0(self, v)) {
        if (o != 0) {
            int h = func_0200322c(v, o + 0x5c);
            *(char *) (self + 0x251) = 5;
            NNS_G3dMdlSetMdlAlpha(func_0209d088(self + 0x130), 0, 0x1f);
            *(short *) (self + 0x23a) = (short) (h + 0x8000);
            *out = 0;
        }
    } else {
        int t;
        if (o != 0) {
            if (func_020ea990(v, o + 0x5c) < 0x5000) {
                *(char *) (self + 0x252) = 0x3c;
            }
        }
        t = *(unsigned char *) (self + 0x252);
        if (t > 0) {
            func_ov003_022353a4(self, 0, 1);
            *(char *) (self + 0x252) = (char) (t - 1);
        }
    }
}
