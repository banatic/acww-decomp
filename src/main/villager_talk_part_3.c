/* villager_talk_part_3: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02026d70 @ 0x02026d70, 0x108 bytes, Thumb
 * func_02026c9c @ 0x02026c9c, 0xd4 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02026d70_2 {
    u8 pad_00[0x830];
    void *unk_830;
};

struct This {
    u8 pad_00[0x100];
    struct UnkStruct_02026d70_2 *unk_100;
    u8 unk_104[0x1e];
    u8 unk_122;
    u8 pad_123;
    u16 unk_124;
    u8 pad_126[0x3a];
    void *unk_160;
    u8 pad_164[0x3c];
    int unk_1A0;
};

struct UnkStruct_02026d70_3 {
    u8 *p;
    u8 c;
};

struct UnkStruct_02026d70 {
    u16 a;
    u16 b;
    u16 c;
};

struct GC {
    void *x;
    u8 y;
};

typedef struct UnkStruct_02026c9c_4 {
    const void *text;
    u8 unk_04;
    u8 unk_05, unk_06, unk_07;
} UnkStruct_02026c9c_4;

typedef struct UnkStruct_02026c9c {
    u8 pad_00[0x830];
    void *unk_830;
} UnkStruct_02026c9c;

typedef struct UnkStruct_02026c9c_2 {
    u8 pad_00[0x100];
    UnkStruct_02026c9c *unk_100;
    u8 unk_104[0x1e];
    u8 unk_122;
    u8 unk_123;
    u16 unk_124;
    u8 pad_126[0x3a];
    void *unk_160;
    u8 pad_164[0x3c];
    int unk_1A0;
} UnkStruct_02026c9c_2;

typedef struct UnkStruct_02026c9c_5 {
    u8 *ptr;
    u8 unk_04;
} UnkStruct_02026c9c_5;

typedef struct UnkStruct_02026c9c_3 {
    u16 a;
    u16 b;
    unsigned int c;
} UnkStruct_02026c9c_3;

extern struct GC data_020c8da0;
extern u8 *func_0209b408(void *);
extern void func_0207de14(u16 *, void *);
extern int func_0207de70(void *, u16 *);
extern void func_0202d5e4(u16 *, int);
extern int func_0205be38(void);
extern int func_0202b510(int);
extern void func_02027170(u16 *, int);
extern unsigned int func_0208150c(void *);
extern int func_020036e8(unsigned char *);
extern int func_0202da38(struct This *, u8 *, u8 *, int, int, void *, int, int, int);
extern const UnkStruct_02026c9c_4 data_020c8d98;

void func_02026d70(struct This *t, struct UnkStruct_02026d70_3 *out)
{
    struct UnkStruct_02026d70 v;
    u8 k;

    k = *func_0209b408(t->unk_160);
    t->unk_124 = 0xfff1;
    switch (k) {
        case 0:
            func_0207de14(&v.a, t->unk_100->unk_830);
            t->unk_124 = v.a;
            if (t->unk_124 != 0xfff1) {
                func_0207de70(t->unk_100->unk_830, &t->unk_124);
            }
            break;
        case 1:
            func_0202d5e4(&v.b, 0);
            t->unk_124 = v.b;
            break;
    }
    if (t->unk_124 == 0xfff1) {
        t->unk_1A0 = func_0205be38() * 4 + 0x1f4;
        t->unk_1A0 = func_0202b510(t->unk_1A0);
        func_02027170(&v.c, t->unk_1A0);
        t->unk_124 = v.c;
    }
    func_0202da38(t, t->unk_104, &t->unk_122, 0x1e, func_020036e8((unsigned char *) func_0208150c(t->unk_100->unk_830)),
                  data_020c8da0.x, data_020c8da0.y, 0, 0);
    out->p = t->unk_104;
    out->c = t->unk_122;
}

void func_02026c9c(UnkStruct_02026c9c_2 *p, UnkStruct_02026c9c_5 *out)
{
    UnkStruct_02026c9c_3 l;
    u8 kind;

    kind = *func_0209b408(p->unk_160);
    p->unk_124 = 0xfff1;
    if (kind == 2) {
        func_0202d5e4((u16 *) (&l), 0);
        p->unk_124 = l.a;
    }
    if (p->unk_124 == 0xfff1) {
        p->unk_1A0 = func_0205be38() * 4 + 0x1f4;
        p->unk_1A0 = func_0202b510(p->unk_1A0);
        func_02027170(&l.b, p->unk_1A0);
        p->unk_124 = l.b;
    }
    func_0202da38((struct This *) p, p->unk_104, &p->unk_122, 0x1e, (int) ((void *) func_020036e8((unsigned char *) func_0208150c(p->unk_100->unk_830))), (void *) data_020c8d98.text, data_020c8d98.unk_04, 0, 0);
    out->ptr = p->unk_104;
    out->unk_04 = p->unk_122;
}
