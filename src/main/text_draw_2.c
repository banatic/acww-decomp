/* text_draw_2: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02051340 @ 0x02051340, 0x26 bytes, Thumb
 * func_020512d4 @ 0x020512d4, 0x6c bytes, Thumb
 * func_020511f8 @ 0x020511f8, 0xdc bytes, Thumb
 * func_020510c8 @ 0x020510c8, 0x130 bytes, Thumb
 * func_02051034 @ 0x02051034, 0x94 bytes, Thumb
 * func_02050fc8 @ 0x02050fc8, 0x6c bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_020512d4 {
    char pad_00[0x28];
    int unk_28;
    char pad_2C[0x8];
    int unk_34;
    char pad_38[0x1f];
    unsigned char unk_57;
    char pad_58[0xc];
    int unk_64;
    int unk_68;
    char pad_6C[0x9];
    unsigned char unk_75;
    char pad_76[0x2];
    int unk_78;
} UnkStruct_020512d4;

typedef struct UnkStruct_020511f8 {
    char pad_00[0x1c];
    int unk_1C;
    char pad_20[0xc];
    int unk_2C;
    char pad_30[9];
    unsigned char unk_39;
    char pad_3A[0x16];
    int unk_50;
    char pad_54[2];
    unsigned char unk_56;
    char pad_57[9];
    unsigned int unk_60;
    char pad_64[0xc];
    int unk_70;
} UnkStruct_020511f8;

typedef void (*Fn)(unsigned char *buf, int a, unsigned int n);

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

typedef struct {
    char pad_00[0x34];
    u32 unk_34;
    char pad_38[0x30];
    u32 unk_68;
} UnkStruct_02051034;

typedef struct {
    char pad_00[0x68];
    unsigned int count;
} UnkStruct_02050fc8;

extern void func_02051458(void *);
extern int func_020516b8(int table, int key);
extern unsigned char data_021c8344[];
extern Fn data_020cb920[];
extern Fn data_020cb938[];
extern void DC_FlushRange(unsigned char *buf, unsigned int n);
extern void MI_CpuCopy8(unsigned char *dst, int src, unsigned int n);
extern u32 func_0205171c(UnkStruct_020510c8_2 *c, u32 a);
extern int FS_SeekFile(void *p, u32 n, int z);
extern int FS_ReadFile(void *p, u8 *buf, u32 n);
extern int func_02050ef4(UnkStruct_020510c8_3 *s);
extern int func_02050edc(UnkStruct_020510c8_3 *s);
extern int func_02050ea8(UnkStruct_020510c8_3 *s);
extern int func_02050e74(UnkStruct_020510c8_3 *s);

u32 func_020510c8(UnkStruct_020510c8_3 *self);
void func_02051034(UnkStruct_02051034 *s);
void func_02050fc8(UnkStruct_02050fc8 *s, unsigned int start);

void func_02051340(void *r0)
{
    unsigned char b;
    int i;

    func_02051458(r0);
    b = *(unsigned char *) ((char *) r0 + 0x74);
    *(unsigned char *) ((char *) r0 + 0x38) = b;
    i = 0;
    *(int *) ((char *) r0 + 0x64) = ~i;
    *(int *) ((char *) r0 + 0x68) = *(int *) ((char *) r0 + 0x30);
    *(int *) ((char *) r0 + 0x78) = i;
}

void func_020512d4(UnkStruct_020512d4 *this, int key)
{
    int old_68;
    this->unk_64 = func_020516b8(this->unk_28, key);
    if (this->unk_64 == -1) {
        this->unk_64 = func_020516b8(this->unk_28, 0x0000ff20);
    }
    old_68 = this->unk_68;
    this->unk_68 = this->unk_68 + (int) func_020510c8((UnkStruct_020510c8_3 *) this);
    func_02051034((UnkStruct_02051034 *) this);
    this->unk_68 = this->unk_68 + this->unk_34;
    if (this->unk_75 != 0 && this->unk_57 != 0) {
        func_02050fc8((UnkStruct_02050fc8 *) this, old_68);
    }
    this->unk_78++;
}

void func_020511f8(UnkStruct_020511f8 *self)
{
    unsigned int n;
    unsigned char *p;
    unsigned char *q;
    unsigned char *end;
    unsigned int hi;
    unsigned int k;

    n = self->unk_60;
    if (n > 0x400) {
        n = 0x400;
    }
    DC_FlushRange(data_021c8344, n);
    if (self->unk_50 == 2 || self->unk_50 == 3) {
        data_020cb920[self->unk_2C](data_021c8344, self->unk_70, n);
    }
    if (self->unk_50 == 1 || self->unk_50 == 3) {
        data_020cb938[self->unk_2C](data_021c8344, self->unk_70, n);
    }
    if (self->unk_50 != 0) {
        return;
    }
    if (self->unk_56 != 0) {
        p = (unsigned char *) (self->unk_1C + self->unk_70);
        q = data_021c8344;
        end = data_021c8344 + n;
        k = self->unk_39;
        hi = (unsigned char) (k << 4);
        while (q < end) {
            if ((*p & 0xf0) == hi) {
                *p &= 0x0f;
                *p |= *q & 0xf0;
            }
            if ((*p & 0x0f) == k) {
                *p &= 0xf0;
                *p |= *q & 0x0f;
            }
            q++;
            p++;
        }
    } else {
        MI_CpuCopy8(data_021c8344, self->unk_1C + self->unk_70, n);
    }
}

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
                        p = ((u8 *) data_021c8344) + (row << 5) + col;
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

void func_02051034(UnkStruct_02051034 *s)
{
    int v;
    int hi;
    unsigned int y;
    int yy;
    u32 x;
    u32 col;
    u32 off;
    u32 j;
    u8 *p;

    if (func_02050ef4((UnkStruct_020510c8_3 *) s) == 0 && func_02050edc((UnkStruct_020510c8_3 *) s) == 0) {
        return;
    }
    v = func_02050e74((UnkStruct_020510c8_3 *) s);
    y = 0;
    hi = v << 4;
    for (; y < 8; y++) {
        j = 0;
        yy = y * 8;
        for (; j < s->unk_34; j++) {
            x = s->unk_68 + j;
            col = x >> 3;
            off = (u32) (yy + (int) (x - col * 8)) >> 1;
            if (col < 0x20) {
                p = ((u8 *) data_021c8344) + col * 32 + off;
                if ((x & 1) != 0) {
                    *p &= ~0xf0;
                    *p |= (u8) hi;
                } else {
                    *p &= ~0x0f;
                    *p |= (u8) v;
                }
            }
        }
    }
}

void func_02050fc8(UnkStruct_02050fc8 *s, unsigned int start)
{
    unsigned int i;
    unsigned int row, col;
    unsigned char *p;
    int hi, v;
    v = func_02050ea8((UnkStruct_020510c8_3 *) s);
    hi = v << 4;

    for (i = start; i < s->count; i++) {
        row = i >> 3;
        col = ((i - (row << 3)) + 0x30) >> 1;
        if (row < 0x20) {
            p = data_021c8344 + (row << 5) + col;
            if ((i & 1) != 0) {
                *p &= ~0xf0;
                *p |= (unsigned char) hi;
            } else {
                *p &= ~0x0f;
                *p |= (unsigned char) v;
            }
        }
    }
}
