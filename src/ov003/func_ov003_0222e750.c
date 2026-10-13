/* func_ov003_0222e750 @ 0x0222e750, 0x6c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_ov003_022617bc[];
extern unsigned char data_ov003_02260994[];
extern void *func_0209d088(void *p);
extern void NNS_G3dMdlSetMdlAlpha(void *p, int a, int b);

void func_ov003_0222e750(int v)
{
    unsigned char *p;
    unsigned char i;
    i = v & 0xf;
    if ((v >> 4) & 1) {
        p = data_ov003_022617bc + i * 0x25c;
    } else if ((v >> 5) & 1) {
        p = data_ov003_02260994 + i * 0x25c;
    }
    if (p[0x250] == 3) {
        NNS_G3dMdlSetMdlAlpha(func_0209d088(p + 0x130), 0, 0);
    }
    p[0x251] = 0x10;
}
