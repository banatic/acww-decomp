/* scene_motion_7: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020183cc @ 0x020183cc, 0x19c bytes, Thumb
 * func_02018340 @ 0x02018340, 0x8c bytes, Thumb
 * func_02018304 @ 0x02018304, 0x3c bytes, Thumb
 * func_02018298 @ 0x02018298, 0x6c bytes, Thumb
 * func_02018090 @ 0x02018090, 0x208 bytes, Thumb
 * func_02017ff4 @ 0x02017ff4, 0x9c bytes, Thumb
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

typedef struct {
    int x, y, z;
} UnkStruct_02018090;

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
extern void func_02012444(u32, u16, int);
extern char data_021fbee8;
extern int func_020164cc(void *ptr, int);
extern int func_02057d0c(int a, void *ptr);
extern void func_02016764(void *, void *, int, unsigned short, int, int, int, int);
extern volatile unsigned short data_020c80f8;
extern int func_02057cf4(void);
extern void func_02057cb8(void *b);
extern int func_02091230(int a, void *b, int c, int d);
extern int func_0200442c(void *a, int b, int c, int d);
extern void func_02054188(void *a, int b, int c);
extern void func_02019af0(void *a, int b);
extern int func_020912d4(int a, UnkStruct_02018090 *b, short *c, int d);
extern void func_0209129c(u32 w);
extern void func_02091278(u32 w, void *p1, void *p2, int p3);

static __inline void do_A(struct UnkStruct_020183cc *p1, struct UnkStruct_020183cc_2 *p2)
{
    u16 g = (*(u16 *) &data_020c80f8);
    func_02016764(&p2->unk_334, p2, 0x25, (u16) (*(volatile u16 *) ((u16 *) &data_020c80f8)), 1, 0x1000, 0, 0);
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
        func_0201b1a4(&p2->unk_350, p2, 1, 0, (*(u16 *) &data_020c80f8));
        p1->state = 1;
    }
}

void func_02018340(char *obj, char *src)
{
    unsigned short h;
    int v;

    if (func_02057c68((struct UnkStruct_020183cc_2 *) src) == 0) {
        return;
    }

    h = (*(unsigned short *) &data_020c80f8);
    func_0201b1a4(src + 0x350, (struct UnkStruct_020183cc_2 *) src, 0, 0, h);
    func_0201b044(src + 0x350, (struct Local2 *) (&data_021fbee8));
    func_0201afd4(src + 0x350, (struct Local2 *) (&data_021fbee8));
    func_02016764(src + 0x334, src, 0x25, h, 1, 0x1000, 0, 0);

    v = *(int *) (src + 0x628);
    if (v != 0) {
        func_02012444(v, h, 0);
    }

    *(unsigned char *) (obj + 0x98) = 2;
}

void func_02018304(void *arg0, void *arg1)
{
    int result;
    char *ptr;

    result = func_020164cc((char *) arg1 + 0x334, (int) arg1);
    if (result != 0) {
        result = func_02057c20((struct UnkStruct_020183cc_2 *) arg1);
        if (result != 0) {
            result = func_02057d0c(3, arg1);
            if (result != 0) {
                ptr = (char *) arg0 + 0x98;
                *ptr = 3;
            }
        }
    }
}

void func_02018298(void *self, void *other)
{
    unsigned short h;
    unsigned int v;

    if (func_02057bf0(3) != 0) {
        return;
    }
    if (func_02057d0c(4, other) == 0) {
        return;
    }

    h = data_020c80f8;
    func_02016764((char *) other + 0x334, other, 0x26, data_020c80f8, 1, 0x1000, 0, 0);

    v = *(unsigned int *) ((char *) other + 0x628);
    if (v != 0) {
        func_02012444(v, (unsigned short) h, 0);
    }
    *(unsigned char *) ((char *) self + 0x98) = 4;
}

void func_02018090(void *param1, void *param2)
{
    short aa;
    UnkStruct_02018090 v;

    if (func_020164cc((void *) (((char *) param2) + 0x334), (int) param2) == 0) {
        return;
    }

    switch (func_02057cf4()) {
        case 6:
            func_02057cb8(param2);
            func_02016764((void *) (((char *) param2) + 0x334), param2, 0x28, data_020c80f8, 1, 0x1000, 0, 0);
            func_02091230(0x61, (void *) (((char *) param2) + 0x5c), 0, 0);
            func_0200442c((void *) (((char *) param2) + 0x514), 0x76, 0x7f, 0);
            *(u8 *) (((char *) param1) + 0x98) = 6;
            break;
        case 7:
            if (func_02057d0c(7, param2) == 0) {
                return;
            }
            func_02016764((void *) (((char *) param2) + 0x334), param2, 0x26, data_020c80f8, 3, 0x1000, 0, 0);
            *(u8 *) (((char *) param1) + 0x98) = 7;
            break;
        case 5:
            if (func_02057d0c(5, param2) == 0) {
                return;
            }
            func_02016764((void *) (((char *) param2) + 0x334), param2, 0x27, data_020c80f8, 1, 0x1000, 0, 0);
            func_0200442c((void *) (((char *) param2) + 0x514), 0x4f, 0x7f, 0);
            *(u8 *) (((char *) param1) + 0x98) = 5;
            break;
        case 10:
            if (func_02057d0c(0xa, param2) == 0) {
                return;
            }
            func_02016764((void *) (((char *) param2) + 0x334), param2, 0, data_020c80f8, 0, 0x1000, 0, 0);
            func_02016764((void *) (((char *) param2) + 0x334), param2, 0x139, 0, 0, 0x1000, 0, 1);
            func_02054188((void *) (((char *) param2) + 0xec), 9, 0xe);
            func_02019af0(param1, 1);
            *(u8 *) (((char *) param1) + 0x98) = 0x14;
            break;
        case 11:
            if (func_02057d0c(0xb, param2) == 0) {
                return;
            }
            v.x = *(int *) (((char *) param2) + 0x478);
            v.y = *(int *) (((char *) param2) + 0x47c);
            v.z = *(int *) (((char *) param2) + 0x480);
            aa = *(short *) (((char *) param2) + 0x8e);
            func_02016764((void *) (((char *) param2) + 0x334), param2, 0x29, data_020c80f8, 1, 0x1000, 0, 0);
            *(int *) (((char *) param1) + 0xac) = func_020912d4(0x40, &v, &aa, 0);
            *(u8 *) (((char *) param1) + 0x98) = 0xb;
            break;
        default:
            func_02016764((void *) (((char *) param2) + 0x334), param2, 0x24, data_020c80f8, 0, 0x1000, 0, 0);
            func_02019af0(param1, 1);
            *(u8 *) (((char *) param1) + 0x98) = 0x14;
            break;
    }
}

void func_02017ff4(char *a, char *b)
{
    u16 v;
    u32 x;
    u32 w;

    if (func_020164cc(b + 0x334, (int) b) != 0) {
        v = data_020c80f8;
        func_02016764(b + 0x334, b, 0, data_020c80f8, 0, 0x1000, 0, 0);
        x = *(u32 *) (b + 0x628);
        if (x != 0) {
            func_02012444(x, v, 0);
        }
        func_02057cb8(b);
        w = *(u32 *) (a + 0xac);
        if (w != -1) {
            func_0209129c(w);
        }
        func_02019af0(a, 1);
        *(u8 *) (a + 0x98) = 0x14;
    } else {
        w = *(u32 *) (a + 0xac);
        if (w != -1) {
            func_02091278(w, b + 0x478, b + 0x8e, 0);
        }
    }
}
