/* func_ov114_0229d3f4 @ 0x0229d3f4, 0xcc bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov002_0220a58c(void *, int arg1, int arg2);
extern void func_ov002_0220a574(void *);
extern int func_02088d34(const void *, int, int, int, int);
extern const u8 data_ov114_0229db00[];
extern const u8 data_ov114_0229db08[];
typedef struct {
    u8 pad_00[0x121c];
    u8 sub_121c[0x54];
    int unk_1270;
    int unk_1274;
    int unk_1278;
    u8 pad_127C[0x3f];
    u8 unk_12BB;
} UnkStruct_0229d3f4;

int func_ov114_0229d3f4(UnkStruct_0229d3f4 *self, int x, int y)
{
    int dx;
    unsigned int dy;

    if (func_ov002_0220a58c(self->sub_121c, x, y)) {
        self->unk_1274 = self->unk_1270 - x;
        func_ov002_0220a574(self->sub_121c);
        self->unk_12BB = 2;
        self->unk_1278 = self->unk_1270;
        return 1;
    }
    dx = x - 0x80;
    dy = y;
    dy -= 0x60;
    if (func_02088d34(data_ov114_0229db00, dx, dy, 2, 2)) {
        self->unk_12BB = 0;
        return 1;
    }
    if (func_02088d34(data_ov114_0229db08, dx, dy, 2, 2)) {
        self->unk_12BB = 1;
        return 1;
    }
    if (x > 0x3a && x < 0xc6 && y > 0xac && y < 0xb8) {
        func_ov002_0220a574(self->sub_121c);
        self->unk_12BB = 3;
        self->unk_1278 = self->unk_1270;
        return 1;
    }
    return 0;
}
