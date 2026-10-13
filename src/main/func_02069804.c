/* func_02069804 @ 0x02069804, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02069804_3;
struct Vtbl;
struct UnkStruct_02069804;
struct UnkStruct_02069804_2;

typedef void (*Method)(struct UnkStruct_02069804_3 *, int, int);

struct Vtbl {
    u8 pad_00[0x34];
    Method method;
};

struct UnkStruct_02069804_3 {
    struct Vtbl *vtbl;
};

struct UnkStruct_02069804 {
    u8 pad_00[0x14a8];
    struct UnkStruct_02069804_3 *obj;
};

struct UnkStruct_02069804_2 {
    u8 pad_00[0x24];
    struct UnkStruct_02069804 *s;
    u8 pad_28[0x38 - 0x28];
    u8 unk_38[4];
};

extern int func_020a86e4(u8 *a, u8 *b, u8 *c, u8 *d);
extern int func_020ba4e4(int x);
extern void func_0206b964(struct UnkStruct_02069804_2 *self, u8 *data);

void func_02069804(struct UnkStruct_02069804_2 *self)
{
    struct UnkStruct_02069804_3 *obj;
    u8 data[4];
    int y;
    int idx;
    u8 *p;

    obj = self->s->obj;
    obj->vtbl->method(obj, 9, 3);

    y = func_020ba4e4(func_020a86e4(self->unk_38, &data[1], &data[2], &data[3]));

    idx = 0;
    if (y == 1) {
        idx = 1;
    } else if (y == 2) {
        idx = 2;
    }

    p = &data[1];
    data[0] = p[idx];

    func_0206b964(self, data);
}
