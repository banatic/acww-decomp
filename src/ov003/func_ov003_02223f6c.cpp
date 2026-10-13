/* func_ov003_02223f6c @ 0x02223f6c, 0x130 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    unsigned char unk_0C;
    unsigned char unk_0D;
    signed char unk_0E;
    unsigned char unk_0F;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1C;
} UnkStruct_02223f6c;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
} UnkStruct_02223f6c_2;

typedef struct {
    char pad_00[0x18];
    UnkStruct_02223f6c_2 **unk_18;
    int unk_1C;
    int unk_20;
    int unk_24;
    int unk_28;
} UnkStruct_02223f6c_3;

// The computed position; the empty destructor keeps the frame bytes the ROM reserves for it.
struct Vec3 {
    int x, y, z;
    Vec3() {}
    ~Vec3() {}
};

extern "C" short FX_SinCosTable_[];
extern "C" int data_ov003_02236bb8[][4];

extern "C" void func_ov003_02223f6c(UnkStruct_02223f6c *self, UnkStruct_02223f6c_3 *out)
{
    int v;
    int a;
    int lim;
    int c;
    int idx;
    Vec3 pos;

    v = data_ov003_02236bb8[self->unk_00][self->unk_0C];
    switch (self->unk_08) {
        case 3:
            switch (self->unk_0F) {
                case 4:
                    lim = 0x10;
                    a = 0xffffc000;
                    break;
                case 5:
                    lim = 0x10;
                    a = 0x4000;
                    break;
                case 6:
                    lim = 9;
                    a = 0xffffe000;
                    break;
                case 7:
                    lim = 9;
                    a = 0x2000;
                    break;
            }
            c = self->unk_0E;
            if (c < lim) {
                a = (short) ((c * a) / lim);
            }
            idx = ((u16) a >> 4) << 1;
            pos.x = self->unk_14 + (FX_SinCosTable_[idx] * v >> 12);
            pos.y = self->unk_18 + (FX_SinCosTable_[idx + 1] * v >> 12);
            pos.z = self->unk_1C;
            break;
        case 4:
            switch (self->unk_0F) {
                case 4:
                    a = 0xffffc000;
                    break;
                case 5:
                    a = 0x4000;
                    break;
                case 6:
                    a = 0xffffe000;
                    break;
                case 7:
                    a = 0x2000;
                    break;
            }
            idx = ((u16) a >> 4) << 1;
            pos.x = self->unk_14 + (FX_SinCosTable_[idx] * v >> 12);
            pos.y = self->unk_18 + (FX_SinCosTable_[idx + 1] * v >> 12);
            pos.z = self->unk_1C;
            break;
        default:
            pos.x = self->unk_14;
            pos.y = self->unk_18 + v;
            pos.z = self->unk_1C;
            break;
    }
    out->unk_20 = pos.x + (*out->unk_18)->unk_04;
    out->unk_24 = pos.y + (*out->unk_18)->unk_08;
    out->unk_28 = pos.z + (*out->unk_18)->unk_0C;
}
