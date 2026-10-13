/* func_020183cc @ 0x020183cc, 0x19c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_020183cc {
    u8 pad_00[0x98];
    u8 state;
};

struct UnkStruct_020183cc_2 {
    u8 pad_00[0xea];
    u16 magic;
    u8 pad_EC[0x334 - 0xea - 2];
    u8 unk_334[0x350 - 0x334];
    u8 unk_350[0x628 - 0x350];
    u32 unk_628;
};

struct UnkStruct_020183cc_3 {
    u8 pad_00[0x22];
    u16 magic2;
    u32 other;
};

struct Local2 {
    u32 a;
    u32 b;
    u32 c;
    u32 d;
};

extern u16 data_020c80f8;

extern int func_02057bf0(int);
extern void *func_02019de4(struct UnkStruct_020183cc *);
extern int func_0204bcdc(void *);
extern int func_0204bc64(void *);
extern int func_02057c68(struct UnkStruct_020183cc_2 *);
extern int func_02057c20(struct UnkStruct_020183cc_2 *);
extern int func_020b65c4(void);
extern int func_02057c44(struct Local2 *);
extern void func_0201b044(void *, struct Local2 *);
extern void func_0201afd4(void *, struct Local2 *);
extern void func_0201b1a4(void *, struct UnkStruct_020183cc_2 *, int, int, u16);
extern void func_02016764(void *, void *, int, u16, int, int, int, int);
extern void func_02012444(u32, u16, int);

static __inline void do_A(struct UnkStruct_020183cc *p1, struct UnkStruct_020183cc_2 *p2)
{
    u16 g = data_020c80f8;
    func_02016764(&p2->unk_334, p2, 0x25, *(volatile u16 *) &data_020c80f8, 1, 0x1000, 0, 0);
    if (p2->unk_628 != 0) {
        func_02012444(p2->unk_628, g, 0);
    }
    p1->state = 2;
}

void func_020183cc(struct UnkStruct_020183cc *p1, struct UnkStruct_020183cc_2 *p2)
{
    struct UnkStruct_020183cc_3 *t;
    u16 magic[2];
    struct Local2 local2;
    unsigned int flag1, flag2;

    if (func_02057bf0(2) == 0) {
        return;
    }

    t = (struct UnkStruct_020183cc_3 *) func_02019de4(p1);

    if (func_0204bcdc((void *) &p2->magic)) {
        magic[0] = 0xd00c;
        flag1 = (func_0204bc64((void *) &p2->magic) == func_0204bc64((void *) &magic[0]));
    } else {
        flag1 = (p2->magic == 0xd00c);
    }

    if (flag1 || func_02057c68(p2)) {
        do_A(p1, p2);
        return;
    }

    if (func_0204bcdc((void *) &t->magic2)) {
        magic[1] = 0x1565;
        flag2 = (func_0204bc64((void *) &t->magic2) == func_0204bc64((void *) &magic[1]));
    } else {
        flag2 = (t->magic2 == 0x1565);
    }

    if (flag2 && t->other == 0 && (func_020b65c4() == 9 || func_020b65c4() == 0x10)) {
        if (func_02057c20(p2) != 0) {
            do_A(p1, p2);
        }
        return;
    }

    if (func_02057c44(&local2) != 0) {
        local2.b = 0;
        func_0201b044(&p2->unk_350, &local2);
        func_0201afd4(&p2->unk_350, &local2);
        func_0201b1a4(&p2->unk_350, p2, 1, 0, data_020c80f8);
        p1->state = 1;
    }
}