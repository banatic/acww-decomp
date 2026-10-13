/* func_ov095_0229ab68 @ 0x0229ab68, 0xc2 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x28];
    int unk_28;
    int unk_2C;
    int unk_30;
} UnkStruct_0229ab68;

extern int func_ov095_0229ac2c(UnkStruct_0229ab68 *self);

void func_ov095_0229ab68(UnkStruct_0229ab68 *self)
{
    int v;

    if (func_ov095_0229ac2c(self) != 0) {
        return;
    }

    v = self->unk_28;
    if (v < 0x3b) {
        return;
    }

    if (v <= 0x46) {
        self->unk_30 = 0x68;
        self->unk_2C = (self->unk_28 - 0x3b) * 0x14 + 0xe;
        return;
    }

    if (v <= 0x51) {
        self->unk_30 = 0x78;
        self->unk_2C = (self->unk_28 - 0x47) * 0x14 + 0x16;
        if (self->unk_28 == 0x51) {
            self->unk_2C = self->unk_2C + 0xa;
        }
        return;
    }

    if (v <= 0x5c) {
        self->unk_30 = 0x88;
        self->unk_2C = (self->unk_28 - 0x52) * 0x14 + 0xe;
        if (self->unk_28 == 0x5c) {
            self->unk_2C = self->unk_2C + 0xe;
        }
        return;
    }

    if (v <= 0x67) {
        self->unk_30 = 0x98;
        self->unk_2C = (self->unk_28 - 0x5d) * 0x14 + 0x16;
        if (self->unk_28 == 0x5d) {
            self->unk_2C = self->unk_2C - 3;
        }
        return;
    }

    if (v <= 0x6f) {
        int w;
        self->unk_30 = 0xa8;
        w = self->unk_28;
        if (w < 0x6b) {
            self->unk_2C = (w - 0x68) * 0x14 + 0x22;
        } else if (w == 0x6b) {
            self->unk_2C = 0x86;
        } else {
            self->unk_2C = (w - 0x6c) * 0x14 + 0xae;
        }
    }
}
