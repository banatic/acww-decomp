/* field_actor_states_25: 14 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0200cc00 @ 0x0200cc00, 0x40 bytes, Thumb
 * func_0200cbfc @ 0x0200cbfc, 0x4 bytes, Thumb
 * func_0200cac0 @ 0x0200cac0, 0x13c bytes, Thumb
 * func_0200cabc @ 0x0200cabc, 0x2 bytes, Thumb
 * func_0200cab0 @ 0x0200cab0, 0xa bytes, Thumb
 * func_0200ca60 @ 0x0200ca60, 0x50 bytes, Thumb
 * func_0200ca18 @ 0x0200ca18, 0x48 bytes, Thumb
 * func_0200c9ec @ 0x0200c9ec, 0x2c bytes, Thumb
 * func_0200c9e8 @ 0x0200c9e8, 0x4 bytes, Thumb
 * func_0200c9a8 @ 0x0200c9a8, 0x40 bytes, Thumb
 * func_0200c98c @ 0x0200c98c, 0x1a bytes, Thumb
 * func_0200c978 @ 0x0200c978, 0x14 bytes, Thumb
 * func_0200c954 @ 0x0200c954, 0x24 bytes, Thumb
 * func_0200c94c @ 0x0200c94c, 0x8 bytes, Thumb
 */

#include "types.h"

struct Vec3 {
    int x;
    int y;
    int z;
};

struct UnkStruct_0200cac0 {
    u8 pad_00[0x8e];
    s16 unk_8E;
    u8 pad_90[0x6c8 - 0x90];
    int unk_6C8;
    int unk_6CC;
    int unk_6D0;
    u8 pad_6D4[0x7d4 - 0x6d4];
    s16 unk_7D4;
    s16 unk_7D6;
};

typedef struct {
    unsigned char pad_00[0x8e];
    short unk_8E;
    short pad_90[2];
    short unk_94;
} UnkStruct_0200cab0;

struct UnkStruct_0200ca18 {
    char pad_00[0x8e];
    short unk_8E;
    char pad_90[8];
    int unk_98;
    char pad_9C[0x738];
    short unk_7D4;
    char pad_7D6[0x1a];
    int unk_7F0;
    char pad_7F4[8];
    int unk_7FC;
};

struct UnkStruct_0200c98c {
    char pad_00[0xC];
    unsigned short unk_0C;
};

typedef struct {
    short unk_00;
    short pad_02;
    int unk_04;
    int unk_08;
} UnkStruct_0200c94c;

extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern void func_0200cc40(void *, int);
extern int func_0200e894(void *, void *);
extern int func_0200e91c(void *);
extern void func_020109fc(struct UnkStruct_0200cac0 *self, int a, int b, int c);
extern int FX_MulFunc(int a, int b);
extern int func_020912d4(int a, struct Vec3 *pos, s16 *ang, int d);
extern int func_0200f328(struct UnkStruct_0200cac0 *self, int code);
extern s16 FX_SinCosTable_[];
extern int func_020113e0(void *a, short b);
extern int func_0201138c(void *a, int b);
extern void func_0201107c(void *self, int *r);
extern int func_02008258(struct UnkStruct_0200ca18 *self, int arg);
extern int func_0200d4e8(struct UnkStruct_0200ca18 *self, int a, int b, int c);
extern void func_02010f5c(void *);
extern int func_0201100c(void *);
extern void func_02010d64(void *);
extern int func_02010ca4(void *);
extern void func_0200eebc(void *arg0);
extern int func_0200f554(int param);

int func_0200cc00(void *a, int b, int c, int d)
{
    char s1[12];
    char s2[16];
    int result;

    func_0200e92c(s1);
    func_0200e90c(s1, 4, c, d);
    func_0200cc40(s2, b);
    result = func_0200e894(a, s1);
    func_0200e91c(s1);
    return result;
}

void func_0200cbfc(unsigned short *p0, int p1)
{
    p0[0] = p1;
}

void func_0200cac0(struct UnkStruct_0200cac0 *self, void *arg, int previous)
{
    s16 ang;
    struct Vec3 v;
    void *base;
    s16 self_ang;
    int shifted_self;
    int shifted_ang;
    int diff;
    int abs_diff;
    int t;
    int sv;
    int cv;

    ang = *(s16 *) ((char *) arg + 0xc);
    base = (char *) self + 0x7d4;
    func_020109fc(self, 4, 3, 0);
    func_0200cbfc((unsigned short *) base, ang);

    self_ang = self->unk_8E;
    shifted_self = self_ang << 12;
    shifted_ang = ang << 12;
    diff = shifted_ang - shifted_self;
    if (diff < 0) {
        abs_diff = -diff;
    } else {
        abs_diff = diff;
    }

    if (shifted_ang >= shifted_self) {
        if (abs_diff > 0x08000000) {
            ang += 0x6fd0;
        } else {
            ang += 0x9030;
        }
    } else {
        if (abs_diff > 0x08000000) {
            ang += 0x9030;
        } else {
            ang += 0x6fd0;
        }
    }

    v.x = self->unk_6C8;
    v.y = self->unk_6CC;
    v.z = self->unk_6D0;

    sv = FX_SinCosTable_[((u16) ang >> 4) * 2];
    cv = FX_SinCosTable_[((u16) ang >> 4) * 2 + 1];

    t = FX_MulFunc(cv, 0x666);
    t -= FX_MulFunc(sv, 0x666);
    sv = FX_MulFunc(sv, 0x666);
    cv = FX_MulFunc(cv, 0x666);
    sv += cv;
    v.x += sv;
    v.z += t;

    *(s16 *) ((char *) base + 2) = ang + 0x8000;
    *(s16 *) ((char *) base + 2) = *(s16 *) ((char *) base + 2) - 0x38e;

    func_020912d4(1, &v, &ang, 0);
    func_0200f328(self, 0x53);
}

void func_0200cabc(void *object, int event) {}

void func_0200cab0(UnkStruct_0200cab0 *p)
{
    p->unk_94 = p->unk_8E;
}

void func_0200ca60(void *self)
{
    char *base714;
    int ret;

    base714 = (char *) self + 0x7d4;
    func_020113e0((char *) self + 0x8e, *(short *) ((char *) self + 0x7d4));
    {
        void *p = *(void **) ((char *) self + 0x98);
        ret = func_0201138c(p, 0);
        func_0201107c(self, &ret);
        if (ret != 0) {
            return;
        }
        if (p == 0) {
            return;
        }
        func_020912d4(0x29, (struct Vec3 *) ((char *) self + 0x5c), (s16 *) (base714 + 2), 0);
    }
}

void func_0200ca18(struct UnkStruct_0200ca18 *self)
{
    int c = self->unk_98;
    if (self->unk_8E != self->unk_7D4) {
        return;
    }
    if (c > 0) {
        return;
    }
    self->unk_7FC = func_02008258(self, self->unk_7F0);
    func_0200d4e8(self, 3, 1, -1);
}

void func_0200c9ec(void *param)
{
    func_0200ca60(param);
    func_02010f5c(param);
    func_0201100c(param);
    func_02010d64(param);
    func_02010ca4(param);
    func_0200ca18((struct UnkStruct_0200ca18 *) param);
}

void func_0200c9e8(unsigned short *p0, int p1)
{
    p0[0] = p1;
}

int func_0200c9a8(void *p0, void *p1, void *p2, void *p3)
{
    char local[0x1c];
    int result;

    func_0200e92c(local);
    func_0200e90c(local, 5, (int) p2, (int) p3);
    func_0200c9e8((unsigned short *) (local + 0xc), (int) p1);
    result = func_0200e894(p0, local);
    func_0200e91c(local);
    return result;
}

void func_0200c98c(void *arg0, struct UnkStruct_0200c98c *arg1, int previous)
{
    unsigned short x = arg1->unk_0C;
    func_020109fc((struct UnkStruct_0200cac0 *) arg0, 18, (unsigned short) x, (unsigned short) x);
    func_0200eebc(arg0);
}

void func_0200c978(int a, int b)
{
    func_0200c9a8((void *) a, (void *) 3, (void *) 5, (void *) b);
}

void func_0200c954(int param)
{
    func_02010f5c((void *) param);
    if (func_0200f554(param) != 0) {
        func_0201100c((void *) param);
    }
    func_02010d64((void *) param);
}

void func_0200c94c(UnkStruct_0200c94c *p, int a, int b, int c)
{
    p->unk_00 = (short) a;
    p->unk_04 = b;
    p->unk_08 = c;
}
