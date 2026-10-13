/* func_ov003_0222e4c0 @ 0x0222e4c0, 0x78 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov003_022617bc[];
extern char data_ov003_02260994[];
extern void *func_0209d088(void *p);
extern void NNS_G3dMdlSetMdlAlpha(void *p, int a, int b);

void func_ov003_0222e4c0(int v)
{
    char *p;
    unsigned char *q;
    unsigned char i;
    i = v & 0xf;
    p = (char *) v;
    if ((v >> 4) & 1) {
        p = data_ov003_022617bc + i * 0x25c;
    } else if ((v >> 5) & 1) {
        p = data_ov003_02260994 + i * 0x25c;
    }
    q = (unsigned char *) (p + 0x251);
    if (*q != 0x10) {
        return;
    }
    if (*(signed char *) (p + 0x24d) < 0) {
        return;
    }
    *q = 0x13;
    NNS_G3dMdlSetMdlAlpha(func_0209d088(p + 0x130), 0, 0x1f);
}
