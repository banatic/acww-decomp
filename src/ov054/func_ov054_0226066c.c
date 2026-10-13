/* func_ov054_0226066c @ 0x0226066c, 0xa4 bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec;
typedef struct UnkStruct_0226066c UnkStruct_0226066c;
typedef struct UnkStruct_0226066c_2 UnkStruct_0226066c_2;

struct UnkStruct_0226066c {
    u8 unk_00[0x618];
    int unk_618;
    u8 p1[0x654 - 0x61c];
    int unk_654;
    u8 p2[0x80c - 0x658];
    int unk_80C;
};
struct UnkStruct_0226066c_2 {
    u8 unk_00[0x5c];
    Vec unk_5C;
};

extern Vec data_ov054_022629c8[];
extern void func_0204f818(int *, int *, Vec *);
extern int func_02014868(int *);
extern int func_0201c014(UnkStruct_0226066c *);

int func_ov054_0226066c(UnkStruct_0226066c *self, UnkStruct_0226066c_2 *p)
{
    int result;
    int a, b, c, d;
    Vec v, w;
    Vec *sv;
    Vec *sw;

    result = 0;
    sv = &p->unk_5C;
    v.x = sv->x;
    v.y = sv->y;
    v.z = sv->z;
    a = 0;
    b = 0;
    c = 0;
    d = 0;
    func_0204f818(&a, &b, &v);
    sw = &data_ov054_022629c8[self->unk_80C];
    w.x = sw->x;
    w.y = sw->y;
    w.z = sw->z;
    func_0204f818(&c, &d, &w);
    if (func_02014868(&self->unk_618) != 0 || func_0201c014(self) != 0) {
        return 0;
    }
    if (self->unk_654 == 2 || self->unk_654 == 0 || self->unk_654 == 9) {
        if (a == c) {
            if (b == d) {
                result = 1;
            }
        }
    }
    return result;
}
