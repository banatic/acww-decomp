/* talk_tags_5: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02069804 @ 0x02069804, 0x5c bytes, Thumb
 * func_02069794 @ 0x02069794, 0x70 bytes, Thumb
 * func_0206973c @ 0x0206973c, 0x58 bytes, Thumb
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

typedef struct UnkStruct_02069794 UnkStruct_02069794;

typedef struct {
    char pad_00[0x34];
    void (*unk_34)(UnkStruct_02069794 *, int, int);
} Vt;

struct UnkStruct_02069794 {
    Vt *vt;
};

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

extern int func_020a86e4(u8 *a, u8 *b, u8 *c, u8 *d);
extern int func_020ba4e4(void);
extern void func_0206b964(struct UnkStruct_02069804_2 *self, u8 *data);
extern int data_021dc7a8;
extern void func_020a86a4(void *a, unsigned char *b1, unsigned char *b2, unsigned char *b3, int *w);
extern int func_02098880(void *p);
extern void func_020a8630(void *, void *, int);

void func_02069804(struct UnkStruct_02069804_2 *self)
{
    struct UnkStruct_02069804_3 *obj;
    u8 data[4];
    int y;
    int idx;
    u8 *p;

    obj = self->s->obj;
    obj->vtbl->method(obj, 9, 3);

    y = (func_020a86e4(self->unk_38, &data[1], &data[2], &data[3]), func_020ba4e4());

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

void func_02069794(unsigned char *self)
{
    unsigned char b[4];
    int w;
    UnkStruct_02069794 *obj;
    int t;
    int i;

    obj = *(UnkStruct_02069794 **) (*(char **) (self + 0x24) + 0x14a8);
    obj->vt->unk_34(obj, 10, 4);
    func_020a86a4(self + 0x38, &b[1], &b[2], &b[3], &w);
    if ((int) &data_021dc7a8 != 0) {
        t = func_02098880((void *) ((int) &data_021dc7a8 + 0x14));
    } else {
        t = 0;
    }
    i = t - 1;
    if (i < 0) {
        i = 0;
    } else if (i > 3) {
        i = 3;
    }
    b[0] = (&b[1])[i];
    func_0206b964((struct UnkStruct_02069804_2 *) self, (u8 *) b);
}

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
    func_0206b964((struct UnkStruct_02069804_2 *) self, (u8 *) buf);
}
