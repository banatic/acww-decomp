/* outdoor_villager_walks_2: 6 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_0226c170 @ 0x0226c170, 0x6c bytes, Thumb
 * func_ov068_0226c0f4 @ 0x0226c0f4, 0x7c bytes, Thumb
 * func_ov068_0226c0e0 @ 0x0226c0e0, 0x14 bytes, Thumb
 * func_ov068_0226c0a4 @ 0x0226c0a4, 0x3c bytes, Thumb
 * func_ov068_0226c034 @ 0x0226c034, 0x70 bytes, Thumb
 * func_ov068_0226befc @ 0x0226befc, 0x138 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y;
} UnkStruct_0226c170;

typedef struct {
    unsigned short id;
} UnkStruct_0226c170_2;

typedef struct {
    fx32 x, y;
} UnkStruct_0226c0f4;

typedef struct {
    fx32 x, y, z;
} Vec;

typedef struct UnkStruct_0226befc {
    unsigned char pad_00[0x98];
    void *unk_98;
    unsigned char pad_9C[0x9F4 - 0x9C];
    unsigned char unk_9F4[0x12];
    unsigned short unk_A06;
} UnkStruct_0226befc;

extern void *data_021c80bc; // 0x021c80bc
extern UnkStruct_0226c170_2 *func_0204f5e0(void *, int, int, int, int, int);
extern int func_0204f294(void *, int, int);
extern void func_0204f818(fx32 *, fx32 *, void *);
extern void func_0204f7e0(Vec *, void *);
extern int func_020ea990(Vec *, void *);
extern int func_0201c444(void *);
extern int func_02043830(int, UnkStruct_0226c0f4 *);
extern int func_020436a8(int);
extern void func_020431b8(int);
extern unsigned int func_ov003_02219be0(void);
extern int func_ov068_0226cf8c(void *);
extern int func_0201c378(void *, unsigned int);
extern int func_0201ac28(void *, void *);
extern int func_0201a7fc(void *);
extern int func_ov068_0226c8b0(void *obj, const void *ptr);
extern void func_0202e118(void *, const void *);
extern void func_ov068_0226cce8(void *, const void *, int);
extern void func_ov068_0226cce4(void *, int);
extern int func_ov068_0226cc20(const void *, const void *);
extern int func_ov068_0226c520(const void *, const void *);
extern int func_ov068_02266e7c(const void *);
extern int func_ov068_0226c1dc(const void *, const void *);
extern int func_ov068_0226c63c(const void *, const void *);
extern short data_ov068_02276724[];

int func_ov068_0226c170(void *unused, UnkStruct_0226c170 *p)
{
    void *g = data_021c80bc;
    UnkStruct_0226c170_2 *e;
    unsigned int ok;
    int r;
    int x, y, hx, hy;
    if (g != 0) {
        x = p->x;
        y = p->y;
        hx = x >> 4;
        hy = y >> 4;
        e = func_0204f5e0(g, hx, hy, x - (hx << 4), y - (hy << 4), 0);
        if (e != 0) {
            r = 0;
            ok = 0;
            if (e->id >= 0x1566 && e->id <= 0x1566) {
                ok = 1;
            }
            if (ok != 0) {
                if (func_0204f294(g, p->x, p->y) != 0) {
                    r = 1;
                }
            }
            return r;
        }
    }
    return 0;
}

int func_ov068_0226c0f4(void *a1, void *a2)
{
    UnkStruct_0226c0f4 p;
    UnkStruct_0226c0f4 p2;
    Vec v;
    int r;
    int h;
    void *q = (char *) a2 + 0x5c;
    r = 0;
    p.x = 0;
    p.y = 0;
    func_0204f818(&p.x, &p.y, q);
    if (func_ov068_0226c170(a1, (UnkStruct_0226c170 *) (&p)) != 0) {
        func_0204f7e0(&v, q);
        if (func_020ea990(&v, q) <= 0xb00) {
            p2.x = p.x;
            p2.y = p.y;
            h = func_02043830((signed char) func_0201c444(a2), &p2);
            if (h >= 0) {
                if (func_020436a8(h) == 1) {
                    r = 1;
                }
                func_020431b8(h);
            }
        }
    }
    return r;
}

int func_ov068_0226c0e0(int unused, unsigned char *p)
{
    if (p[0xa05] != 0) {
        return 1;
    }
    return 0;
}

int func_ov068_0226c0a4(unsigned int param)
{
    unsigned int x;
    x = func_ov003_02219be0();
    if ((x >= 0x12e8u && x <= 0x131fu) || (x >= 0x12b0u && x <= 0x12e7u)) {
        return 1;
    } else {
        return 0;
    }
}

int func_ov068_0226c034(void *a0, void *a1)
{
    int call_res;

    call_res = func_ov068_0226cf8c(a1);
    if (*((unsigned char *) a0 + 0xE0) != 0) {
        goto fail;
    }
    if (call_res != 0 && call_res != 1) {
        goto fail;
    }
    if (func_ov068_0226c0a4((unsigned int) a0) == 0) {
        goto fail;
    }
    if (*((unsigned char *) a1 + 0x3B0) != 1) {
        goto fail;
    }
    if (func_0201c378(a1, 4) > 0x6000) {
        goto fail;
    }
    if (func_0201ac28((unsigned char *) a1 + 0x3B0, a1) == 0) {
        goto fail;
    }
    if (func_0201a7fc((unsigned char *) a1 + 0x3B0) == 0) {
        goto fail;
    }
    return 1;
fail:
    return 0;
}

int func_ov068_0226befc(void *obj, const void *ptr)
{
    int flag = 0;
    char buffer[8];

    if (func_ov068_0226c8b0(obj, ptr)) {
        func_0202e118(buffer, ptr);
        if (*(unsigned short *) buffer != 0xFFF1) {
            func_ov068_0226cce8(obj, ptr, 0x10);
            func_ov068_0226cce4(obj, 2);
        } else {
            func_ov068_0226cce8(obj, ptr, 2);
        }
        flag = 1;
        goto exit;
    }

    if (func_ov068_0226c0f4((void *) obj, (void *) ptr)) {
        func_ov068_0226cce8(obj, ptr, 0x11);
        flag = 1;
        goto exit;
    }

    if (((const UnkStruct_0226befc *) ptr)->unk_A06 >= data_ov068_02276724[0]) {
        func_ov068_0226cce8(obj, ptr, 0x15);
        flag = 1;
        goto exit;
    }

    if (func_ov068_0226c0e0((int) obj, (unsigned char *) ptr)) {
        func_ov068_0226cce8(obj, ptr, 0x13);
        flag = 1;
        goto exit;
    }

    if (func_ov068_0226cc20(obj, ptr)) {
        func_ov068_0226cce8(obj, ptr, 7);
        flag = 1;
        goto exit;
    }

    if (func_ov068_0226c520(obj, ptr)) {
        flag = 1;
        goto exit;
    }

    if (func_ov068_02266e7c(&((const UnkStruct_0226befc *) ptr)->unk_9F4[0])) {
        func_ov068_0226cce8(obj, ptr, 0x0b);
        flag = 1;
        goto exit;
    }

    if (func_ov068_0226c1dc(obj, ptr)) {
        flag = 1;
        goto exit;
    }

    if (func_ov068_0226c034((void *) obj, (void *) ptr)) {
        func_ov068_0226cce8(obj, ptr, 0x17);
        flag = 1;
        goto exit;
    }

    if (((const UnkStruct_0226befc *) ptr)->unk_98 != 0) {
        if (func_ov068_0226c63c(obj, ptr)) {
            flag = 1;
        }
    }

exit:
    return flag;
}
