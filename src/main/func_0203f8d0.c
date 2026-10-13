/* func_0203f8d0 @ 0x0203f8d0, 0xb4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    unsigned char pad_00[4];
    unsigned char unk_04;
} Mode;

typedef struct {
    unsigned char pad_00[8];
    volatile int unk_08;
    unsigned char pad_0C[4];
    int unk_10;
    int unk_14;
} Cam;

extern int FX_MulFunc(int a, int b);
extern int FX_Div(int a, int b);
extern const short FX_SinCosTable_[];

extern Mode *data_021f6948;
extern Cam data_021c749c;
extern int data_021c748c;

int func_0203f8d0(Vec3 *out, Vec3 *in)
{
    unsigned int ok;
    int base;
    int d;
    int t;
    short angle;
    int idx;

    if (data_021f6948->unk_04 == 1) {
        ok = 1;
    } else {
        ok = 0;
    }
    if (ok != 0) {
        base = in->y + 0x1f576;
        if (in->z <= data_021c749c.unk_08 - data_021c749c.unk_10) {
            d = in->z - (data_021c749c.unk_08 - data_021c749c.unk_10);
            if (d < 0) {
                d = -d;
            }
            base -= FX_MulFunc(data_021c749c.unk_14, d);
        }
        t = FX_Div(in->z, data_021c748c);
        t = 0x2999 * t;
        angle = (short) (t >> 12);
        out->x = in->x;
        idx = ((unsigned short) angle >> 4) << 1;
        out->y = FX_MulFunc(base, FX_SinCosTable_[idx + 1]);
        out->z = FX_MulFunc(base, FX_SinCosTable_[idx]);
        return angle;
    }
    out->x = in->x;
    out->y = in->y;
    out->z = in->z;
    return 0;
}
