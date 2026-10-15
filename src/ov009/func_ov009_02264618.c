/* func_ov009_02264618 @ 0x02264618, 0xa0 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *data_021c9b1c;
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
extern void *func_ov009_02264884(void *ctx);
extern u32 func_ov009_02264394(void *field);
extern void *func_020e9948(void *heap, u32 size);
extern void *func_020ad1dc(void *ptr);
extern ItemStruct *func_ov009_02264388(void *field, u32 idx);
extern void func_ov009_02265660(u32 *out, u32 *in, int arg);
extern int func_020ad0c0(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);
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
    res = func_ov009_02264884(ctx);
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
