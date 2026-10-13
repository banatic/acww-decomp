/* func_ov003_02230f60 @ 0x02230f60, 0x28 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0209d088(void *p);
extern void NNS_G3dMdlSetMdlAlpha(void *mdl, int a, int b);

void func_ov003_02230f60(unsigned char *p)
{
    p[0x250] = 4;
    NNS_G3dMdlSetMdlAlpha(func_0209d088(p + 0x130), 0, 0);
}
