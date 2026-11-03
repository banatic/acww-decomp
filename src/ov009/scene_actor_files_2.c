/* scene_actor_files_2: 3 functions, module ov009
 * mwccarm 1.2/base -O4,s
 * func_ov009_02264618 @ 0x02264618, 0xa0 bytes, Thumb
 * func_ov009_022645b8 @ 0x022645b8, 0x60 bytes, Thumb
 * func_ov009_02264580 @ 0x02264580, 0x38 bytes, Thumb
 */

#include "types.h"

typedef struct {
    u32 pad_00[7];
    void *unk_1C;
} ResultStruct;

typedef struct {
    u32 pad_00[0x284 / 4];
    void *ptr;
} CtxStruct;

typedef struct {
    u32 unk_00;
    u32 unk_04;
    u32 unk_08;
    u32 unk_0C;
    u32 unk_10;
    u32 unk_14;
    u32 unk_18;
} ItemStruct;

struct UnkStruct_022645b8_2 {
    char pad_00[0x284];
    void *slots;
};

struct Container {
    char pad_00[0x1c];
    void *arr;
};

struct Elem {
    int pad_00;
    int unk_04;
    int unk_08;
};

struct UnkStruct_022645b8 {
    int unk_00, t1, t2;
};

struct UnkStruct_022645b8_3 {
    int unk_00, unk_04, unk_08;
};

typedef struct UnkStruct_02264580 {
    char pad_00[0x1c];
    unsigned int unk_1C;
} UnkStruct_02264580;

typedef struct UnkStruct_02264580_2 {
    char pad_00[0x284];
    unsigned int unk_284;
} UnkStruct_02264580_2;

extern void *data_021c9b1c;
extern u32 func_ov009_02264394(void *field);
extern void *func_020e9948(void *heap, u32 size);
extern void *func_020ad1dc(void *ptr);
extern ItemStruct *func_ov009_02264388(void *field, u32 idx);
extern void func_ov009_02265660(u32 *out, u32 *in, int arg);
extern int func_020ad0c0(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);
extern void func_020aced0(void *dst, struct UnkStruct_022645b8_3 *item);
extern UnkStruct_02264580 *func_ov009_02264884(UnkStruct_02264580_2 *self);

void func_ov009_02264618(CtxStruct *ctx, int arg1)
{
    ResultStruct *res;
    u32 val;
    ItemStruct *p;
    void *heap;
    void *ptr;
    u32 count;
    u32 zero;
    u32 input[3];
    u32 out[4];
    u32 i;
    res = (void *) func_ov009_02264884((UnkStruct_02264580_2 *) ctx);
    if ((res == 0) || (res->unk_1C == 0)) {
        return;
    }
    heap = data_021c9b1c;
    count = func_ov009_02264394(res->unk_1C);
    ctx->ptr = func_020e9948(heap, count * 0x34);
    ptr = ctx->ptr;
    zero = 0;
    for (i = 0; i < count; i++) {
        u32 a8tmp;
        if (ptr) {
            ptr = func_020ad1dc(ptr);
        }
        p = func_ov009_02264388(res->unk_1C, i);
        a8tmp = p->unk_08;
        val = p->unk_04;
        input[0] = val;
        input[1] = zero;
        input[2] = a8tmp;
        func_ov009_02265660(out, input, arg1);
        func_020ad0c0((u32) ptr, (u32) out, p->unk_0C, p->unk_10, p->unk_00, p->unk_14, p->unk_18, (u32) heap);
        ptr = ((char *) ptr) + 0x34;
    }
}

void func_ov009_022645b8(struct UnkStruct_022645b8_2 *self, void *param2)
{
    struct Container *c;
    void *slot;
    unsigned int i;

    c = (struct Container *) func_ov009_02264884((UnkStruct_02264580_2 *) self);
    if (!c) {
        return;
    }
    slot = self->slots;
    if (!slot) {
        return;
    }
    for (i = 0; i < (unsigned int) func_ov009_02264394(c->arr); i++) {
        struct Elem *e;
        struct UnkStruct_022645b8 tmp;
        struct UnkStruct_022645b8_3 outbuf;
        int f8v;

        e = (struct Elem *) func_ov009_02264388(c->arr, i);
        f8v = e->unk_08;
        tmp.unk_00 = e->unk_04;
        tmp.t1 = 0;
        tmp.t2 = f8v;
        func_ov009_02265660((u32 *) (&outbuf), (u32 *) (&tmp), (int) param2);
        func_020aced0(slot, &outbuf);
        slot = (char *) slot + 0x34;
    }
}

void func_ov009_02264580(UnkStruct_02264580_2 *self)
{
    UnkStruct_02264580 *p;
    unsigned int i;

    p = func_ov009_02264884(self);
    if (p != 0 && self->unk_284 != 0) {
        for (i = 0; i < (unsigned int) func_ov009_02264394((void *) p->unk_1C); i++) {
        }
        self->unk_284 = 0;
    }
}
