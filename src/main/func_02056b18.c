/* func_02056b18 @ 0x02056b18, 0x9a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
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
