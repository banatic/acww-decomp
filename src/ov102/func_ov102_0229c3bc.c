/* func_ov102_0229c3bc @ 0x0229c3bc, 0xa4 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_020896b8(int a, void *b, int c, void *d, int e, int f, int g);
extern u8 data_ov102_0229eac0[];

typedef struct {
    u8 pad_00[0x24d4];
    void *unk_24D4;
    u8 pad_24D8[0x25aa - (0x24d4 + 4)];
    u8 unk_25AA;
} Param;

void func_ov102_0229c3bc(Param *p)
{
    u8 *r6 = (u8 *) p->unk_24D4 + 0x60;
    int i = 0;
    int j = i;
    int m1 = ~i;
    u8 *tmp10;
    int tmp14;
    int local18 = i;
    int local1c = i;
    int local20 = i;

    do {
        if (i == p->unk_25AA) {
            tmp10 = r6 + 2;
            tmp14 = 4;
        } else {
            tmp10 = r6;
            tmp14 = 5;
        }

        func_020896b8(1, &data_ov102_0229eac0[j * 8], 0x80, tmp10, m1, 1, local18);
        func_020896b8(1, &data_ov102_0229eac0[(j + 1) * 8], 0x80, tmp10, tmp14, 1, local1c);
        func_020896b8(1, &data_ov102_0229eac0[(j + 2) * 8], 0x80, r6, m1, 1, local20);

        i++;
        j += 3;
    } while (i < 6);
}
