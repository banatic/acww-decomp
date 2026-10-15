/* func_ov004_0220c9fc @ 0x0220c9fc, 0x16c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#pragma opt_common_subs off
typedef struct {
    int x, y, z;
} UnkStruct_0220c9fc;

typedef struct {
    unsigned char pad_00[0x150];
    int unk_150;
    int unk_154;
    int unk_158;
    int unk_15C;
    unsigned short unk_160;
    unsigned short unk_162;
    short unk_164;
    unsigned char pad_166[2];
    int unk_168;
    unsigned char pad_16C[0x770 - 0x16c];
    unsigned short unk_770;
} RoomObject;

extern short FX_SinCosTable_[];
static inline short sine(unsigned short idx)
{
    return FX_SinCosTable_[(idx >> 4) * 2];
}

extern int func_020e895c(int *p, int a, int b);
extern int func_02095380(int a);
extern void func_ov004_0220fefc(RoomObject *self, UnkStruct_0220c9fc *out);
extern int func_ov004_0220e61c(RoomObject *self, UnkStruct_0220c9fc *out);
extern int FX_MulFunc(int a, int b);
extern int func_ov004_0220ccf8(RoomObject *self, int a);
extern void func_ov004_0220e5dc(RoomObject *self, int a);

void func_ov004_0220c9fc(RoomObject *self)
{
    UnkStruct_0220c9fc local;
    short orig162;
    unsigned short u162;
    int absval;
    int r0;

    func_020e895c(&self->unk_15C, 0x1000, 0x88);

    if (self->unk_160 < 0xf) {
        self->unk_160++;
        self->unk_770 = 0;
        if (self->unk_160 == 0xc) {
            func_02095380(0x4c7);
        }
        if (self->unk_160 == 0xf) {
            func_ov004_0220fefc(self, &local);
            func_ov004_0220e61c(self, &local);
        }
    } else if (self->unk_160 < 0x11) {
        self->unk_160++;
    } else {
        orig162 = self->unk_162;
        self->unk_162 += self->unk_164;
        u162 = self->unk_162;

        r0 = FX_MulFunc(self->unk_168, sine((short) u162));
        self->unk_154 = r0 + 0x1000;
        self->unk_150 = 0x1000 - r0;
        self->unk_158 = self->unk_150;

        if (FX_MulFunc(sine(orig162), sine((short) u162)) < 0) {
            self->unk_168 = FX_MulFunc(self->unk_168, 0x4cd);
            self->unk_164 += 0x960;
        }

        if (self->unk_15C == 0x1000) {
            absval = self->unk_168;
            if (absval < 0) {
                absval = -absval;
            }
            if (absval < 0x52) {
                func_ov004_0220ccf8(self, 1);
            }
        }

        switch (self->unk_770) {
            case 0:
                func_ov004_0220e5dc(self, 0);
                func_ov004_0220e5dc(self, 2);
                break;
            case 2:
                func_ov004_0220e5dc(self, 1);
                func_ov004_0220e5dc(self, 3);
                break;
        }
        self->unk_770++;
    }
}
