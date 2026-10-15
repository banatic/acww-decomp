/* func_020f6a80 @ 0x020f6a80, 0x120 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x14];
    u8 unk_14[0x14];
    u8 unk_28[0x11];
    s8 unk_39;
    u8 unk_3A;
    u8 unk_3B;
    u8 unk_3C;
} UnkStruct_020f6a80;

typedef struct {
    u8 pad_00[8];
    u16 unk_08;
    u8 pad_0A;
    s8 unk_0B;
    u8 pad_0C[2];
    s8 unk_0E;
    u8 pad_0F;
    s8 unk_10;
    s8 unk_11;
} Param;

typedef struct {
    u8 pad_00[0x30];
    UnkStruct_020f6a80 *inner;
} Glb;

extern Glb data_021fd1bc;

typedef struct {
    u8 pad_00[0xc];
    u8 unk_0C;
} Misc;
extern Misc data_02138fd4;

extern int func_020eed18(int, int);
extern int func_020f6d78(void *obj, u8 byte);

int func_020f6a80(Param *self)
{
    s8 state = self->unk_10;
    u8 nextb;
    int result;

    if (state == 0) {
        if (self->unk_0B == 0xf) {
            func_020eed18((int) self, 0);
            data_021fd1bc.inner->unk_3C = 0;
            return 1;
        }
    } else {
        u8 v = (u8) (s8) (state - 1);
        if (v <= 1) {
            if (self->unk_0B == 0x17) {
                func_020eed18((int) self, 0);
                data_021fd1bc.inner->unk_3C = 0;
                return 1;
            }
        } else if (state == 3) {
            if (self->unk_0B == data_02138fd4.unk_0C + 6) {
                func_020eed18((int) self, 0);
                data_021fd1bc.inner->unk_3C = 0;
                return 1;
            }
        }
    }

    nextb = (u8) (self->unk_0B + 1);
    result = func_020f6d78(self, nextb);
    if (result == 0xe) {
        goto ret0;
    }
    if (result == 0xf) {
        if (self->unk_11 == 1) {
            goto ret0;
        }
    }
    func_020eed18((int) self, 0);
ret0:
    return 0;
}
