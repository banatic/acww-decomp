/* func_020510c8 @ 0x020510c8, 0x130 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_020510c8 {
    u8 pad[4];
    u16 w;
    u16 h;
} UnkStruct_020510c8;

typedef struct UnkStruct_020510c8_2 {
    UnkStruct_020510c8 *p;
    u8 pad[0x10];
    u8 sub;
} UnkStruct_020510c8_2;

typedef struct UnkStruct_020510c8_3 {
    u8 pad_00[0x28];
    UnkStruct_020510c8_2 *ctx;
    u8 pad_2C[0x64 - 0x2c];
    u32 unk_64;
    u32 unk_68;
    u32 unk_6C;
} UnkStruct_020510c8_3;

extern u8 data_021c8344[];
extern u32 func_0205171c(UnkStruct_020510c8_2 *c, u32 a);
extern void FS_SeekFile(void *p, u32 n, int z);
extern void FS_ReadFile(void *p, u8 *buf, u32 n);
extern int func_02050ef4(UnkStruct_020510c8_3 *s);
extern int func_02050edc(UnkStruct_020510c8_3 *s);
extern int func_02050ea8(UnkStruct_020510c8_3 *s);
extern int func_02050e74(UnkStruct_020510c8_3 *s);

u32 func_020510c8(UnkStruct_020510c8_3 *self)
{
    // DECLS
    u32 h;
    u32 k;
    u32 mask;
    u8 buf[0x84];
    u32 total;
    u32 byteIdx;
    u32 pos;
    int valA;
    u32 ibase;
    u32 nbytes;
    int valB;
    u32 w;
    u32 row;
    u8 *p;
    int v;
    u32 bit;
    u32 i;
    u32 flag;
    u32 kshift;
    u32 col;
    // ENDDECLS

    w = self->ctx->p->w;
    h = self->ctx->p->h;
    total = func_0205171c(self->ctx, self->unk_64);
    nbytes = ((w * h) + 7 & ~7) >> 3;
    FS_SeekFile(&self->ctx->sub, nbytes * (self->unk_64 & 0x7fffffff), 0);
    FS_ReadFile(&self->ctx->sub, buf, nbytes);
    mask = 0x80;
    byteIdx = (self->unk_6C * w) >> 3;
    flag = 1;
    if (func_02050ef4(self) == 0) {
        if (func_02050edc(self) == 0) {
            flag = 0;
        }
    }
    valA = func_02050ea8(self);
    valB = func_02050e74(self);
    ibase = 0;
    for (k = 0; k < 8; k++) {
        i = ibase;
        kshift = k << 3;
        for (; i < w; i++) {
            if (i < total) {
                bit = buf[byteIdx] & mask;
                v = bit ? valA : valB;
                if (bit != 0 || flag != 0) {
                    pos = self->unk_68 + i;
                    row = pos >> 3;
                    col = (kshift + (pos - (row << 3))) >> 1;
                    if (row < 0x20) {
                        p = data_021c8344 + (row << 5) + col;
                        pos = pos & 1;
                        if (pos != 0) {
                            *p &= ~0xf0;
                            *p |= (u8) (v << 4);
                        } else {
                            *p &= ~0x0f;
                            *p |= (u8) v;
                        }
                    }
                }
            }
            mask = (u8) (mask >> 1);
            if (mask == 0) {
                mask = 0x80;
                byteIdx = byteIdx + 1;
            }
        }
    }
    return total;
}
