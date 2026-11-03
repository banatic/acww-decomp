/* mabel_talk: 12 functions, module ov049
 * mwccarm 1.2/base -O4,s
 * func_ov049_022610c4 @ 0x022610c4, 0x6 bytes, Thumb
 * func_ov049_02261080 @ 0x02261080, 0x44 bytes, Thumb
 * func_ov049_02261060 @ 0x02261060, 0x20 bytes, Thumb
 * func_ov049_02260fe4 @ 0x02260fe4, 0x7c bytes, Thumb
 * func_ov049_02260ec8 @ 0x02260ec8, 0x11c bytes, Thumb
 * func_ov049_02260dac @ 0x02260dac, 0x11c bytes, Thumb
 * func_ov049_02260cf8 @ 0x02260cf8, 0xb4 bytes, Thumb
 * func_ov049_02260c94 @ 0x02260c94, 0x64 bytes, Thumb
 * func_ov049_02260c60 @ 0x02260c60, 0x34 bytes, Thumb
 * func_ov049_02260b9c @ 0x02260b9c, 0xc4 bytes, Thumb
 * func_ov049_02260b20 @ 0x02260b20, 0x7c bytes, Thumb
 * func_ov049_02260ac4 @ 0x02260ac4, 0x5c bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[184];
    unsigned long unk_B8;
} UnkStruct_022610c4;

struct UnkStruct_02261080 {
    char pad_00[0x40];
    int unk_40;
};

struct UnkStruct_02261060 {
    char pad_00[0x40];
    void *unk_40;
};

typedef struct {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0x6c];
    unsigned char *unk_B0;
} UnkStruct_02260fe4;

struct UnkStruct_02260ec8 {
    u8 pad_00[0x976];
    u8 unk_976;
};

struct UnkStruct_02260ec8_2 {
    u8 pad_00[0x40];
    u32 unk_40;
    u8 pad_44[0x6c];
    struct UnkStruct_02260ec8 *unk_B0;
};

typedef struct UnkStruct_02260dac {
    char pad_00[0x976];
    u8 unk_976;
} UnkStruct_02260dac;

typedef struct UnkStruct_02260dac_2 {
    char pad_00[0x40];
    void *unk_40;
    char pad_44[0xb0 - 0x44];
    UnkStruct_02260dac *unk_B0;
} UnkStruct_02260dac_2;

typedef struct Msg {
    u8 b[2];
    u16 unk_02;
    u16 unk_04;
} Msg;

typedef struct UnkStruct_02260cf8 {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xbc - 0x44];
    int unk_BC;
    int unk_C0;
} UnkStruct_02260cf8;

typedef struct Msg_02260cf8 {
    u8 b;
    u8 pad_01;
    u16 h;
} Msg_02260cf8;

typedef struct {
    char pad_00[0x728];
    int a;
    int b;
} UnkStruct_02260c94;

typedef struct {
    char pad_00[0x40];
    void *p;
    char pad_44[0x6c];
    UnkStruct_02260c94 *sub;
} UnkStruct_02260c94_2;

struct UnkStruct_02260b9c {
    unsigned char op;
    unsigned short key;
    unsigned short val;
};

struct UnkStruct_02260b9c_2 {
    unsigned char pad_00[0x40];
    void *unk_40;
};

typedef struct {
    char pad_00[0x40];
    int unk_40;
} UnkStruct_02260b20;

typedef struct {
    const unsigned char *data;
    unsigned char count;
} List;

typedef struct {
    unsigned char pad_00[0x728];
    unsigned int unk_728;
    unsigned int unk_72C;
    unsigned char pad1[0x244];
    unsigned char unk_974;
} PtrStruct;

typedef struct {
    unsigned char pad_00[0xb0];
    PtrStruct *unk_B0;
    unsigned char pad1[0x8];
    void *unk_BC;
} UnkStruct_02260ac4;

extern int func_0206fc6c(void);
extern void func_0206844c(int a, char *b, int c);
extern int data_ov049_02263298;
extern int func_020984e8(void);
extern int func_0206fc8c(void);
extern int func_020996b8(int);
extern int func_02072ba4(int);
extern int func_02072b64(int, int);
extern int func_02071d8c(int, int, int, int, int);
extern u16 *func_02099710(void *);
extern u16 *func_020996f8(void *);
extern int func_02095b58(void *);
extern int func_02095b40(void *);
extern int func_02071aa8(int, unsigned int, int, int, int);
extern u8 data_021f43ec;
extern u16 *func_0206faf0(void);
extern int func_0204c878(u16 *p);
extern void func_02015fb0(UnkStruct_02260cf8 *self, int a, int b, int c, int d, int e);
extern int func_ov004_0222c2bc(void);
extern int func_ov004_0223b39c(int a, int b);
extern void *func_020960f8(int size, int align);
extern void func_02068434(void *p);
extern int func_ov004_0223b340(int, int);
extern int func_02099640(int argument0);
extern int func_0209a850(int argument0);
extern int func_0202e9fc(void);
extern int func_0209a034(int);
extern void func_0209a050(int);
extern int func_0204bcdc(unsigned short *);
extern int func_0204bc64(unsigned short *);
extern int func_02015330(void *, unsigned short *, int, int, int);
extern void *func_0209b0f0(void *record);
extern void func_0209bb90(void *, int);
extern int func_0206837c(int);
extern void func_020ab670(int, int, int);
extern void func_020ab628(int, int, char *, int, char *, unsigned int, int);
extern void func_020ab5f8(int);
extern void func_02068388(int, int);
extern void func_0201b420(PtrStruct *a, void *b);
extern int func_0209a000(char *dst, int val);
extern void func_020ad8f8(unsigned int a, unsigned int b, int c);
extern void func_0207972c(void);

void func_ov049_022610c4(UnkStruct_022610c4 *p, unsigned long v)
{
    p->unk_B8 = v;
}

void func_ov049_02261080(struct UnkStruct_02261080 *param)
{
    char local[8];
    if (func_0206fc6c()) {
        local[0] = 16;
        func_0206844c(param->unk_40, &local[0], data_ov049_02263298);
    } else {
        local[1] = 15;
        func_0206844c(param->unk_40, &local[1], data_ov049_02263298);
    }
}

void func_ov049_02261060(struct UnkStruct_02261060 *self)
{
    char c = 0x12;
    func_0206844c((int) self->unk_40, (char *) (&c), (int) ((*(void * *) &data_ov049_02263298)));
}

void func_ov049_02260fe4(UnkStruct_02260fe4 *self)
{
    char buf[2];
    if (func_0206fc6c()) {
        int a = func_020984e8();
        int b = func_0206fc8c();
        int c = func_02072b64(func_02072ba4(func_020996b8(a)), b);
        unsigned char d = self->unk_B0[0x976];
        func_02071d8c(9, c, 4, d, 1);
        buf[0] = 0x24;
        func_0206844c(self->unk_40, buf, data_ov049_02263298);
    } else {
        buf[1] = 0x22;
        func_0206844c(self->unk_40, &buf[1], data_ov049_02263298);
    }
}

inline u16 inline_fn(u16 *arg0)
{
    return *arg0;
}

void func_ov049_02260ec8(struct UnkStruct_02260ec8_2 *self)
{
    u32 idx;
    u16 r5;
    u16 r4;
    u32 v1;
    u32 v2;
    char buf[8];
    unsigned int flag;
    void *p;
    if (func_0206fc6c()) {
        p = (void *) func_020984e8();
        idx = (u32) func_0206fc8c();
        idx = (u32) func_02072b64(func_02072ba4(func_020996b8((int) p)), idx);
        func_02071d8c(4, (u8) self->unk_B0->unk_976, 9, idx, 1);
        if (idx < 8) {
            r5 = (u16) (idx + 0x12a8);
        } else {
            r5 = 0x12a8;
        }
        if (idx < 8) {
            r4 = (u16) (idx + 0x1429);
        } else {
            r4 = 0x1429;
        }
        v1 = *func_02099710(p);
        v2 = *func_020996f8(p);
        if (r5 == v1) {
            u16 cur = inline_fn(func_02099710(p));
            flag = 0;
            if ((((unsigned int) cur) >= 0x12a8) && (((unsigned int) cur) <= 0x12af)) {
                flag = 1;
            }
            if (flag != 0) {
                *((u16 *) (buf + 2)) = r5;
                func_02095b58(buf + 2);
            }
        }
        if (r4 == v2) {
            u16 cur = inline_fn(func_020996f8(p));
            flag = 0;
            if ((((unsigned int) cur) >= 0x1429) && (((unsigned int) cur) <= 0x1430)) {
                flag = 1;
            }
            if (flag != 0) {
                *((u16 *) (buf + 4)) = r4;
                func_02095b40(buf + 4);
            }
        }
        buf[0] = 0x27;
        func_0206844c(self->unk_40, (char *) buf, (int) ((*(void * *) &data_ov049_02263298)));
    } else {
        buf[1] = 0x22;
        func_0206844c(self->unk_40, (char *) (buf + 1), (int) ((*(void * *) &data_ov049_02263298)));
    }
}

void func_ov049_02260dac(UnkStruct_02260dac_2 *this)
{
    Msg m;
    void *a;
    unsigned int t;
    u16 x, y;
    int p, q;

    if (func_0206fc6c() != 0) {
        a = (void *) func_020984e8();
        t = (unsigned int) func_0206fc8c();
        t = (unsigned int) func_02072b64(func_02072ba4((int) (void *) func_020996b8((int) a)), t);
        func_02071aa8(9, t, 4, this->unk_B0->unk_976, 1);
        if (t < 8) {
            x = (u16) (t + 0x12a8);
        } else {
            x = 0x12a8;
        }
        if (t < 8) {
            y = (u16) (t + 0x1429);
        } else {
            y = 0x1429;
        }
        p = *func_02099710(a);
        q = *func_020996f8(a);
        if (x == p) {
            u16 *ptr = func_02099710(a);
            int ok = 0;
            u16 v = *ptr;
            if (v >= 0x12a8 && v <= 0x12af) {
                ok = 1;
            }
            if (ok != 0) {
                m.unk_02 = x;
                func_02095b58((void *) (&m.unk_02));
            }
        }
        if (y == q) {
            u16 *ptr = func_020996f8(a);
            int ok = 0;
            u16 v = *ptr;
            if (v >= 0x1429 && v <= 0x1430) {
                ok = 1;
            }
            if (ok != 0) {
                m.unk_04 = y;
                func_02095b40((void *) (&m.unk_04));
            }
        }
        m.b[0] = 0x21;
        func_0206844c((int) this->unk_40, (char *) (&m.b[0]), data_ov049_02263298);
    } else {
        m.b[1] = 0x22;
        func_0206844c((int) this->unk_40, (char *) (&m.b[1]), data_ov049_02263298);
    }
}

void func_ov049_02260cf8(UnkStruct_02260cf8 *self)
{
    Msg_02260cf8 m;
    int h;
    u16 *p;
    int i;

    self->unk_BC = 0;
    self->unk_C0 = 0;
    h = self->unk_40;
    m.b = data_021f43ec;
    if (func_0206fc6c() != 0) {
        p = func_0206faf0();
        m.h = 0xfff1;
        for (i = 0; i < 15; i++) {
            if (p[i] == 0xfff1) {
                break;
            }
            m.h = p[i];
            self->unk_BC = self->unk_BC + func_0204c878(&m.h) / 4;
        }
        if (self->unk_BC == 0) {
            m.b = 0x17;
        } else {
            func_02015fb0(self, self->unk_BC, 1, 0xa, 0, 0);
            m.b = 0x1b;
        }
    } else {
        m.b = 0x15;
    }
    func_0206844c(h, (char *) (&m.b), data_ov049_02263298);
}

void func_ov049_02260c94(UnkStruct_02260c94_2 *arg)
{
    char c;
    if (func_ov004_0222c2bc() != 0) {
        UnkStruct_02260c94 *sub = arg->sub;
        func_ov004_0223b39c(sub->a, sub->b);
    }
    if (func_020960f8(16, 4) != 0) {
        void *p = arg->p;
        func_02068434(p);
        c = '-';
        func_0206844c((int) p, &c, (int) ((*(void * *) &data_ov049_02263298)));
        func_ov049_022610c4((UnkStruct_022610c4 *) arg, 0);
    }
}

void func_ov049_02260c60(int param)
{
    int *ptr;
    int a, b;

    if (func_ov004_0222c2bc() != 0) {
        ptr = *(int **) (param + 0xb0);
        a = *(int *) ((char *) ptr + 0x728);
        b = *(int *) ((char *) ptr + 0x72c);
        func_ov004_0223b340(a, b);
        func_ov049_022610c4((UnkStruct_022610c4 *) param, 0);
    }
}

void func_ov049_02260b9c(struct UnkStruct_02260b9c_2 *ctx)
{
    unsigned int status;
    int something;
    int r5;
    unsigned int eq;
    struct UnkStruct_02260b9c local;
    void *r6 = ctx->unk_40;
    void *r7 = (*(void * *) &data_ov049_02263298);
    status = 0x30;
    if (func_0206fc6c() == 0) {
        goto end;
    }

    something = func_0209a850((int) func_02099640(func_020984e8()));

    if (func_0202e9fc() == 0) {
        goto end;
    }

    r5 = func_0206fc8c();
    local.key = func_0209a034(r5);

    if (r5 >= 0) {
        func_0209a050(r5);
    }

    if (func_0204bcdc(&local.key)) {
        local.val = 0xfff1;
        eq = (func_0204bc64(&local.key) == func_0204bc64(&local.val));
    } else {
        eq = (local.key == 0xfff1);
    }

    if (eq != 0) {
        goto end;
    }

    func_02015330(ctx, &local.key, 2, 5, 0);
    status = 0x2f;
    {
        void *retainedAddress;
        retainedAddress = func_0209b0f0((void *) something);
        func_0209bb90(retainedAddress, 1);
    }

end:
    local.op = (unsigned char) status;
    func_0206844c((int) r6, (char *) (&local), (int) r7);
}

void func_ov049_02260b20(UnkStruct_02260b20 *obj, List *list, int c)
{
    int v = obj->unk_40;
    int handle;
    int zero = 0;
    const unsigned char *data;
    unsigned char count;
    int i;
    char buf[2];

    handle = func_0206837c(v);
    data = list->data;
    count = list->count;
    if (c != -1) {
        func_020ab670(handle, count, c);
    } else {
        func_020ab670(handle, count, -1);
    }
    for (i = 0; i < count; i++) {
        buf[0] = data[i];
        buf[1] = 6;
        func_020ab628(handle, i, buf, zero, &buf[1], (*(unsigned int *) &data_ov049_02263298), zero);
    }
    func_020ab5f8(handle);
    func_02068388(v, 1);
}

void func_ov049_02260ac4(UnkStruct_02260ac4 *self)
{
    self->unk_B0->unk_974 = 1;
    func_0201b420(self->unk_B0, self->unk_BC);
    func_0209a000((char *) self->unk_B0 + 0x738, 0);
    func_020ad8f8(self->unk_B0->unk_728, self->unk_B0->unk_72C, 0xa);
    func_0207972c();
}
