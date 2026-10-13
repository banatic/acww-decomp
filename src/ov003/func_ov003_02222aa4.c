/* func_ov003_02222aa4 @ 0x02222aa4, 0x4c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct Vec2 {
    int x;
    int y;
};

struct UnkStruct_02222aa4 {
    u8 pad_00[0x10];
    int unk_10;
    int unk_14;
    u8 pad_18[0x88];
    u8 flagA;
    u8 flagB;
};

extern void func_02045f08(struct Vec2 *v, int flag);
extern void func_02045df8(struct Vec2 *w, int flag);

void func_ov003_02222aa4(struct UnkStruct_02222aa4 *p)
{
    struct Vec2 v, w;

    if (p->flagA) {
        p->flagA = 0;
        v.x = p->unk_10;
        v.y = p->unk_14;
        func_02045f08(&v, 0);
    } else if (p->flagB) {
        p->flagB = 0;
        w.x = p->unk_10;
        w.y = p->unk_14;
        func_02045df8(&w, 0);
    }
}
