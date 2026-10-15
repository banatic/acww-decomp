/* func_ov004_022392a0 @ 0x022392a0, 0xb4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern const unsigned char data_ov004_02247927[];
extern char data_ov004_022593dc[];
extern char data_ov004_022593c4[];
extern int func_ov004_02239bb4(int *a, int b, int c);
extern int func_02031168(int *a, int lim, void *tbl, int m, int q);

int func_ov004_022392a0(void *self)
{
    int a[3];
    int ok = 0;
    int lim;
    int v;

    a[0] = *(int *) ((char *) self + 0x1a8);
    a[1] = *(int *) ((char *) self + 0x1ac);
    a[2] = *(int *) ((char *) self + 0x1b0);
    func_ov004_02239bb4(a, ((int) data_ov004_02247927[*(int *) ((char *) self + 0x15c) * 0x11] << 12) >> 7,
                        *(short *) ((char *) self + 0x1c0));
    lim = 0x400;
    if (*((unsigned char *) self + 0x1fc) != 0) {
        lim = 0x1000;
    }
    v = *(int *) ((char *) self + 0x15c);
    if (v == 0x19 || v < 0x11) {
        if (func_02031168(a, lim, data_ov004_022593dc, 0xfc00, 0x3c00) != 0) {
            ok = 1;
        }
    } else {
        if (func_02031168(a, lim, data_ov004_022593c4, 0xfc00, 0x3c00) != 0) {
            ok = 1;
        }
    }
    return ok;
}
