/* func_ov114_0229cadc @ 0x0229cadc, 0xa0 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0229cadc UnkStruct_0229cadc;
struct UnkStruct_0229cadc {
    u8 unk_00[0x128c];
    int unk_128C;
    int unk_1290;
    u8 p1[0x12b7 - 0x1294];
    u8 unk_12B7;
};
extern void func_ov114_0229c924(UnkStruct_0229cadc *, u16 *, int);

void func_ov114_0229cadc(UnkStruct_0229cadc *self)
{
    u16 h;
    int n;
    unsigned int k;
    int j;

    self->unk_1290 = self->unk_128C % 9;
    k = self->unk_128C;
    j = self->unk_1290;
    h = 0xfff1;
    for (n = 0; n < 9; n++) {
        switch (self->unk_12B7) {
            case 0:
                h = (k < 0x38) ? (u16) (k + 0x12e8) : 0x12e8;
                break;
            case 1:
                h = (k < 0x38) ? (u16) (k + 0x12b0) : 0x12b0;
                break;
            default:
                return;
        }
        func_ov114_0229c924(self, &h, j);
        j = j + 1;
        if (j >= 9) {
            j = 0;
        }
        k = k + 1;
        if (k >= 0x38) {
            return;
        }
    }
}
