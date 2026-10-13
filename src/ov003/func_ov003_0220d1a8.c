/* func_ov003_0220d1a8 @ 0x0220d1a8, 0xc0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_0200fa1c(int *dst, void *self, const u8 *a, const u8 *b, const u8 *data);
extern int func_0201005c(void *self, int *data, int len);
extern int func_0200ff28(void *self, int *data, int mode, int val);
extern int func_0200fd04(void *self, int *data, int mode);
extern u8 data_ov003_02236608[];

typedef struct {
    u8 pad_00[0x5c];
    u8 sub5c[0x32];
    u8 sub8e[0xca];
    int unk_158;
    int unk_15C;
    int unk_160;
    u8 pad_164[0x0c];
    int unk_170;
} UnkStruct_0220d1a8;

int func_ov003_0220d1a8(UnkStruct_0220d1a8 *self, int *param)
{
    int triplet[3];
    int gen[3];

    if (self->unk_170 == 1) {
        func_0200fa1c(gen, self, self->sub5c, self->sub8e, data_ov003_02236608);
        triplet[0] = gen[0];
        triplet[1] = gen[1];
        triplet[2] = gen[2];

        if (func_0201005c(self, triplet, 0xd) != 0 && func_0200ff28(self, triplet, 2, *param) != 0 &&
            func_0200fd04(self, triplet, 0) != 0) {
            return 1;
        }
    } else {
        triplet[0] = self->unk_158;
        triplet[1] = self->unk_15C;
        triplet[2] = self->unk_160;

        if (func_0201005c(self, triplet, 0xd) != 0 && func_0200ff28(self, triplet, 2, *param) != 0 &&
            func_0200fd04(self, triplet, 0) != 0) {
            return 1;
        }
    }

    return 0;
}
