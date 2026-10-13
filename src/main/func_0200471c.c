/* func_0200471c @ 0x0200471c, 0x410 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0200471c_3 UnkStruct_0200471c_3;
typedef struct Vt {
    void (*unk_00)(UnkStruct_0200471c_3 *);
    void (*unk_04)(UnkStruct_0200471c_3 *);
    void (*unk_08)(UnkStruct_0200471c_3 *);
    void (*unk_0C)(UnkStruct_0200471c_3 *);
} Vt;
struct UnkStruct_0200471c_3 {
    Vt *vt;
};

typedef struct {
    u8 unk_00, unk_01, unk_02, unk_03;
} UnkStruct_0200471c;
typedef struct {
    u32 lo, hi;
} UnkStruct_0200471c_2;

extern u8 data_020e54a8;
extern UnkStruct_0200471c_3 *data_0213fff0;

extern void *func_020edb54(int);
extern void func_0209def4(UnkStruct_0200471c *);
extern u8 func_020b65c4(void);
extern int func_020b22b8(void);
extern int func_020b22dc(void);
extern int func_020b6640(void);
extern void func_0209e474(UnkStruct_0200471c_2 *);
extern void MI_CpuCopy8(void *, void *, int);
extern int func_0203fc78(int, UnkStruct_0200471c_2 *, int);

extern void *func_020f2590(void *);
extern void *func_020f2664(void *);
extern void *func_020f2720(void *);
extern void *func_020f2814(void *);
extern void *func_020f28d8(void *);
extern void *func_020f29a4(void *);
extern void *func_020f2a68(void *);
extern void *func_020f2b2c(void *);
extern void *func_020f2bf0(void *);
extern void *func_020f2cb4(void *);
extern void *func_020f2d78(void *);
extern void *func_020f2e3c(void *);
extern void *func_020f2f84(void *);
extern void *func_020f3050(void *);
extern void *func_020f3114(void *);
extern void *func_020f31e8(void *);
extern void *func_020f32bc(void *);
extern void *func_020f3390(void *);
extern void *func_020f3464(void *);
extern void *func_020f3538(void *);
extern void *func_020f35fc(void *);
extern void *func_020f36d0(void *);
extern void *func_020f3794(void *);
extern void *func_020f3858(void *);
extern void *func_020f391c(void *);
extern void *func_020f39e0(void *);
extern void *func_020f3be8(void *);
extern void *func_020f3cd4(void *);
extern void *func_020f3dc4(void *);
extern void *func_020f3f88(void *);

void func_0200471c(void)
{
    UnkStruct_0200471c a;
    UnkStruct_0200471c_2 b, c, d, e;
    void *p;
    unsigned int t;
    unsigned int t2;
    u8 x;

    x = data_020e54a8;
    t = (x == 0) ? 1 : 0;
    if (t != 0) {
        goto sw;
    }
    t2 = (x == 1) ? 1 : 0;
    if (t2 != 0) {
        goto sw;
    }
    p = func_020edb54(8);
    if (p != 0) {
        p = func_020f2590(p);
    }
    data_0213fff0 = (UnkStruct_0200471c_3 *) p;
    goto tail;
sw:
    func_0209def4(&a);
    switch (func_020b65c4()) {
        case 6:
        case 7:
        case 8:
            p = func_020edb54(8);
            if (p != 0) {
                p = func_020f39e0(p);
            }
            data_0213fff0 = (UnkStruct_0200471c_3 *) p;
            break;
        case 9:
            p = func_020edb54(8);
            if (p != 0) {
                p = func_020f391c(p);
            }
            data_0213fff0 = (UnkStruct_0200471c_3 *) p;
            break;
        case 0xa:
            p = func_020edb54(8);
            if (p != 0) {
                p = func_020f3858(p);
            }
            data_0213fff0 = (UnkStruct_0200471c_3 *) p;
            break;
        case 0xb:
        case 0xc:
        case 0xd:
        case 0xe:
        case 0x2f:
            p = func_020edb54(8);
            if (p != 0) {
                p = func_020f3794(p);
            }
            data_0213fff0 = (UnkStruct_0200471c_3 *) p;
            break;
        case 0xf:
            p = func_020edb54(8);
            if (p != 0) {
                p = func_020f36d0(p);
            }
            data_0213fff0 = (UnkStruct_0200471c_3 *) p;
            break;
        case 0x10:
            p = func_020edb54(8);
            if (p != 0) {
                p = func_020f35fc(p);
            }
            data_0213fff0 = (UnkStruct_0200471c_3 *) p;
            break;
        case 0x1a:
            p = func_020edb54(8);
            if (p != 0) {
                p = func_020f3538(p);
            }
            data_0213fff0 = (UnkStruct_0200471c_3 *) p;
            break;
        case 0x1b:
            p = func_020edb54(8);
            if (p != 0) {
                p = func_020f3464(p);
            }
            data_0213fff0 = (UnkStruct_0200471c_3 *) p;
            break;
        case 0x1c:
            p = func_020edb54(8);
            if (p != 0) {
                p = func_020f3390(p);
            }
            data_0213fff0 = (UnkStruct_0200471c_3 *) p;
            break;
        case 0x1d:
            p = func_020edb54(8);
            if (p != 0) {
                p = func_020f32bc(p);
            }
            data_0213fff0 = (UnkStruct_0200471c_3 *) p;
            break;
        case 0x1e:
            p = func_020edb54(8);
            if (p != 0) {
                p = func_020f31e8(p);
            }
            data_0213fff0 = (UnkStruct_0200471c_3 *) p;
            break;
        case 0x1f:
            p = func_020edb54(8);
            if (p != 0) {
                p = func_020f3114(p);
            }
            data_0213fff0 = (UnkStruct_0200471c_3 *) p;
            break;
        case 0x20:
            p = func_020edb54(8);
            if (p != 0) {
                p = func_020f3050(p);
            }
            data_0213fff0 = (UnkStruct_0200471c_3 *) p;
            break;
        case 0x21:
            p = func_020edb54(0x38);
            if (p != 0) {
                p = func_020f2f84(p);
            }
            data_0213fff0 = (UnkStruct_0200471c_3 *) p;
            break;
        case 0x22:
            p = func_020edb54(8);
            if (p != 0) {
                p = func_020f2e3c(p);
            }
            data_0213fff0 = (UnkStruct_0200471c_3 *) p;
            break;
        case 0x23:
        case 0x24:
            p = func_020edb54(8);
            if (p != 0) {
                p = func_020f2d78(p);
            }
            data_0213fff0 = (UnkStruct_0200471c_3 *) p;
            break;
        case 0x25:
        case 0x26:
            p = func_020edb54(8);
            if (p != 0) {
                p = func_020f2cb4(p);
            }
            data_0213fff0 = (UnkStruct_0200471c_3 *) p;
            break;
        case 0x27:
            p = func_020edb54(8);
            if (p != 0) {
                p = func_020f2bf0(p);
            }
            data_0213fff0 = (UnkStruct_0200471c_3 *) p;
            break;
        case 0x28:
            if (a.unk_01 >= 8 && a.unk_01 < 0x11) {
                p = func_020edb54(8);
                if (p != 0) {
                    p = func_020f2a68(p);
                }
                data_0213fff0 = (UnkStruct_0200471c_3 *) p;
            } else {
                p = func_020edb54(8);
                if (p != 0) {
                    p = func_020f2b2c(p);
                }
                data_0213fff0 = (UnkStruct_0200471c_3 *) p;
            }
            break;
        case 0x29:
            p = func_020edb54(8);
            if (p != 0) {
                p = func_020f29a4(p);
            }
            data_0213fff0 = (UnkStruct_0200471c_3 *) p;
            break;
        case 0x2c:
            p = func_020edb54(8);
            if (p != 0) {
                p = func_020f28d8(p);
            }
            data_0213fff0 = (UnkStruct_0200471c_3 *) p;
            break;
        case 0x2d:
            p = func_020edb54(8);
            if (p != 0) {
                p = func_020f2814(p);
            }
            data_0213fff0 = (UnkStruct_0200471c_3 *) p;
            break;
        case 0x2e:
        case 0x30:
            p = func_020edb54(8);
            if (p != 0) {
                p = func_020f2720(p);
            }
            data_0213fff0 = (UnkStruct_0200471c_3 *) p;
            break;
        case 0x32:
            p = func_020edb54(8);
            if (p != 0) {
                p = func_020f2590(p);
            }
            data_0213fff0 = (UnkStruct_0200471c_3 *) p;
            break;
        default:
            t = (data_020e54a8 == 0) ? 1 : 0;
            if (t == 0) {
                p = func_020edb54(0x20);
                if (p != 0) {
                    p = func_020f3be8(p);
                }
                data_0213fff0 = (UnkStruct_0200471c_3 *) p;
                break;
            }
            if (func_020b22b8() != 0 || func_020b22dc() != 0) {
                p = func_020edb54(8);
                if (p != 0) {
                    p = func_020f3dc4(p);
                }
                data_0213fff0 = (UnkStruct_0200471c_3 *) p;
                break;
            }
            if (func_020b6640() != 0) {
                p = func_020edb54(8);
                if (p != 0) {
                    p = func_020f2664(p);
                }
                data_0213fff0 = (UnkStruct_0200471c_3 *) p;
                break;
            }
            b.lo = 0;
            b.hi = 0;
            func_0209e474(&b);
            MI_CpuCopy8(&b, &c, 8);
            t = (func_0203fc78(0xf, &c, 0) != 0) ? 1 : 0;
            if (t != 0) {
                p = func_020edb54(8);
                if (p != 0) {
                    p = func_020f3cd4(p);
                }
                data_0213fff0 = (UnkStruct_0200471c_3 *) p;
                break;
            }
            MI_CpuCopy8(&b, &d, 8);
            t = (func_0203fc78(0x12, &d, 0) != 0) ? 1 : 0;
            if (t != 0) {
                p = func_020edb54(8);
                if (p != 0) {
                    p = func_020f3cd4(p);
                }
                data_0213fff0 = (UnkStruct_0200471c_3 *) p;
                break;
            }
            MI_CpuCopy8(&b, &e, 8);
            t = (func_0203fc78(0x13, &e, 0) != 0) ? 1 : 0;
            if (t != 0) {
                if (((u8 *) &b)[2] < 2) {
                    p = func_020edb54(8);
                    if (p != 0) {
                        p = func_020f3cd4(p);
                    }
                    data_0213fff0 = (UnkStruct_0200471c_3 *) p;
                } else {
                    p = func_020edb54(8);
                    if (p != 0) {
                        p = func_020f3f88(p);
                    }
                    data_0213fff0 = (UnkStruct_0200471c_3 *) p;
                }
            } else {
                p = func_020edb54(8);
                if (p != 0) {
                    p = func_020f3f88(p);
                }
                data_0213fff0 = (UnkStruct_0200471c_3 *) p;
            }
            break;
    }
tail:
    data_0213fff0->vt->unk_0C(data_0213fff0);
}
