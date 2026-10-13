/* func_0206973c @ 0x0206973c, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_020a8630(void *, void *, int);
extern void func_0206b964(void *, void *);

struct VTable {
    u8 pad_00[0x34];
    void (*m)(void *, int, int);
};

struct UnkStruct_0206973c {
    struct VTable *vt;
};

struct Work {
    u8 pad_00[0x14a8];
    struct UnkStruct_0206973c *obj;
    u8 pad_14AC[0x5c0];
    u32 key;
};

struct Context {
    u8 pad_00[0x24];
    struct Work *work;
    u8 pad_28[0x10];
    u8 source[7];
};

void func_0206973c(struct Context *self)
{
    u8 buf[8];
    int idx;
    u8 *p;

    self->work->obj->vt->m(self->work->obj, 0xb, 7);
    func_020a8630(self->source, &buf[1], 7);

    if (self->work->key == 0) {
        idx = 6;
    } else {
        idx = (int) (self->work->key - 1);
    }

    p = &buf[1];
    buf[0] = p[idx];
    func_0206b964(self, buf);
}
