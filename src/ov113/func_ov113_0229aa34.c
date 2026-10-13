/* func_ov113_0229aa34 @ 0x0229aa34, 0x58 bytes, Thumb, module ov113
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct Context {
    u8 pad_00[0x9a];
    u8 index;
    u8 pad_9B[2];
    u8 count;
};

struct Elem {
    int a;
    int b;
};

extern struct Elem data_ov113_0229ac60[];
extern void func_020896b8(int, void *, int, int, int, int, int);

void func_ov113_0229aa34(struct Context *self, int arg1, int arg2)
{
    u8 i = 0;
    int flag = 0;
    while (i < self->count) {
        int a = (i == self->index) ? 11 : 10;
        func_020896b8(flag, &data_ov113_0229ac60[i + 8], arg1, arg2, a, 1, flag);
        i++;
    }
}
