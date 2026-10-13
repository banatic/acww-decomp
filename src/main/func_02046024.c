/* func_02046024 @ 0x02046024, 0xc8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u32 x;
    u32 y;
} Pair;

struct Entry {
    unsigned char b0_low : 3;
    unsigned char b0_high : 5;
    unsigned char b1_low : 7;
    unsigned char b1_high : 1;
    unsigned char pad_02[14];
};

extern struct Entry data_021c7884[];
extern int func_02045cec(void *pair, u8 b);
extern int func_020460ec(int a0, void *pair, u32 a2, u32 a3, u8 a4, u8 a5, u8 a6, u8 a7, u8 a8, s8 a9);
extern void func_02046194(int idx, int a0, void *pair, u32 a2, u32 a3, u8 a4, u8 a5, u8 a6, u8 a7, u8 a8, s8 a9);

int func_02046024(int p0, Pair *p1, u32 p2, u32 p3, u8 p4, u8 p5, u8 p6, u8 p7, u8 p8, s8 p9)
{
    int result;
    Pair tmp0;
    Pair tmp2;
    Pair tmp1;
    int idx;

    result = 0;
    tmp0.x = p1->x;
    tmp0.y = p1->y;
    idx = func_02045cec(&tmp0, p8);

    if (idx >= 0) {
        if ((p0 & 3) == data_021c7884[idx].b0_low && data_021c7884[idx].b1_high != 0) {
            tmp2.x = p1->x;
            tmp2.y = p1->y;
            func_02046194(idx, p0, &tmp2, p2, p3, p4, p5, p6, p7, p8, p9);
            result = 1;
        }
    } else {
        tmp1.x = p1->x;
        tmp1.y = p1->y;
        result = func_020460ec(p0, &tmp1, p2, p3, p4, p5, p6, p7, p8, p9);
    }

    return result;
}
