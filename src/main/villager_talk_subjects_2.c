/* villager_talk_subjects_2: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02022bbc @ 0x02022bbc, 0x70 bytes, Thumb
 * func_02022ad4 @ 0x02022ad4, 0xe8 bytes, Thumb
 * func_020229ec @ 0x020229ec, 0xe8 bytes, Thumb
 * func_020229a0 @ 0x020229a0, 0x4c bytes, Thumb
 * func_02022938 @ 0x02022938, 0x68 bytes, Thumb
 * func_020228e4 @ 0x020228e4, 0x54 bytes, Thumb
 * func_02022840 @ 0x02022840, 0xa4 bytes, Thumb
 */

#include "types.h"

#define ITEM_NONE 0xfff1

struct Inner_02022bbc {
    char pad_00[0x830];
    int unk_830;
};

struct Outer_02022bbc {
    char pad_00[0x100];
    struct Inner_02022bbc *inner;
};

struct Arg2_02022bbc {
    int unk_00;
    unsigned char unk_04;
};

typedef struct UnkStruct_02022ad4 {
    volatile u16 a;
    volatile u16 b;
    u16 c;
    u16 d;
} UnkStruct_02022ad4;

typedef struct UnkStruct_02022ad4_2 {
    u8 pad_00[0x830];
    int unk_830;
} UnkStruct_02022ad4_2;

typedef struct UnkStruct_02022ad4_3 {
    u8 pad_00[0x100];
    UnkStruct_02022ad4_2 *unk_100;
    u8 unk_104[0x1e];
    u8 unk_122;
} UnkStruct_02022ad4_3;

typedef struct Settings {
    int unk_00;
    u8 unk_04;
} Settings;

typedef struct UnkStruct_020229ec {
    volatile u16 a;
    volatile u16 b;
    u16 c;
    u16 d;
} UnkStruct_020229ec;

typedef struct UnkStruct_020229ec_2 {
    u8 pad_00[0x830];
    int unk_830;
} UnkStruct_020229ec_2;

typedef struct UnkStruct_020229ec_3 {
    u8 pad_00[0x100];
    UnkStruct_020229ec_2 *unk_100;
    u8 unk_104[0x1e];
    u8 unk_122;
} UnkStruct_020229ec_3;

struct UnkStruct_020229a0 {
    unsigned char pad_00[0x100];
    int unk_100;
};

typedef struct {
    u8 pad_00[0x830];
    u8 *name;
} Player;

typedef struct {
    u8 pad_00[0x100];
    Player *player;
} UnkStruct_02022938;

struct UnkStruct_020228e4 {
    unsigned char pad_00[0x100];
    unsigned int unk_100;
};

// Filled in by func_0202e118. The halfword is volatile; it is read once per bound.
typedef struct UnkStruct_02022840 {
    volatile u16 value;
    volatile u16 unk_02;
} UnkStruct_02022840;

typedef struct UnkStruct_02022840_2 {
    u8 pad_00[0x830];
    int unk_830;
} UnkStruct_02022840_2;

typedef struct UnkStruct_02022840_3 {
    u8 pad_00[0x100];
    UnkStruct_02022840_2 *unk_100;
    u8 pad_104[0x200];
} UnkStruct_02022840_3;

extern void *func_0209b5ec(void *);
extern int func_0209c330(unsigned char *);
extern int func_020036e8(unsigned char *);
extern int func_0202da38(void *, char *, char *, int, int, int, int, int, int);
extern Settings data_020c8b48;
extern void func_0202e118(volatile u16 *out, UnkStruct_02022ad4_2 *p);
extern int func_0207f1c8(int a);
extern void func_0202cfa8(UnkStruct_02022ad4 *p);
extern void func_02015de4(UnkStruct_02022ad4_3 *self, UnkStruct_02022ad4 *p, int a, int b);
extern int func_0208150c(int a);
extern Settings data_020c8d40;
extern void func_0202cac4(UnkStruct_020229ec *p);
extern char data_020c8d30;
extern void func_0202bd40(UnkStruct_02022938 *self, int n, u8 *name);
extern const u8 data_020c8d28[];
extern unsigned char data_020c8a68[];
extern Settings data_020c8b08;

void func_02022bbc(struct Outer_02022bbc *a0, int arg1, struct Arg2_02022bbc *arg2)
{
    int flag;
    int ret;

    flag = (arg1 != func_0209c330((unsigned char *) func_0209b5ec((void *) (unsigned int) func_0207f1c8(a0->inner->unk_830))))
               ? 1
               : 0;

    ret = func_020036e8((unsigned char *) (unsigned int) func_0208150c(a0->inner->unk_830));

    func_0202da38(a0, (char *) a0 + 0x104, (char *) a0 + 0x122, 0x1e, ret, arg2->unk_00, arg2->unk_04, flag, 0);
}

int func_02022ad4(UnkStruct_02022ad4_3 *self)
{
    int state;
    UnkStruct_02022ad4 info;

    state = -1;
    func_0202e118(&info.b, self->unk_100);
    {
        unsigned int ok = 0;
        u16 hi;
        u16 lo;

        hi = info.b;
        lo = info.b;
        if (lo >= 0x1376 && hi <= 0x1376) {
            ok = 1;
        }
        if (ok > 0) {
            state = 0;
            if (func_0209c330((unsigned char *) func_0209b5ec((void *) func_0207f1c8(self->unk_100->unk_830))) != 0) {
                state = 2;
            }
        }
    }
    if (state != -1) {
        info.a = 0xfff1;
        func_0202cfa8(&info);
        {
            unsigned int ok2 = 0;
            u16 hi2;
            u16 lo2;

            hi2 = info.a;
            lo2 = info.a;
            if (lo2 >= 0x12b0 && hi2 <= 0x12e7) {
                ok2 = 1;
            }
            if (ok2 > 0) {
                func_02015de4(self, &info, 0, 7);
                func_0202da38((void *) self, (char *) self->unk_104, (char *) (&self->unk_122), 0x1e,
                              func_020036e8((unsigned char *) (func_0208150c(self->unk_100->unk_830))), data_020c8b48.unk_00,
                              data_020c8b48.unk_04, state, 0);
                return 1;
            }
        }
    }
    return 0;
}

int func_020229ec(UnkStruct_020229ec_3 *self)
{
    int state;
    UnkStruct_020229ec info;

    state = -1;
    func_0202e118(&info.b, (UnkStruct_02022ad4_2 *) self->unk_100);
    {
        unsigned int ok = 0;
        u16 hi;
        u16 lo;

        hi = info.b;
        lo = info.b;
        if (lo >= 0x1374 && hi <= 0x1374) {
            ok = 1;
        }
        if (ok > 0) {
            state = 0;
            if (func_0209c330((unsigned char *) func_0209b5ec((void *) func_0207f1c8(self->unk_100->unk_830))) != 1) {
                state = 1;
            }
        }
    }
    if (state != -1) {
        info.a = 0xfff1;
        func_0202cac4(&info);
        {
            unsigned int ok2 = 0;
            u16 hi2;
            u16 lo2;

            hi2 = info.a;
            lo2 = info.a;
            if (lo2 >= 0x12e8 && hi2 <= 0x131f) {
                ok2 = 1;
            }
            if (ok2 > 0) {
                func_02015de4((UnkStruct_02022ad4_3 *) self, (UnkStruct_02022ad4 *) (&info), 0, 7);
                func_0202da38((void *) self, (char *) self->unk_104, (char *) (&self->unk_122), 0x1e,
                              func_020036e8((unsigned char *) (func_0208150c(self->unk_100->unk_830))), data_020c8d40.unk_00,
                              data_020c8d40.unk_04, state, 0);
                return 1;
            }
        }
    }
    return 0;
}

int func_020229a0(struct UnkStruct_020229a0 *p)
{
    unsigned char buf[8];
    volatile unsigned short *vp;
    unsigned short a, b;
    int cond;

    func_0202e118((volatile u16 *) buf, (UnkStruct_02022ad4_2 *) p->unk_100);

    cond = 0;
    vp = (volatile unsigned short *) buf;
    b = vp[0];
    a = vp[0];

    if (a >= 0x1369 && b <= 0x1369) {
        cond = 1;
    }

    if (cond) {
        func_02022bbc((struct Outer_02022bbc *) p, 2, (struct Arg2_02022bbc *) (&data_020c8d30));
        return 1;
    }
    return 0;
}

static inline BOOL ItemIsNone(const u16 *item)
{
    return *item == ITEM_NONE;
}

static inline BOOL ItemIsSpecial(const u16 *item)
{
    return *item >= 0x1380 && *item <= 0x139f;
}

int func_02022938(UnkStruct_02022938 *self)
{
    u16 item;

    func_0202e118((volatile u16 *) (&item), (UnkStruct_02022ad4_2 *) self->player);
    if (ItemIsNone(&item) || ItemIsSpecial(&item)) {
        func_02022bbc((struct Outer_02022bbc *) self, 3, (struct Arg2_02022bbc *) data_020c8d28);
        func_0202bd40(self, 5, self->player->name);
        return 1;
    }
    return 0;
}

int func_020228e4(struct UnkStruct_020228e4 *obj)
{
    unsigned short result;
    unsigned short b;
    unsigned short a;

    func_0202e118((volatile u16 *) (&result), (UnkStruct_02022ad4_2 *) obj->unk_100);
    b = *(volatile unsigned short *) &result;
    a = *(volatile unsigned short *) &result;

    if (a == 0xfff1 || (b >= 0x1380 && b <= 0x139f)) {
        func_02022bbc((struct Outer_02022bbc *) obj, 4, (struct Arg2_02022bbc *) data_020c8a68);
        return 1;
    }
    return 0;
}

int func_02022840(UnkStruct_02022840_3 *self)
{
    int state;
    UnkStruct_02022840 info;

    state = -1;
    func_0202e118((volatile u16 *) (&info), (UnkStruct_02022ad4_2 *) self->unk_100);
    {
        unsigned int ok = 0;
        u16 hi;
        u16 lo;

        hi = info.value;
        lo = info.value;
        if (lo >= 0x1378 && hi <= 0x1378) {
            ok = 1;
        }
        if (ok > 0) {
            state = 0;
            if (func_0209c330((unsigned char *) func_0209b5ec((void *) func_0207f1c8(self->unk_100->unk_830))) != 5) {
                state = 2;
            }
        }
    }
    if (state != -1) {
        func_0202da38((void *) self, (char *) ((u8 *) self + 0x104), (char *) ((u8 *) self + 0x122), 0x1e,
                      func_020036e8((unsigned char *) func_0208150c(self->unk_100->unk_830)), data_020c8b08.unk_00,
                      data_020c8b08.unk_04, state, 0);
        return 1;
    }
    return 0;
}
