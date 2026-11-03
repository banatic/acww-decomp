/* joint_blend: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02056b18 @ 0x02056b18, 0x9a bytes, Thumb
 * func_02056aa0 @ 0x02056aa0, 0x78 bytes, Thumb
 */

#include "types.h"

typedef struct {
    u8 pad0;
    u8 unk_01;
    u8 pad_02[2];
} Header;

typedef struct {
    u32 data[3];
} Field12;

typedef struct {
    u32 data[9];
} Field36;

typedef struct {
    u32 flags;      // 0x00
    u32 pad0[9];    // 0x04
    Field36 unk_28; // 0x28
    Field12 unk_4C; // 0x4c
} UnkStruct_02056b18;

typedef struct {
    Header *header;          // 0x00
    u32 pad0[0x2c];          // 0x04
    UnkStruct_02056b18 *obj; // 0xb4
} UnkStruct_02056b18_2;

typedef struct {
    u32 pad0;       // 0x00
    Field36 unk_04; // 0x04
    Field12 unk_28; // 0x28
    u32 unk_34;     // 0x34
} Src;

typedef struct {
    int w[9];
} UnkStruct_02056aa0;

typedef struct {
    int unk_00;
    UnkStruct_02056aa0 data;
    int extra[3];
} UnkStruct_02056aa0_2;

typedef struct {
    char pad_00[0x28];
    UnkStruct_02056aa0 data;
    int extra[3];
} UnkStruct_02056aa0_3;

typedef struct {
    char pad_00[0x34];
    UnkStruct_02056aa0_3 *base;
} UnkStruct_02056aa0_4;

typedef struct {
    const unsigned char *str;
    UnkStruct_02056aa0_4 *inner;
} Param;

extern void func_02056bb4(void *dst, const void *src, void *out, u32 value);
extern void func_02056c20(void *dst, const void *src, void *out, u32 value);
extern void MTX_Identity33_(void *p);

void func_02056b18(Src *src, UnkStruct_02056b18_2 *ctx)
{
    u8 b;
    UnkStruct_02056b18 *o;
    u32 *dst;
    Field12 tmp1;
    Field36 tmp2;

    b = ctx->header->unk_01;
    if ((ctx->obj->flags & 4) == 0 && b <= 1) {
        func_02056bb4(&ctx->obj->unk_4C, &src->unk_28, &tmp1, src->unk_34);
        o = ctx->obj;
        dst = o->unk_4C.data;
        dst[0] = tmp1.data[0];
        dst[1] = tmp1.data[1];
        dst[2] = tmp1.data[2];
    }
    if (ctx->obj->flags & 2) {
        MTX_Identity33_(&ctx->obj->unk_28);
    }
    func_02056c20(&ctx->obj->unk_28, &src->unk_04, &tmp2, src->unk_34);
    ctx->obj->unk_28 = tmp2;
    ctx->obj->flags &= ~2u;
}

void func_02056aa0(UnkStruct_02056aa0_2 *out, Param *param)
{
    UnkStruct_02056aa0_3 *item;

    item = &param->inner->base[param->str[1]];
    if (item->data.w[0] == 0 && item->data.w[1] == 0 && item->data.w[2] == 0 && item->data.w[3] == 0 && item->data.w[4] == 0 &&
        item->data.w[5] == 0 && item->data.w[6] == 0 && item->data.w[7] == 0 && item->data.w[8] == 0) {
        MTX_Identity33_(&out->data);
    } else {
        out->data = item->data;
    }
    out->extra[0] = item->extra[0];
    out->extra[1] = item->extra[1];
    out->extra[2] = item->extra[2];
}
