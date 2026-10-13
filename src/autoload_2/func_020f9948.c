/* func_020f9948 @ 0x020f9948, 0x208 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

typedef struct {
    unsigned char pad_00[0x1a];
    short unk_1A;
} UnkStruct_020f9948;

typedef struct {
    unsigned char pad_00[0x2c];
    UnkStruct_020f9948 *pA;
} UnkStruct_020f9948_2;

typedef struct {
    unsigned char pad_00[9];
    signed char unk_09;
    signed char unk_0A;
    signed char unk_0B;
    signed char unk_0C;
    signed char unk_0D;
    signed char unk_0E;
    unsigned char pad_0F;
    unsigned char unk_10;
} UnkStruct_020f9948_3;

extern short data_021fd26c;
extern UnkStruct_020f9948_2 data_021fd1bc;
extern short data_021fd270;
extern void NNS_SndPlayerReadVariable(UnkStruct_020f9948_3 *self, int idx, short *out);
extern int FX_Div(int a, int b);

int func_020f9948(UnkStruct_020f9948_3 *self)
{
    short v0, v1;
    int d, r5, r4, t;
    UnkStruct_020f9948 *pa;

    if (self->unk_09 == 1 || self->unk_09 == 3) {
        v0 = self->unk_0C;
        d = data_021fd26c - v0;
        if (d < 0) {
            d += 0x10;
        }
        r4 = d << 14;
        pa = data_021fd1bc.pA;
        if (pa == 0) {
            return 0;
        }
        if (pa->unk_1A == 1) {
            t = data_021fd270;
            if (t < 0x20) {
                r4 += (t << 14) >> 5;
            } else {
                t -= 0x20;
                r4 += (t << 14) >> 4;
            }
        } else {
            r4 += FX_Div(data_021fd270 << 14, 0x18000);
        }
        if (self->unk_0A == 2) {
            r4 <<= 1;
            if (r4 > 0x40000) {
                r4 -= 0x40000;
            }
        }
    } else {
        NNS_SndPlayerReadVariable(self, 7, &v0);
        NNS_SndPlayerReadVariable(self, 0xc, &v1);
        d = data_021fd26c - v0;
        if (d < 0) {
            d += 0x10;
        }
        switch (self->unk_0A) {
            case 1:
            case 2:
            case 4:
                r5 = self->unk_0A;
                break;
            case 0x63:
                r5 = self->unk_0E;
                break;
        }
        pa = data_021fd1bc.pA;
        if (pa == 0) {
            return 0;
        }
        switch (pa->unk_1A) {
            case 0:
                r4 = 0x18;
                break;
            case 1:
                t = data_021fd270;
                if (t < 0x20) {
                    r4 = 0x20;
                } else {
                    data_021fd270 = (short) (t - 0x20);
                    r4 = 0x10;
                }
                break;
        }
        if (self->unk_10 == 0) {
            if (d >= r5) {
                self->unk_10 = 1;
            }
        }
        if (self->unk_10 != 0) {
            if (self->unk_0B == 0) {
                self->unk_10 = 0;
            }
        }
        if (self->unk_10 != 0) {
            r4 = 0;
        } else {
            r4 = FX_Div((d * r4 + data_021fd270) << 12, (r5 * r4) << 12) << 6;
        }
    }
    return r4;
}
