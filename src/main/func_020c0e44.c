/* func_020c0e44 @ 0x020c0e44, 0xc0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned char unk_02;
    unsigned char unk_03;
} UnkStruct_020c0e44;

extern unsigned int func_0209def4(unsigned short *p);
extern unsigned int CARDi_GetTargetMode(void);
extern int FX_MulFunc(int a, int b);
extern int FX_Sqrt(int a);
extern int FX_Div(int a, int b);

int func_020c0e44(int *out)
{
    UnkStruct_020c0e44 t;
    int ret = 1;
    unsigned int h, m, base, secs;
    int q, d, s;

    func_0209def4((unsigned short *) &t);
    h = t.unk_01;
    m = t.unk_00;
    base = CARDi_GetTargetMode();
    secs = 0;
    if (h >= 0x13) {
        secs = base + (0x3c * m + 0xe10 * (h - 0x13));
    } else if (h < 4) {
        secs = base + (0xe10 * h + 0x4650 + 0x3c * m);
    } else {
        ret = 0;
    }
    if (ret != 0) {
        int a;
        q = (int) ((secs << 12) / 0x7e90);
        a = FX_MulFunc(0xffee0000, q) + 0x110000;
        d = q - 0x800;
        s = FX_Sqrt(0x1000 - FX_MulFunc(d, d));
        s = FX_Div(s - 0xddb, 0x225);
        out[0] = a;
        out[1] = s * -16 + 0x3c000;
        out[2] = 0;
    }
    return ret;
}
