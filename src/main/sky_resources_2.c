/* sky_resources_2: 16 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020bf1b8 @ 0x020bf1b8, 0x68 bytes, Thumb
 * func_020bf064 @ 0x020bf064, 0x154 bytes, Thumb
 * func_020befa0 @ 0x020befa0, 0xc4 bytes, Thumb
 * func_020bef88 @ 0x020bef88, 0x18 bytes, Thumb
 * func_020bef78 @ 0x020bef78, 0xe bytes, Thumb
 * func_020bee9c @ 0x020bee9c, 0xdc bytes, Thumb
 * func_020bee74 @ 0x020bee74, 0x28 bytes, Thumb
 * func_020bee60 @ 0x020bee60, 0x12 bytes, Thumb
 * func_020bee4c @ 0x020bee4c, 0x14 bytes, Thumb
 * func_020bee3c @ 0x020bee3c, 0xe bytes, Thumb
 * func_020bedf4 @ 0x020bedf4, 0x48 bytes, Thumb
 * func_020bed64 @ 0x020bed64, 0x90 bytes, Thumb
 * func_020bed04 @ 0x020bed04, 0x60 bytes, Thumb
 * func_020bece0 @ 0x020bece0, 0x24 bytes, Thumb
 * func_020becbc @ 0x020becbc, 0x22 bytes, Thumb
 * func_020beca4 @ 0x020beca4, 0x18 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned int unk_00;
    unsigned short unk_04;
    unsigned short unk_06;
    unsigned int unk_08;
    unsigned int pad_0C;
} Entry;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
} Block;

typedef struct {
    unsigned char b[23];
} UnkStruct_020befa0;

typedef struct {
    unsigned char b[28];
} UnkStruct_020befa0_2;

struct Tile {
    u8 b[32];
};

struct UnkStruct_020bee9c {
    int unk_00;
    int n0;
    int s1;
    int n1;
};

struct Ref {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
};

struct UnkStruct_020bee74 {
    int unk_00;
    int unk_04;
    char unk_08;
};

typedef struct {
    unsigned int unk_00;
    unsigned int pad_04;
    unsigned char unk_08;
    unsigned char unk_09;
} UnkStruct_020bee60;

typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_020bee3c;

typedef struct {
    u16 item;
} Slot;

typedef struct {
    int unk_00;
    u8 flags[4];
    u16 unk_08;
    Slot slots[15];
    u8 pal[0x20];
} UnkStruct_020bedf4;

typedef struct {
    char pad_00[12];
    signed char unk_0C;
    signed char unk_0D;
    char pad_0E[2];
} Entry_020bed64;

typedef struct {
    unsigned char pad_00[8];
    unsigned short unk_08;
    unsigned short arr1[15];
    unsigned short arr2[16];
} UnkStruct_020bed04;

struct UnkStruct_020becbc {
    int unk_00;
    char arr[4];
};

struct UnkStruct_020d2bac {
    char pad_00[13];
    signed char unk_0D;
    char pad_0E[2];
};

extern void FS_InitFile(void *file);
extern void MI_CpuFill8(void *dst, int val, unsigned int size);
extern int FS_OpenFile(void *self, void *ptr);
extern int FS_SeekFile(void *self, int val, int arg2);
extern int FS_ReadFile(void *self, void *dst, int size);
extern void MI_CpuCopy8(void *dst, void *src, int size);
extern int FS_CloseFile(void *self);
extern Entry data_020d2bac[];
extern unsigned int data_020d22d8[];
extern Block data_020d26a0[];
extern const UnkStruct_020befa0 data_020e6100;
extern const UnkStruct_020befa0_2 data_020e6168;
extern void DC_FlushRange(void *startAddr, unsigned int nBytes);
extern int data_021f75b0;
extern void GX_LoadOBJ(const void *src, u32 off, u32 size);
extern void GXS_LoadOBJ(const void *src, u32 off, u32 size);
extern unsigned char data_021fba00[];

// The empty slot every entry starts as.
extern Slot data_020d22c0;
extern void GX_LoadOBJPltt(void *a, int b, int c);
extern void GXS_LoadOBJPltt(void *a, int b, int c);
extern void func_020bec60(void *a, int b, int c);
extern unsigned char data_020d2324[];
extern int func_020bec40(UnkStruct_020bed04 *, int);
extern int func_020644cc(int);
extern signed char data_020d2d8c[];

int func_020bed04(UnkStruct_020bed04 *self, int param2);
void func_020becbc(struct UnkStruct_020becbc *p, int n);
void func_020beca4(int a, int b);

void func_020bf1b8(void *self)
{
    FS_InitFile(self);
    MI_CpuFill8((char *) self + 0x48, 0, 0x400);
    MI_CpuFill8((char *) self + 0x448, 0, 0xc00);
    MI_CpuFill8((char *) self + 0x1048, 0, 0x1c0);
    MI_CpuFill8((char *) self + 0x1208, 0, 0x140);
    *(unsigned int *) ((char *) self + 0x1348) = 0x12345678;
}

int func_020bf064(void *self, int arg1)
{
    Entry *entry = &data_020d2bac[arg1];
    Block *block;
    int flag0, flag1, flag2;
    int i, j, local;
    int last;

    flag0 = FS_OpenFile(self, (void *) data_020d22d8[entry->unk_00]);
    flag1 = 1;
    flag2 = 1;
    block = &data_020d26a0[entry->unk_08];

    if (entry->unk_04 != 0xffff) {
        char *p = (char *) self + 0x448;
        flag1 &= FS_SeekFile(self, (entry->unk_04 & ~0x1f) << 5, 0);
        i = 0;
        local = 0;
        for (; i < 4; i++) {
            if (block->unk_04 != 0) {
                int ret = FS_ReadFile(self, (char *) self + 0x48, 0x400);
                flag2 = flag2 & ((ret > 0) ? 1 : local);
                MI_CpuCopy8((char *) self + 0x48 + ((entry->unk_04 & 0x1f) << 5), p + (block->unk_00 << 5),
                            block->unk_04 << 5);
            }
            p += 0x180;
        }
    }

    if (entry->unk_06 != 0xffff) {
        char *p = (char *) self + 0xa48;
        flag1 &= FS_SeekFile(self, (entry->unk_06 & ~0x1f) << 5, 0);
        j = 4;
        for (; j < 8; j++) {
            if (block->unk_0C != 0) {
                int ret = FS_ReadFile(self, (char *) self + 0x48, 0x400);
                flag2 = flag2 & ((ret > 0) ? 1 : 0);
                MI_CpuCopy8((char *) self + 0x48 + ((entry->unk_06 & 0x1f) << 5), p + (block->unk_08 << 5),
                            block->unk_0C << 5);
            }
            p += 0x180;
        }
    }

    last = FS_CloseFile(self);
    if (flag0 && flag1 && flag2 && last) {
        return 1;
    } else {
        return 0;
    }
}

int func_020befa0(void *p)
{
    UnkStruct_020befa0 a;
    UnkStruct_020befa0_2 b;
    int r1, r2, r3, r4, r5, r6;

    a = data_020e6100;
    r1 = FS_OpenFile(p, &a);
    r2 = FS_ReadFile(p, (char *) p + 0x1048, 0x1c0) > 0;
    r3 = FS_CloseFile(p);
    b = data_020e6168;
    r4 = FS_OpenFile(p, &b);
    r5 = FS_ReadFile(p, (char *) p + 0x1208, 0x140) > 0;
    r6 = FS_CloseFile(p);
    return r1 && r2 && r3 && r4 && r5 && r6;
}

void func_020bef88(void *object)
{
    DC_FlushRange((unsigned char *) object + 0x448, 0xc00);
}

void func_020bef78(void *r0)
{
    unsigned char *p = (unsigned char *) r0;
    unsigned int *q = (unsigned int *) r0;
    q[0] = 0x34;
    q[1] = 0;
    p[8] = 0;
    p[9] = 0;
}

void func_020bee9c(int *a, u8 *b)
{
    unsigned int sub;
    struct UnkStruct_020bee9c *e;
    struct Ref *r;
    struct Tile *base;
    int t;
    int v;
    int i;
    const void *src1;
    int j;
    const void *src2;
    u32 size1;
    u32 off1;
    u32 size2;
    u32 off2;

    sub = (data_021f75b0 == 0) ? 1 : 0;
    func_020bef88(b);
    r = &((struct Ref *) data_020d2bac)[*a];
    e = &((struct UnkStruct_020bee9c *) data_020d26a0)[r->unk_08];
    base = (struct Tile *) (b + 0x448);
    t = 0;
    v = 0x94;
    for (i = 0; i < 4; i++) {
        if (e->n0 != 0) {
            src1 = base + t + e->unk_00;
            size1 = e->n0 * 32;
            off1 = (v + e->unk_00) * 32;
            GX_LoadOBJ(src1, off1, size1);
            if (sub != 0) {
                GXS_LoadOBJ(src1, off1, size1);
            }
        }
        t += 0xc;
        v += 0x20;
    }
    for (j = 4; j < 8; j++) {
        if (e->n1 != 0) {
            src2 = base + t + e->s1;
            size2 = e->n1 * 32;
            off2 = (v + e->s1) * 32;
            GX_LoadOBJ(src2, off2, size2);
            if (sub != 0) {
                GXS_LoadOBJ(src2, off2, size2);
            }
        }
        t += 0xc;
        v += 0x20;
    }
}

void func_020bee74(struct UnkStruct_020bee74 *s, int value, int arg2)
{
    s->unk_04++;
    if (value != s->unk_00) {
        s->unk_08 = 0;
        func_020beca4(arg2, value);
        s->unk_00 = value;
    }
}

void func_020bee60(UnkStruct_020bee60 *s, unsigned int value)
{
    if (value != s->unk_00) {
        s->unk_08 = 0;
        s->unk_09 = 1;
        s->unk_00 = value;
    }
}

void func_020bee4c(unsigned char *self, int arg)
{
    self[9] = 1;
    func_020beca4((int) ((void *) data_021fba00), arg);
}

void func_020bee3c(UnkStruct_020bee3c *p)
{
    int tmp;
    tmp = p->unk_04 - 1;
    p->unk_04 = tmp > 0 ? tmp : 0;
}

UnkStruct_020bedf4 *func_020bedf4(UnkStruct_020bedf4 *self)
{
    Slot *end;
    Slot *dst;
    Slot v;

    self->unk_00 = 0;
    self->unk_08 = 0;
    func_020becbc((struct UnkStruct_020becbc *) self, -1);
    end = self->slots + 15;
    dst = self->slots;
    v = data_020d22c0;
    while (dst < end) {
        *dst++ = v;
    }
    MI_CpuFill8(self->pal, 0, sizeof(self->pal));
    return self;
}

void func_020bed64(void *a0, void *a1, unsigned int idx)
{
    Entry_020bed64 *e = &((Entry_020bed64 *) data_020d2bac)[idx];
    int r6 = e->unk_0C;
    int r7;
    int ret;

    if (idx - 31 <= 1) {
        r6 += *(int *) a0;
    }

    r7 = (int) e->unk_0D << 5;

    MI_CpuCopy8((char *) a1 + 0x1048 + r6 * 32, (void *) ((char *) a0 + 0x28), 32);

    ret = func_020bed04((UnkStruct_020bed04 *) a0, (int) e->unk_0D);

    DC_FlushRange((char *) a0 + 0x28, 32);
    GX_LoadOBJPltt((char *) a0 + 0x28, r7, 32);

    if (data_021f75b0 == 0) {
        GXS_LoadOBJPltt((char *) a0 + 0x28, r7, 32);
    }

    if (ret == 0) {
        func_020bec60(a0, (int) e->unk_0D, r6);
    }
}

int func_020bed04(UnkStruct_020bed04 *self, int param2)
{
    int found = 0;
    if (self->unk_08) {
        int i = 0;
        int zero = 0;
        for (; i < 15; i++) {
            int ret = func_020bec40(self, i);
            unsigned char b = data_020d2324[i];
            int cond = (((b >> 4) & 0xf) == param2) ? 1 : zero;
            if (ret && cond) {
                self->arr2[b & 0xf] = self->arr1[i];
                found = 1;
            }
        }
    }
    return found;
}

void func_020bece0(int *ptr)
{
    *ptr = func_020644cc(5);
    func_020becbc((struct UnkStruct_020becbc *) ptr, data_020d2d8c[0x1d]);
}

void func_020becbc(struct UnkStruct_020becbc *p, int n)
{
    if (n < 0) {
        unsigned i = 0;
        goto test;
    loop:
        p->arr[i] = -1;
        i++;
    test:
        if (i < 4) {
            goto loop;
        }
    } else {
        p->arr[n - 12] = -1;
    }
}

void func_020beca4(int a, int b)
{
    register int offset = 13;
    func_020becbc((struct UnkStruct_020becbc *) a, *(signed char *) ((char *) &((struct UnkStruct_020d2bac *) data_020d2bac)[b] + offset));
}
