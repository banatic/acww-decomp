/* effect_system_6: 25 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02091db4 @ 0x02091db4, 0x24 bytes, Thumb
 * func_02091d90 @ 0x02091d90, 0x24 bytes, Thumb
 * func_02091d3c @ 0x02091d3c, 0x54 bytes, Thumb
 * func_02091ce8 @ 0x02091ce8, 0x54 bytes, Thumb
 * func_02091ca0 @ 0x02091ca0, 0x48 bytes, Thumb
 * func_02091c58 @ 0x02091c58, 0x48 bytes, Thumb
 * func_02091c30 @ 0x02091c30, 0x28 bytes, Thumb
 * func_02091c0c @ 0x02091c0c, 0x24 bytes, Thumb
 * func_02091be8 @ 0x02091be8, 0x24 bytes, Thumb
 * func_02091bc4 @ 0x02091bc4, 0x24 bytes, Thumb
 * func_02091b7c @ 0x02091b7c, 0x48 bytes, Thumb
 * func_02091b54 @ 0x02091b54, 0x28 bytes, Thumb
 * func_02091b2c @ 0x02091b2c, 0x28 bytes, Thumb
 * func_02091ad0 @ 0x02091ad0, 0x5c bytes, Thumb
 * func_02091a74 @ 0x02091a74, 0x5c bytes, Thumb
 * func_02091a24 @ 0x02091a24, 0x50 bytes, Thumb
 * func_020919d4 @ 0x020919d4, 0x50 bytes, Thumb
 * func_020919ac @ 0x020919ac, 0x28 bytes, Thumb
 * func_02091960 @ 0x02091960, 0x4c bytes, Thumb
 * func_020918d8 @ 0x020918d8, 0x88 bytes, Thumb
 * func_0209184c @ 0x0209184c, 0x8c bytes, Thumb
 * func_02091824 @ 0x02091824, 0x28 bytes, Thumb
 * func_02091810 @ 0x02091810, 0x14 bytes, Thumb
 * func_020917ec @ 0x020917ec, 0x24 bytes, Thumb
 * func_020917c8 @ 0x020917c8, 0x24 bytes, Thumb
 */

#include "types.h"

struct Global {
    char pad_00[16];
    short idx;
};

struct Blk {
    unsigned char v[4];
};

typedef char Table1[12];

typedef char Table2[28];

struct UnkStruct_02091ca0 {
    unsigned char v[4];
};

struct UnkStruct_02091c58 {
    unsigned char v[4];
};

typedef struct UnkStruct_02091b7c {
    int x;
    int y;
    int z;
} UnkStruct_02091b7c;

typedef struct UnkStruct_02091b7c_2 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
} UnkStruct_02091b7c_2;

typedef struct Mid {
    UnkStruct_02091b7c_2 *p;
} Mid;

typedef struct UnkStruct_02091b7c_3 {
    char pad_00[0x18];
    Mid *m;
    int unk_1C;
    int unk_20;
    int unk_24;
    int unk_28;
} UnkStruct_02091b7c_3;

struct UnkStruct_02091ad0 {
    u8 pad_00[0x10];
    short unk_10;
};

struct Blk_02091ad0 {
    u8 v[4];
};

struct UnkStruct_02091ad0_2 {
    u8 data[0x1c];
};

struct UnkStruct_02091a74 {
    u8 pad_00[0x10];
    short unk_10;
};

struct Blk_02091a74 {
    u8 v[4];
};

struct UnkStruct_02091a74_2 {
    u8 data[0x1c];
};

typedef struct {
    unsigned char b[4];
} UnkStruct_02091a24;

typedef struct {
    unsigned char b[4];
} UnkStruct_020919d4;

struct UnkStruct_02091960 {
    unsigned char pad_00[0x1c];
    unsigned short unk_1C;
};

typedef struct CmdId {
    u8 b[4];
} CmdId;

typedef struct Node Node;

typedef struct SomeVec {
    int unk_00;
    int x;
    int y;
    int z;
} SomeVec;

typedef struct {
    u32 unk_00;
    u32 unk_04;
    Node *list;
    u32 unk_0C;
    u32 unk_10;
    u32 unk_14;
    SomeVec **vecs;
    u32 unk_1C;
    int x;
    int y;
    int z;
} UnkStruct_020918d8;

typedef struct {
    u32 unk_00;
    CmdId cmd;
    u32 unk_08;
    UnkStruct_020918d8 *obj;
} UnkStruct_020918d8_2;

typedef struct CmdEntry {
    u32 a;
    u32 b;
    u32 c;
    u16 unk_0C;
    s16 flagE;
    u16 unk_10;
    u16 unk_12;
    int unk_14;
    u32 tail18;
} CmdEntry;

struct Node {
    struct Node *next;
    u8 pad_04[0x20];
    u16 src;
    u16 dst;
};

typedef struct UnkStruct_0209184c {
    char pad_00[0x18];
    int **unk_18;
    int pad_1C;
    int unk_20;
    int unk_24;
    int unk_28;
} UnkStruct_0209184c;

typedef struct Key {
    unsigned char b[4];
} Key;

typedef struct Param {
    int pad_00;
    Key key;
    int pad_08;
    UnkStruct_0209184c *obj;
} Param;

typedef struct Elem {
    int unk_00;
    int unk_04;
    int unk_08;
    short unk_0C;
    short unk_0E;
    int unk_10;
    int unk_14;
    int unk_18;
} Elem;

extern int func_02094b58(int, int, int, int, int, int);
extern void func_02094c38(void *a, void *b, int c);
extern void MI_CpuCopy8(void *d, void *e, int f);
extern struct Global data_021d5658;
extern Table1 data_020e2b44[];
extern Table2 data_021d52d8[];
extern Table1 data_020e2bb0[];
extern int func_02094bcc(void *a, void *b, int c);
extern unsigned char data_020e29c4[];
extern int func_02094cf8(int, int, int, int, int, int);
extern void func_02090db0(UnkStruct_02091b7c_3 *);
extern unsigned char data_020e27c0[];
extern unsigned char data_020e2984[];
extern char data_020d1840[];
extern char data_020d184c[];
extern char data_020d178c[];
extern char data_020d1828[];
extern char data_020d1834[];
extern char data_020d1744[];
extern unsigned char data_020e2934[];
extern void func_02091494(void *, unsigned short, int, int, int, int, int);
extern int func_02090ac4(int, int, int, void *);
extern void func_020914dc(void *);
extern int data_020e2ac4;
extern unsigned char data_020e2a1c[];
extern void func_020913c8(void *dst, const void *src, unsigned int size);

void func_02091db4(int r0, int r1, int r2, int r3)
{
    int sp0 = r3;
    int sp4 = 0;
    func_02094b58(8, r0, r1, r2, sp0, sp4);
}

void func_02091d90(int r0, int r1, int r2, int r3)
{
    int sp0 = r3;
    int sp4 = 0;
    func_02094b58(0x16, r0, r1, r2, sp0, sp4);
}

void func_02091d3c(unsigned char *p)
{
    struct Global *g = (struct Global *) &data_021d5658;
    struct Blk buf;

    buf = *(struct Blk *) (p + 4);
    func_02094c38(p, data_020e2b44[g->idx], 0);
    MI_CpuCopy8(g, data_021d52d8[buf.v[0]], 28);
}

void func_02091ce8(unsigned char *p)
{
    struct Global *g = (struct Global *) &data_021d5658;
    struct Blk buf;

    buf = *(struct Blk *) (p + 4);
    func_02094c38(p, data_020e2bb0[g->idx], 0);
    MI_CpuCopy8(g, data_021d52d8[buf.v[0]], 28);
}

void func_02091ca0(void *p)
{
    unsigned char buf[4];
    unsigned char *src;
    unsigned char *dst;
    int count;
    short s;
    void *dest;

    *(struct UnkStruct_02091ca0 *) buf = *(struct UnkStruct_02091ca0 *) ((unsigned char *) p + 4);

    s = *(short *) (((char *) data_021d52d8) + 0x1c * buf[0] + 0x10);
    dest = ((char *) data_020e2b44) + 12 * s;
    func_02094bcc(p, dest, 0);
}

void func_02091c58(void *p)
{
    unsigned char buf[4];
    unsigned char *src;
    unsigned char *dst;
    int count;
    short s;
    void *dest;

    *(struct UnkStruct_02091c58 *) buf = *(struct UnkStruct_02091c58 *) ((unsigned char *) p + 4);

    s = *(short *) (((char *) data_021d52d8) + 0x1c * buf[0] + 0x10);
    dest = ((char *) data_020e2bb0) + 12 * s;
    func_02094bcc(p, dest, 0);
}

void func_02091c30(int r0, int r1, int r2, int r3)
{
    int sp[2];
    sp[0] = r3;
    sp[1] = (unsigned int) data_020e29c4;
    func_02094b58(9, r0, r1, r2, sp[0], sp[1]);
}

int func_02091c0c(int a0, int a1, int a2, int a3)
{
    return func_02094cf8(0xA, a0, a1, a2, a3, 0);
}

int func_02091be8(int a1, int a2, int a3, int a4)
{
    return func_02094cf8(0xb, a1, a2, a3, a4, 0);
}

void func_02091bc4(int r0, int r1, int r2, int r3)
{
    int sp0 = r3;
    int sp4 = 0;
    func_02094cf8(0xc, r0, r1, r2, sp0, sp4);
}

void func_02091b7c(UnkStruct_02091b7c_3 *self)
{
    UnkStruct_02091b7c v;
    int *g = (int *) ((UnkStruct_02091b7c *) &data_021d5658);

    v.x = g[0];
    v.y = g[1];
    v.z = g[2];
    v.y = 0;
    self->unk_20 = v.x + self->m->p->unk_04;
    self->unk_24 = *(volatile int *) &v.y + self->m->p->unk_08;
    self->unk_28 = v.z + self->m->p->unk_0C;
    func_02090db0(self);
}

void func_02091b54(int r0, int r1, int r2, int r3)
{
    int sp[2];
    sp[0] = r3;
    sp[1] = (unsigned int) data_020e27c0;
    func_02094cf8(0x5d, r0, r1, r2, sp[0], sp[1]);
}

void func_02091b2c(int r0, int r1, int r2, int r3)
{
    int sp[2];
    sp[0] = r3;
    sp[1] = (unsigned int) data_020e2984;
    func_02094b58(0xd, r0, r1, r2, sp[0], sp[1]);
}

void func_02091ad0(void *self)
{
    struct Blk_02091ad0 buf;
    struct UnkStruct_02091ad0 *gp = (struct UnkStruct_02091ad0 *) ((struct UnkStruct_02091ad0 *) &data_021d5658);

    buf = *(struct Blk_02091ad0 *) ((u8 *) self + 4);

    func_02094c38(self, gp->unk_10 != 3 ? data_020d1840 : data_020d184c, (int) data_020d178c);

    MI_CpuCopy8(gp, &((struct UnkStruct_02091ad0_2 *) data_021d52d8)[buf.v[0]], 28);
}

void func_02091a74(void *self)
{
    struct Blk_02091a74 buf;
    struct UnkStruct_02091a74 *gp = (struct UnkStruct_02091a74 *) ((struct UnkStruct_02091a74 *) &data_021d5658);

    buf = *(struct Blk_02091a74 *) ((u8 *) self + 4);

    func_02094c38(self, gp->unk_10 != 3 ? data_020d1828 : data_020d1834, (int) data_020d1744);

    MI_CpuCopy8(gp, &((struct UnkStruct_02091a74_2 *) data_021d52d8)[buf.v[0]], 28);
}

void func_02091a24(void *self)
{
    UnkStruct_02091a24 local;
    void *p;
    short val;

    local = *(UnkStruct_02091a24 *) ((unsigned char *) self + 4);
    val = *(short *) (((unsigned char *) data_021d52d8) + local.b[0] * 0x1c + 0x10);
    if (val != 3) {
        p = ((int *) data_020d1840);
    } else {
        p = ((int *) data_020d184c);
    }
    func_02094bcc(self, p, (int) (((int *) data_020d178c)));
}

void func_020919d4(void *self)
{
    UnkStruct_020919d4 local;
    void *p;
    short val;

    local = *(UnkStruct_020919d4 *) ((unsigned char *) self + 4);
    val = *(short *) (((unsigned char *) data_021d52d8) + local.b[0] * 0x1c + 0x10);
    if (val != 3) {
        p = ((int *) data_020d1828);
    } else {
        p = ((int *) data_020d1834);
    }
    func_02094bcc(self, p, (int) (((int *) data_020d1744)));
}

void func_020919ac(int r0, int r1, int r2, int r3)
{
    int sp[2];
    sp[0] = r3;
    sp[1] = (unsigned int) data_020e2934;
    func_02094b58(0xe, r0, r1, r2, sp[0], sp[1]);
}

int func_02091960(int a0, int a1, int a2, int a3)
{
    struct UnkStruct_02091960 *p = ((struct UnkStruct_02091960 *) &data_021d5658);
    struct UnkStruct_02091960 *q = ((struct UnkStruct_02091960 *) &data_021d5658);
    int result = 3;

    func_02091494(p, q->unk_1C, a0, a1, a2, a3, 0xf);
    if (func_02090ac4(0xf, a1, a2, &data_020e2ac4) != 0) {
        result = 2;
    }
    func_020914dc(p);

    return result;
}

int func_020918d8(UnkStruct_020918d8_2 *self)
{
    CmdId cmd = self->cmd;
    CmdEntry *entry = &((CmdEntry *) data_021d52d8)[cmd.b[0]];
    int success = 0;

    if (entry->unk_14 != -1 && entry->flagE == -1) {
        UnkStruct_020918d8 *obj = self->obj;
        obj->x = entry->a + (*obj->vecs)->x;
        obj->y = entry->b + (*obj->vecs)->y;
        obj->z = entry->c + (*obj->vecs)->z;
        success = 1;
    }

    if (!success) {
        Node *node = self->obj->list;
        while (node != 0) {
            node->dst = node->src;
            node = node->next;
        }
        func_020914dc((void *) entry);
    }

    return success;
}

int func_0209184c(Param *p)
{
    Key tmp;
    Elem *e;
    int result;
    UnkStruct_0209184c *obj;

    tmp = p->key;
    e = &((Elem *) data_021d52d8)[tmp.b[0]];
    result = 0;
    if ((e->unk_14 != (-1)) && (e->unk_0E != 0)) {
        obj = p->obj;
        obj->unk_20 = e->unk_00 + (*obj->unk_18)[1];
        obj->unk_24 = e->unk_04 + (*obj->unk_18)[2];
        obj->unk_28 = e->unk_08 + (*obj->unk_18)[3];
        if (e->unk_0E > 0) {
            ((unsigned char *) p->obj)[0x69] = (unsigned char) (6 * e->unk_0E);
            e->unk_0E--;
        }
        result = 1;
    }
    if (result == 0) {
        func_020914dc(e);
    }
    return result;
}

void func_02091824(int r0, int r1, int r2, int r3)
{
    int sp[2];
    sp[0] = r3;
    sp[1] = (unsigned int) data_020e2a1c;
    func_02094b58(0x10, r0, r1, r2, sp[0], sp[1]);
}

void func_02091810(void *src)
{
    func_020913c8((void *) ((unsigned char *) data_021d52d8), src, 4);
}

void func_020917ec(int a, int b, int c, int d)
{
    func_02094cf8(0x11, a, b, c, d, 0);
}

void func_020917c8(int r0, int r1, int r2, int r3)
{
    int sp8;
    int sp4;

    sp4 = 0;
    sp8 = r3;
    func_02094cf8(0x12, r0, r1, r2, sp8, sp4);
}
