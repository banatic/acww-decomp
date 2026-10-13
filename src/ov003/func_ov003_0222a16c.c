/* func_ov003_0222a16c @ 0x0222a16c, 0x1c4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} UnkStruct_0222a16c;

typedef struct {
    char pad_00[0x120];
    UnkStruct_0222a16c unk_120;
    char pad_12C[0x1fe - 0x12c];
    u8 unk_1FE;
    char pad_1FF[0x218 - 0x1ff];
    UnkStruct_0222a16c unk_218;
} UnkStruct_0222a16c_2;

extern void func_0204f818(int *x, int *z, UnkStruct_0222a16c *p);
extern int func_02031b5c(int x, int z);
extern int func_ov003_0222a088(UnkStruct_0222a16c_2 *s);
extern int func_ov003_0222a378(UnkStruct_0222a16c_2 *s);
extern int func_ov003_0222a330(UnkStruct_0222a16c_2 *s);

int func_ov003_0222a16c(UnkStruct_0222a16c_2 *self)
{
    int ret;
    int px, pz;
    int t;

    ret = 0;
    func_0204f818(&px, &pz, &self->unk_120);
    switch (self->unk_1FE) {
        case 0:
        case 1:
        case 2:
        case 3:
            if (func_ov003_0222a088(self) != 0) {
                self->unk_120.x = self->unk_218.x;
                self->unk_120.y = self->unk_218.y;
                self->unk_120.z = self->unk_218.z;
                ret = 1;
            } else if (func_02031b5c(px, pz) == 1) {
                self->unk_120.x = self->unk_218.x;
                self->unk_120.y = self->unk_218.y;
                self->unk_120.z = self->unk_218.z;
                ret = 3;
            }
            break;
        case 5:
        case 6:
            t = func_ov003_0222a378(self);
            if (t == 0) {
                ret = 6;
            } else if (t == 1) {
                ret = 7;
            } else if (func_ov003_0222a088(self) != 0) {
                self->unk_120.x = self->unk_218.x;
                self->unk_120.y = self->unk_218.y;
                self->unk_120.z = self->unk_218.z;
                ret = 2;
            } else if (func_02031b5c(px, pz) != 1) {
                self->unk_120.x = self->unk_218.x;
                self->unk_120.y = self->unk_218.y;
                self->unk_120.z = self->unk_218.z;
                ret = 4;
            } else if (func_ov003_0222a330(self) != 0) {
                ret = 5;
            }
            break;
        default:
            if (func_02031b5c(px, pz) == 2) {
                if (func_ov003_0222a088(self) != 0) {
                    self->unk_120.x = self->unk_218.x;
                    self->unk_120.y = self->unk_218.y;
                    self->unk_120.z = self->unk_218.z;
                    ret = 1;
                }
            } else if (func_02031b5c(px, pz) == 1) {
                t = func_ov003_0222a378(self);
                if (t == 0) {
                    ret = 6;
                } else if (t == 1) {
                    ret = 7;
                } else if (func_ov003_0222a088(self) != 0) {
                    self->unk_120.x = self->unk_218.x;
                    self->unk_120.y = self->unk_218.y;
                    self->unk_120.z = self->unk_218.z;
                    ret = 2;
                } else if (func_ov003_0222a330(self) != 0) {
                    ret = 5;
                }
            } else {
                self->unk_120.x = self->unk_218.x;
                self->unk_120.y = self->unk_218.y;
                self->unk_120.z = self->unk_218.z;
                ret = 1;
            }
            break;
    }
    return ret;
}
