/* func_02064fb4 @ 0x02064fb4, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

// Bitfield reads (RGB555).
typedef struct Rgb {
    u16 r : 5;
    u16 g : 5;
    u16 b : 5;
    u16 x : 1;
} Rgb;

typedef struct UnkStruct_02064fb4 {
    u8 pad_00[0x16a];
    Rgb c0;
    Rgb c1;
} UnkStruct_02064fb4;

typedef struct UnkStruct_02064fb4_2 {
    u8 pad_00[0x1c];
    u8 unk_1C[0x18];
    u16 unk_34;
} UnkStruct_02064fb4_2;

extern UnkStruct_02064fb4 *data_021cd864;
extern int func_020b3658(void *p);

void func_02064fb4(UnkStruct_02064fb4_2 *self)
{
    int t;

    t = func_020b3658(self->unk_1C);
    // Red and green are combined first, then blue.
    self->unk_34 = (u16) (((data_021cd864->c1.b + (((data_021cd864->c0.b - data_021cd864->c1.b) * t) >> 12)) << 10) |
                          ((data_021cd864->c1.r + (((data_021cd864->c0.r - data_021cd864->c1.r) * t) >> 12)) |
                           ((data_021cd864->c1.g + (((data_021cd864->c0.g - data_021cd864->c1.g) * t) >> 12)) << 5)));
}
