/* func_ov003_0222e2d8 @ 0x0222e2d8, 0x80 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov003_0223c146[];
extern void *func_0209d088(void *a);
extern int NNS_G3dMdlGetMdlAlpha(void *a, int b);
extern void func_0205510c(void *a, void *b);
extern int func_ov003_0222e264(void *a, void *b);
extern void func_020acdcc(void *a, int b, int c, unsigned char d);

void func_ov003_0222e2d8(void *ctx, char *o)
{
    int *p = (int *) (o + 0x210);
    if (*p > 0) {
        int v;
        int t = (0x1f - NNS_G3dMdlGetMdlAlpha(func_0209d088(o + 0x130), 0)) * 2;
        if (t > 0x1f) {
            v = 0;
        } else {
            v = 0x1f - t;
        }
        func_0205510c(o + 0x50, p);
        if (func_ov003_0222e264(ctx, o)) {
            func_020acdcc(o + 0x204, *(unsigned short *) (data_ov003_0223c146 + 6 * *(signed char *) (o + 0x24d)), 0x9000,
                          (unsigned char) v);
        }
    }
}
