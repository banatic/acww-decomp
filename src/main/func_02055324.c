/* func_02055324 @ 0x02055324, 0xfc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02055324 UnkStruct_02055324;
typedef struct UnkStruct_02055324_2 UnkStruct_02055324_2;

struct UnkStruct_02055324 {
    void *unk_00;
    u32 count;
    UnkStruct_02055324_2 *elements;
    void *unk_0C;
};

struct UnkStruct_02055324_2 {
    u8 data[0x9c];
};

typedef struct Node {
    u8 unk_00[8];
    u8 unk_08;
    u8 unk_09;
    u8 pad_0A[4];
    u16 unk_0E;
} Node;

extern void *func_02064b2c(void *a, void *b, int c, int d);
extern void *func_02107828(void *a);
extern void *func_020e9948(void *a, u32 b);
extern void MI_CpuCopy8(void *a, void *b, u32 c);
extern void *func_021077e8(void *a);
extern void func_02056064(void *a, int b);
extern void *func_020561cc(void *a, void *b);
extern void *func_02056268(void *a, void *b);
extern void func_02055f40(void *a, void *b, void *c);
extern void func_0205577c(void *a);
extern void func_020e993c(void *a, void *b);

extern void *data_021c9b2c;
extern void *data_021fbe94;

int func_02055324(UnkStruct_02055324 *self, void *arg, void *flag)
{
    Node *node;
    void *handle;
    void *p;
    void *g2;
    u32 size;
    void *temp;
    u32 i;

    if (flag == 0) {
        flag = data_021c9b2c;
    }

    g2 = data_021fbe94;
    handle = func_02064b2c(arg, g2, ~3, 0);
    if (handle == 0) {
        return 0;
    }

    node = func_02107828(handle);
    self->count = node->unk_09;
    size = self->count << 4;
    self->unk_0C = func_020e9948(flag, size);

    {
        u8 *b;
        u8 *q;
        b = (u8 *) node + 8;
        q = b + node->unk_0E;
        p = q + *(u16 *) (q + 2);
    }
    MI_CpuCopy8(p, self->unk_0C, size);

    self->elements = func_020e9948(flag, self->count * 0x9c);

    for (i = 0; i < self->count; i++) {
        UnkStruct_02055324_2 *e;
        e = self->elements + i;
        if (e != 0) {
            func_0205577c(e);
        }
    }

    p = func_021077e8(handle);
    func_02056064(p, 0);
    *(void **) &temp = func_020561cc(p, flag);

    for (i = 0; i < self->count; i++) {
        Node *n2;
        u8 *b;
        u8 *q;
        u32 m;
        void *target;
        void *res;

        n2 = func_02107828(handle);
        b = (u8 *) n2 + 8;
        q = b + n2->unk_0E;
        m = *(u16 *) q;
        target = (u8 *) n2 + *(u32 *) (q + m * i + 4);
        res = func_02056268(target, flag);
        func_02055f40(self->elements + i, res, *(void **) &temp);
    }

    func_020e993c(g2, handle);
    return 1;
}
