/* field_actor_support_2: 20 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0200f650 @ 0x0200f650, 0x6c bytes, Thumb
 * func_0200f5e4 @ 0x0200f5e4, 0x6c bytes, Thumb
 * func_0200f554 @ 0x0200f554, 0x90 bytes, Thumb
 * func_0200f530 @ 0x0200f530, 0x22 bytes, Thumb
 * func_0200f434 @ 0x0200f434, 0xfc bytes, Thumb
 * func_0200f3e8 @ 0x0200f3e8, 0x4a bytes, Thumb
 * func_0200f394 @ 0x0200f394, 0x54 bytes, Thumb
 * func_0200f328 @ 0x0200f328, 0x6c bytes, Thumb
 * func_0200f2a0 @ 0x0200f2a0, 0x88 bytes, Thumb
 * func_0200f290 @ 0x0200f290, 0x10 bytes, Thumb
 * func_0200f27c @ 0x0200f27c, 0x14 bytes, Thumb
 * func_0200f268 @ 0x0200f268, 0x14 bytes, Thumb
 * func_0200f234 @ 0x0200f234, 0x34 bytes, Thumb
 * func_0200f1ec @ 0x0200f1ec, 0x48 bytes, Thumb
 * func_0200f1a4 @ 0x0200f1a4, 0x48 bytes, Thumb
 * func_0200f164 @ 0x0200f164, 0x40 bytes, Thumb
 * func_0200f11c @ 0x0200f11c, 0x48 bytes, Thumb
 * func_0200f098 @ 0x0200f098, 0x84 bytes, Thumb
 * func_0200f05c @ 0x0200f05c, 0x3c bytes, Thumb
 * func_0200ef1c @ 0x0200ef1c, 0x140 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_0200f5e4 {
    char pad_00[0x60];
    int unk_60;
    char pad_64[0x800 - 0x64];
    int unk_800;
} UnkStruct_0200f5e4;

typedef struct UnkStruct_0200f5e4_2 {
    char pad_00[4];
    int unk_04;
} UnkStruct_0200f5e4_2;

typedef struct {
    int x, y, z;
} Vec;

typedef struct {
    char pad_00[0x5c];
    Vec unk_5C;
    Vec unk_68;
    char pad_74[0x8e - 0x74];
    short unk_8E;
} UnkStruct_0200f554;

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
} Pair;

typedef struct {
    int x;
    int y;
    int z;
} UnkStruct_0200f434;

typedef struct {
    u8 pad_00[0x5c];
    UnkStruct_0200f434 unk_5C;
    UnkStruct_0200f434 unk_68;
    u8 pad_74[0x8e - 0x74];
    s16 unk_8E;
} UnkStruct_0200f434_2;

typedef struct {
    char pad_00[0x5c];
    int unk_5C;
    char pad_60[4];
    int unk_64;
    char pad_68[0x26];
    short unk_8E;
} UnkStruct_0200f3e8;

typedef struct {
    char pad_00[0x5c];
    int unk_5C;
    char pad_60[0x4];
    int unk_64;
    char pad_68[0x26];
    short unk_8E;
    char pad_90[0x770];
    int unk_800;
} Self0300f394;

struct DamageFlags {
    char pad_00[0xb0];
    unsigned int flags;
    char pad_B4[0x788];
    char data1[0x44];
    char data2[0x44];
};

typedef struct UnkStruct_0200ef1c {
    int x, y, z;
} UnkStruct_0200ef1c;

typedef struct UnkStruct_0200ef1c_2 {
    u8 pad_00[0x5c];
    UnkStruct_0200ef1c v;
    u8 pad_68[0x182 - 0x68];
    u8 unk_182;
    u8 unk_183;
    u8 pad_184[0x1b0 - 0x184];
    u8 unk_1B0;
    u8 pad_1B1[0x800 - 0x1b1];
    int unk_800;
} UnkStruct_0200ef1c_2;

extern void func_0200f6bc(int *dst, int src, int *args);
extern int func_020e8bb0(void *dst, int src, int size, int flags, int control);
extern int func_02073908(int, int);
extern int func_0200e9a8(UnkStruct_0200f5e4 *, unsigned char *, UnkStruct_0200f5e4_2 *, char *, int);
extern int func_020b65c4(void);
extern int func_020ea990(Vec *a, Vec *b);
extern void func_0200fb7c(UnkStruct_0200f554 *o, int x, int z, short b);
extern void func_0204f794(void *dst, unsigned int a, unsigned int b);
extern s16 FX_SinCosTable_[];
extern int func_020e8ed8(int dx, int dz);
extern int func_020e8b4c(int a, int b);
extern int FX_MulFunc(int a, int b);
extern unsigned int func_02064558(int x);
extern int func_020044c0(char *dest, int code, unsigned int size, int param);
extern int func_020044b0(void *dest, void *src, int len, int flag);
extern int func_0208ffac(void);
extern int func_0208ff98(void);
extern int func_0203f7d0(void *, void *);
extern void *data_020ccf94;
extern int func_02073d90(void *);
extern void func_02096484(void *, int, int);
extern void func_02073820(void *);
extern void func_020737f0(void *, void *, int);
extern void func_02073770(void *, int, int);
extern int func_02011404(void *ptr, int a, int b, int c, int d);
extern unsigned char data_020c7a20[];
extern int data_020d7300;
extern int func_020960f8(int a, int b);
extern int func_02096614(short *pair, UnkStruct_0200ef1c *pos, int *z, int m, int e);
extern UnkStruct_0200ef1c *func_02095794(int a);
extern void func_0200fa1c(UnkStruct_0200ef1c *out, UnkStruct_0200ef1c_2 *s, UnkStruct_0200ef1c *cur, short *ang, void *tbl);
extern void func_02010d64(UnkStruct_0200ef1c_2 *s);

int func_0200f434(UnkStruct_0200f434_2 *a, UnkStruct_0200f434 *b);
int func_0200f290(unsigned int *ptr, int bit);

void func_0200f650(int a0, int a1)
{
    int buf[3];
    func_0200f6bc(buf, a0, &a1);
    func_020e8bb0((char *) a0 + 0x824, buf[0], 0x800, 0x2000, 0x333);
    func_020e8bb0((char *) a0 + 0x828, buf[1], 0x800, 0x2000, 0x333);
    func_020e8bb0((char *) a0 + 0x82c, buf[2], 0x800, 0x2000, 0x333);
}

int func_0200f5e4(UnkStruct_0200f5e4 *param1, UnkStruct_0200f5e4_2 *param2, int param3)
{
    unsigned char local;

    if (func_02073908((*(int *) &data_020ccf94), param1->unk_800)) {
        return 0;
    }
    if (func_0200f290((unsigned int *) param1, 0x10)) {
        return 0;
    }
    param2->unk_04 = param1->unk_60;
    if (func_0200e9a8(param1, &local, param2, (char *) param2 + 8, param3) == 0) {
        return 0;
    }
    if (local == func_020b65c4()) {
        return 1;
    } else {
        return 0;
    }
}

int func_0200f554(UnkStruct_0200f554 *o)
{
    short b;
    Vec a;
    Vec *p;
    Vec *q;

    if (func_0200f5e4((UnkStruct_0200f5e4 *) o, (UnkStruct_0200f5e4_2 *) (&a), (int) (&b))) {
        p = &o->unk_5C;
        if (p->x == a.x && p->z == a.z && b == o->unk_8E) {
            return 1;
        }
        if (func_020ea990(p, &a) >= 0xe000) {
            q = &o->unk_68;
            q->x = a.x;
            q->y = a.y;
            q->z = a.z;
            p->x = q->x;
            p->y = q->y;
            p->z = q->z;
            o->unk_8E = b;
            return 0;
        } else {
            func_0200fb7c(o, a.x, a.z, b);
            return 0;
        }
    } else {
        return 1;
    }
}

int func_0200f530(void *arg1, Pair *arg2)
{
    unsigned int buffer[4];
    func_0204f794(buffer, arg2->unk_00, arg2->unk_04);
    return func_0200f434((UnkStruct_0200f434_2 *) arg1, (UnkStruct_0200f434 *) buffer);
}

int func_0200f434(UnkStruct_0200f434_2 *a, UnkStruct_0200f434 *b)
{
    UnkStruct_0200f434 *q;
    UnkStruct_0200f434 *w;
    s16 ang;
    UnkStruct_0200f434 t;

    q = &a->unk_5C;
    if (func_0200f5e4((UnkStruct_0200f5e4 *) a, (UnkStruct_0200f5e4_2 *) (&t), (int) (&ang)) != 0) {
        if (func_020ea990((Vec *) (&t), (Vec *) b) >= 0x4000) {
            ang = func_020e8ed8(b->x - q->x, b->z - q->z);
            t.x = b->x - FX_MulFunc(0x2000, FX_SinCosTable_[((u16) ang >> 4) * 2]);
            t.z = b->z - FX_MulFunc(0x2000, FX_SinCosTable_[((u16) ang >> 4) * 2 + 1]);
        } else {
            ang = a->unk_8E;
        }
    } else {
        return 1;
    }
    if (func_020ea990((Vec *) q, (Vec *) (&t)) <= 0x200) {
        if (func_020e8b4c(a->unk_8E, ang) < 0x100) {
            return 1;
        }
    }
    if (func_020ea990((Vec *) q, (Vec *) (&t)) >= 0xe000) {
        w = &a->unk_68;
        a->unk_68.x = t.x;
        w->y = t.y;
        w->z = t.z;
        q->x = a->unk_68.x;
        q->y = w->y;
        q->z = w->z;
        a->unk_8E = ang;
        return 1;
    } else {
        return 0;
    }
}

void func_0200f3e8(UnkStruct_0200f3e8 *self)
{
    unsigned int v = func_02064558(self->unk_8E);
    switch (v) {
        case 2:
            self->unk_64--;
            break;
        case 0:
            self->unk_64++;
            break;
        case 3:
            self->unk_5C--;
            break;
        case 1:
            self->unk_5C++;
            break;
    }
}

void func_0200f394(Self0300f394 *self)
{
    int dir;
    int delta;

    dir = (int) func_02064558(self->unk_8E);
    delta = self->unk_800;

    switch (dir) {
        case 2:
            self->unk_64 -= delta;
            break;
        case 0:
            self->unk_64 += delta;
            break;
        case 3:
            self->unk_5C -= delta;
            break;
        case 1:
            self->unk_5C += delta;
            break;
    }
}

int func_0200f328(struct DamageFlags *self, int param)
{
    int flag4 = (self->flags & 4) ? 1 : 0;
    if (flag4 != 0) {
        int flag2 = (self->flags & 2) ? 1 : 0;
        if (flag2 != 0) {
            return flag2;
        }
    }
    if (func_0200f290((unsigned int *) self, 0x19) != 0) {
        return func_020044c0(self->data1, param, 0x7f, 0);
    } else {
        return func_020044c0(self->data2, param, 0x7f, 0);
    }
}

void func_0200f2a0(void *self, void *param2, void *param3)
{
    int flags;
    int f4;
    int f2;

    flags = *(int *) ((char *) self + 0xb0);
    f4 = (flags & 4) ? 1 : 0;
    if (f4 != 0) {
        f2 = (flags & 2) ? 1 : 0;
        if (f2 != 0) {
            return;
        }
    }
    if (func_0200f290((unsigned int *) self, 25) != 0) {
        func_020044b0((char *) self + 0x83c, param2, 0x7f, 0);
    } else {
        func_020044b0((char *) self + 0x880, param2, 0x7f, 0);
    }
    *(int *) ((char *) self + 0x8c4) = ((int *) param3)[0];
    *(int *) ((char *) self + 0x8c8) = ((int *) param3)[1];
    *(int *) ((char *) self + 0x8cc) = ((int *) param3)[2];
}

int func_0200f290(unsigned int *ptr, int bit)
{
    unsigned int value = ptr[0x1BB];
    return (value & (1 << bit));
}

unsigned int *func_0200f27c(unsigned int *param0, int param1)
{
    unsigned int *r0;
    unsigned int r3;
    unsigned int r2;

    r0 = param0 + 0x1BB;
    r3 = *r0;
    r2 = 1;
    r2 = r2 << param1;
    r3 = r3 | r2;
    *r0 = r3;
    return r0;
}

void func_0200f268(char *base, int bit)
{
    *(unsigned int *) (base + 0x6ec) &= ~(1 << bit);
}

void func_0200f234(int *arg0)
{
    int *r4;
    int r0;
    int r1;

    r4 = arg0;
    if (func_0208ffac() != 0) {
        r1 = 1;
        r0 = 0x170;
        *(int *) ((char *) r4 + r0) = r1;
    } else if (func_0208ff98() != 0) {
        r1 = 2;
        r0 = 0x170;
        *(int *) ((char *) r4 + r0) = r1;
    } else {
        r1 = 0;
        r0 = 0x170;
        *(int *) ((char *) r4 + r0) = r1;
    }
    return;
}

int func_0200f1ec(void *r0, void *r1)
{
    if (*(int *) ((char *) r0 + 0x6bc) == 0 && *(int *) ((char *) r0 + 0x6c0) == 0 && *(int *) ((char *) r0 + 0x6c4) == 0) {
        return 0;
    }
    *(int *) r1 = *(int *) ((char *) r0 + 0x6bc);
    *(int *) ((char *) r1 + 4) = *(int *) ((char *) r0 + 0x6c0);
    *(int *) ((char *) r1 + 8) = *(int *) ((char *) r0 + 0x6c4);
    func_0203f7d0(r1, r1);
    return 1;
}

void func_0200f1a4(int unused, int a, int b)
{
    int local;
    void *obj;

    if (func_02073d90(data_020ccf94)) {
        func_02096484(&local, b, a);
        obj = data_020ccf94;
        func_02073820(obj);
        func_020737f0(obj, &local, 3);
        func_02073770(obj, 0x2b, 4);
    }
}

void func_0200f164(void *receiver)
{
    if (func_02073d90(data_020ccf94) != 0) {
        char flag = 0;
        void *p = data_020ccf94;
        func_02073820(p);
        func_020737f0(p, (void *) (&flag), 1);
        func_02073770(p, 0x2d, 4);
    }
}

void func_0200f11c(unsigned int param1)
{
    extern int func_020112bc(unsigned int);
    unsigned char local;
    unsigned int r4;

    if (func_02073d90((void *) (*(unsigned int *) ((unsigned int *) &data_020ccf94))) != 0) {
        local = (unsigned char) func_020112bc(param1);
        r4 = *(unsigned int *) ((unsigned int *) &data_020ccf94);
        func_02073820((void *) r4);
        func_020737f0((void *) r4, (void *) (&local), 1);
        func_02073770((void *) r4, 0x2e, 4);
    }
}

void func_0200f098(void *self)
{
    if (func_0200f290((unsigned int *) self, 0x15)) {
        func_02011404((char *) self + 0x45c, *(short *) ((char *) self + 0x460), 0x400, 0x1770000, 0xC0000);
        func_02011404((char *) self + 0x45e, *(short *) ((char *) self + 0x462), 0x400, 0x1770000, 0xC0000);
        if (*(short *) ((char *) self + 0x460) == 0 && *(short *) ((char *) self + 0x462) == 0 &&
            *(short *) ((char *) self + 0x45c) == 0 && *(short *) ((char *) self + 0x45e) == 0) {
            func_0200f268((char *) self, 0x15);
        }
    }
}

int func_0200f05c(unsigned char *r0, int r1)
{
    if (r1 == 0x1e) {
        if (r0[0x7d5] == 0) {
            if (*(unsigned int *) (r0 + 0xc7c) == 0) {
                return 1;
            }
        }
    } else if (r1 == 0x4f) {
        if (*(unsigned int *) (r0 + 0xc7c) == 0) {
            return 1;
        }
    }
    return data_020c7a20[r1];
}

void func_0200ef1c(UnkStruct_0200ef1c_2 *self)
{
    struct {
        short pair[2];
        UnkStruct_0200ef1c old;
    } s;
    UnkStruct_0200ef1c pos;
    UnkStruct_0200ef1c cur;
    UnkStruct_0200ef1c nv;
    UnkStruct_0200ef1c *p;
    UnkStruct_0200ef1c *q;
    UnkStruct_0200ef1c *tgt;
    int h;
    int d1;
    int d2;

    p = &self->v;
    s.old.x = p->x;
    s.old.y = p->y;
    s.old.z = p->z;
    if (self->unk_1B0 == 0) {
        goto end;
    }
    if (self->unk_182 != 0x15) {
        goto end;
    }
    h = self->unk_183;
    if (func_02073908((int) data_020ccf94, h) == 0) {
        goto end;
    }
    if (func_020960f8(2, 4) == 0) {
        goto end;
    }
    if (func_02096614(s.pair, &pos, &pos.z, -1, self->unk_800) == 0) {
        goto end;
    }
    tgt = func_02095794(h);
    q = &self->v;
    cur.x = q->x;
    cur.y = q->y;
    cur.z = q->z;
    d1 = func_020e8ed8(tgt->x - cur.x, tgt->z - cur.z);
    s.pair[1] = (short) func_020e8ed8(pos.x - cur.x, pos.z - cur.z);
    if (func_020e8b4c(d1, s.pair[1]) >= 0x400) {
        goto end;
    }
    d2 = func_020ea990((Vec *) (&cur), (Vec *) tgt);
    if (d2 > func_020ea990((Vec *) (&cur), (Vec *) (&pos))) {
        goto end;
    }
    if (self->unk_800 >= h) {
        s.pair[1] = (short) (s.pair[1] + 0x4000);
    } else {
        s.pair[1] = (short) (s.pair[1] - 0x4000);
    }
    func_0200fa1c(&nv, self, &cur, &s.pair[1], &data_020d7300);
    p = &self->v;
    p->x = nv.x;
    p->y = nv.y;
    p->z = nv.z;
end:
    func_02010d64(self);
    p = &self->v;
    p->x = s.old.x;
    p->y = s.old.y;
    p->z = s.old.z;
}
