/* func_02045ea8 @ 0x02045ea8, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct Copy {
    u32 a;
    u32 b;
};

struct Entry {
    unsigned char low : 3;
    unsigned char : 5;
    unsigned char pad_01[15];
};

extern int func_02045cec(struct Copy *, int);
extern void func_0204629c(struct Entry *);
extern struct Entry data_021c7884[];

void func_02045ea8(const struct Copy *src, int mask, int param)
{
    struct Copy local;
    int res;

    local.a = src->a;
    local.b = src->b;
    res = func_02045cec(&local, param);
    if (res < 0) {
        return;
    }
    if ((unsigned char) (mask & 3) == data_021c7884[res].low) {
        func_0204629c(&data_021c7884[res]);
    }
}
