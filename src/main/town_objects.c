/* town_objects: 11 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b260c @ 0x020b260c, 0x128 bytes, Thumb
 * func_020b25e0 @ 0x020b25e0, 0x2c bytes, Thumb
 * func_020b25a8 @ 0x020b25a8, 0x38 bytes, Thumb
 * func_020b248c @ 0x020b248c, 0x11c bytes, Thumb
 * func_020b2470 @ 0x020b2470, 0x1c bytes, Thumb
 * func_020b23ec @ 0x020b23ec, 0x84 bytes, Thumb
 * func_020b23e0 @ 0x020b23e0, 0xc bytes, Thumb
 * func_020b23d4 @ 0x020b23d4, 0xc bytes, Thumb
 * func_020b23c8 @ 0x020b23c8, 0xc bytes, Thumb
 * func_020b235c @ 0x020b235c, 0x6c bytes, Thumb
 * func_020b232c @ 0x020b232c, 0x30 bytes, Thumb
 */

#include "types.h"

typedef struct ModeIdx {
    u8 mode : 2;
    u8 idx : 6;
} ModeIdx;

typedef struct Nibble {
    u8 low : 4;
    u8 high : 4;
} Nibble;

struct Nibble_020b25e0 {
    unsigned char low : 4;
    unsigned char high : 4;
};

typedef struct {
    u8 lo : 4;
    u8 hi : 4;
} UnkStruct_020b248c;

typedef struct {
    u8 d[10];
} UnkStruct_020b248c_4;

typedef struct {
    u8 a : 2;
    u8 b : 6;
    u8 pad_01;
    UnkStruct_020b248c_4 sub;
} UnkStruct_020b248c_2;

typedef struct {
    int pad_00;
} UnkStruct_020b248c_3;

struct nibble {
    unsigned char low : 4;
    unsigned char high : 4;
};

typedef struct {
    unsigned char low : 4;
    unsigned char high : 4;
} NibbleByte;

extern Nibble data_021f4bac[];
extern u8 data_020d1f24[];
extern void *data_020ccf94;
extern int func_020b3fc0(int a);
extern void func_020b2a68(void *dst, const void *src);
extern unsigned int func_020b2a3c(void *buf);
extern int func_0204bbd4(int a);
extern int func_020b278c(int a);
extern void func_02073820(void *obj);
extern void func_020737f0(void *obj, void *buf, int a);
extern void func_02073770(void *obj, int a, int b);
extern void func_020b2a64(void *buf);
extern unsigned char data_021f4bce[];
extern unsigned char data_021f4b14;
extern int func_020b3f58(int a);
extern int func_02073d90(void *p);
extern int func_02073918(void *p, int n);
extern unsigned short data_020d1ebc[];
extern int func_020b67e8(int param);

void func_020b260c(u8 *p, int arg2)
{
    ModeIdx *m = (ModeIdx *) p;
    u32 mode = m->mode;
    u32 idx = m->idx;
    u8 buf[16];
    u32 res1;
    u32 res2;
    u8 val;
    Nibble *q;
    const u8 *src;
    void *obj;

    if (mode == 1) {
        goto set_mode;
    }
    if (mode == 2) {
        goto set_mode;
    }
    if (mode == 3) {
    set_mode:
        data_021f4bac[idx].high = mode;
        goto done;
    }

    q = &data_021f4bac[idx];
    val = q->low;
    res1 = func_020b3fc0(val);
    val = (u8) (val | (1 << arg2));
    res2 = func_020b3fc0(val);

    if (idx < 0x22) {
        src = &data_020d1f24[idx * 10];
    } else {
        src = &data_020d1f24[0];
    }

    func_020b2a68(&buf[2], src);

    if (res2 > func_020b2a3c(&buf[2])) {
        q->high = 2;
    } else {
        idx = func_0204bbd4(idx);
        if (func_020b278c(idx) != 0 && res1 == 0) {
            q->high = 3;
        } else {
            *(u8 *) q = (*(u8 *) q & ~0xf) | (val & 0xf);
            q->high = 1;
            func_020b278c(idx);
        }
    }

    buf[0] = *p;
    buf[0] = (buf[0] & ~3) | (q->high & 3);

    obj = data_020ccf94;
    func_02073820(obj);
    func_020737f0(obj, buf, 1);
    func_02073770(obj, 0x23, arg2);
    func_020b2a64(&buf[2]);

done:
    return;
}

void func_020b25e0(unsigned char *idx, unsigned int bit)
{
    ((struct Nibble_020b25e0 *) data_021f4bac)[*idx].low &= ~(1 << bit);
}

void func_020b25a8(void)
{
    unsigned char *p = ((unsigned char *) data_021f4bac);

    while (p < data_021f4bce) {
        *p &= ~0xf;
        *p &= ~0xf0;
        p++;
    }

    data_021f4b14 = 0;
}

void func_020b248c(void *a0)
{
    u32 x;
    UnkStruct_020b248c_2 m;
    u32 idx;
    UnkStruct_020b248c_3 *g;
    u8 lo;
    u32 y;
    UnkStruct_020b248c *e;

    idx = (u32) func_020b3f58((int) a0);
    g = (*(UnkStruct_020b248c_3 * *) &data_020ccf94);
    if (func_02073d90((void *) g) == 0 || func_02073918((void *) g, 0) != 0) {
        e = &((UnkStruct_020b248c *) data_021f4bac)[idx];
        lo = ((UnkStruct_020b248c *) data_021f4bac)[idx].lo;
        x = (u32) func_020b3fc0((u8) lo);
        lo = (u8) (lo | 1);
        y = (u32) func_020b3fc0((u8) lo);
        func_020b2a68((void *) (&m.sub), (const void *) (idx < 0x22 ? &((UnkStruct_020b248c_4 *) data_020d1f24)[idx] : &((UnkStruct_020b248c_4 *) data_020d1f24)[0]));
        if (y > (u32) func_020b2a3c((void *) (&m.sub))) {
            e->hi = 2;
        } else if (func_020b278c((int) a0) && x == 0) {
            e->hi = 3;
        } else {
            e->lo = lo;
            e->hi = 1;
            func_020b278c((int) a0);
        }
        func_020b2a64((void *) (&m.sub));
    } else {
        ((UnkStruct_020b248c *) data_021f4bac)[idx].hi = 0;
        m.a = 0;
        m.b = idx;
        g = (*(UnkStruct_020b248c_3 * *) &data_020ccf94);
        func_02073820((void *) g);
        func_020737f0((void *) g, (void *) (&m), 1);
        func_02073770((void *) g, 0x23, 0);
    }
}

int func_020b2470(unsigned short code)
{
    return ((struct nibble *) data_021f4bac)[func_020b3f58((unsigned short) code)].high;
}

void func_020b23ec(int a, int b)
{
    int idx = func_020b3f58(a);
    void *p = data_020ccf94;

    if (func_02073d90(p) == 0 || func_02073918(p, 0) != 0 || func_02073918(p, 4) != 0) {
        NibbleByte *nf = &((NibbleByte *) data_021f4bac)[idx];
        nf->low = nf->low & ~(1 << b);
    } else {
        unsigned char c = (unsigned char) idx;
        void *obj = data_020ccf94;
        func_02073820(obj);
        func_020737f0(obj, &c, 1);
        func_02073770(obj, 0x24, 0);
    }
}

unsigned char func_020b23e0(void)
{
    return data_021f4b14;
}

void func_020b23d4(void)
{
    data_021f4b14 = 1;
}

void func_020b23c8(void)
{
    char *ptr;
    ptr = ((char *) &data_021f4b14);
    *ptr = 0;
}

int func_020b235c(int idx)
{
    void *p;
    volatile unsigned short id;
    unsigned int ok;
    unsigned int v;

    p = data_020ccf94;
    if (func_02073d90(p) != 0) {
        if (func_02073918(p, 0) == 0) {
            goto ret0;
        }
    }
    id = data_020d1ebc[idx];
    ok = 0;
    v = id;
    if (v >= 0x5000 && v <= 0x5021) {
        ok = 1;
    }
    if (ok != 0) {
        return ((struct nibble *) data_021f4bac)[func_020b3f58(v)].low;
    }
ret0:
    return 0;
}

int func_020b232c(int param)
{
    int r4;
    int r5;
    int result;

    r5 = param;
    r4 = func_020b3fc0((int) func_020b235c(param));
    result = func_020b67e8(r5);
    if (result != 0) {
        if ((int) func_020b23e0() != 0) {
            return r4 + 2;
        }
    }
    return r4;
}
