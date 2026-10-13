/* func_ov095_0229a1ec @ 0x0229a1ec, 0x94 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229a1ec {
    unsigned char unk_00[0x18];
    unsigned char unk_18;
    unsigned char pad_19[0x0F];
    int unk_28;
} UnkStruct_0229a1ec;

extern int func_ov095_0229ae5c(UnkStruct_0229a1ec *self, int index);
extern int func_ov095_0229ad90(UnkStruct_0229a1ec *self, int index);
extern int func_ov095_022999b0(UnkStruct_0229a1ec *self, int value);

void func_ov095_0229a1ec(UnkStruct_0229a1ec *self, int value)
{
    int best;
    int i;
    int diff;

    if (value < 0x80) {
        self->unk_28 = 0x109;
        best = value - 0x18;
    } else {
        self->unk_28 = 0x10a;
        best = value - 0xe8;
    }

    for (i = 0; i < 3; i++) {
        diff = value - func_ov095_0229ae5c(self, i + 0xf8);
        if (diff < 0) {
            diff = -diff;
        }
        if (diff < best) {
            best = diff;
            self->unk_28 = i + 0xf8;
        }
    }

    if (func_ov095_022999b0(self, 4) != 0) {
        if (best < 0) {
            best = -best;
        }
        for (i = 0; i < self->unk_18; i++) {
            diff = value - func_ov095_0229ad90(self, i + 0x10c);
            if (diff < 0) {
                diff = -diff;
            }
            if (diff < best) {
                best = diff;
                self->unk_28 = i + 0x10c;
            }
        }
    }
}
