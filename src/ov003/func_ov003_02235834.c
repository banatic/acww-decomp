/* func_ov003_02235834 @ 0x02235834, 0x100 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02235834;
extern UnkStruct_02235834 *data_020ccf94;

extern int func_ov003_02235744(void *self, int ang, int n);
extern int func_02073dd4(void *a, int b);
extern short FX_SinCosTable_[];
extern int FX_MulFunc(int a, int b);

int func_ov003_02235834(char *self, int ang, int d)
{
    int *dst;
    int *src;
    int idx;

    switch (*(signed char *) (self + 0x24d)) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 0x25:
            return func_ov003_02235744(self, ang, (u8) (d >> 12));
        case 0x1e:
        case 0x31:
            return func_ov003_02235744(self, ang, (u8) (d >> 12));
        case 0xc:
        case 0xd:
        case 0x1b:
        case 0x1c:
        case 0x1d:
            if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0) {
                return func_ov003_02235744(self, ang, (u8) (d >> 12));
            }
            break;
    }
    dst = (int *) (self + 0x1d4);
    src = (int *) (self + 0x204);
    idx = ((int) (u16) ang >> 4) * 2;
    dst[0] = src[0] + FX_MulFunc(d, FX_SinCosTable_[idx]);
    dst[2] = src[2] + FX_MulFunc(d, FX_SinCosTable_[idx + 1]);
    return 1;
}
