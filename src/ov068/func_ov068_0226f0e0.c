/* func_ov068_0226f0e0 @ 0x0226f0e0, 0x98 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204f7e0(void *dst, void *src);
extern int FX_Div(int numer, int denom);
extern void *func_020b03f8(void);

int func_ov068_0226f0e0(void *self)
{
    unsigned short *p;
    void *base;
    unsigned int (*arr)[4];
    int mask;
    int diff_x;
    int diff_y;

    p = (unsigned short *) ((char *) self + 0x378);
    *p &= ~0x10;
    *p |= 0x20;

    func_0204f7e0((char *) self + 0x37C, (char *) self + 0x5C);

    mask = *(unsigned int *) ((char *) self + 8) & 1;
    base = func_020b03f8();
    mask = mask & 1;
    arr = (unsigned int (*)[4]) base;

    arr[mask][0] = 0;
    arr[mask][1] = 0;
    arr[mask][2] = 0;
    arr[mask][3] = 0x800;

    diff_x = *(int *) ((char *) self + 0x37C) - *(int *) ((char *) self + 0x5C);
    *(int *) ((char *) self + 0x314) = FX_Div(diff_x, 0x10000);

    diff_y = *(int *) ((char *) self + 0x384) - *(int *) ((char *) self + 0x64);
    *(int *) ((char *) self + 0x318) = FX_Div(diff_y, 0x10000);

    *(unsigned char *) ((char *) self + 0x399) = 0;

    return 1;
}
