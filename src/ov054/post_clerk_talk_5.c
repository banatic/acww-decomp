/* post_clerk_talk_5: 15 functions, module ov054
 * mwccarm 1.2/base -O4,s
 * func_ov054_02261af8 @ 0x02261af8, 0xbc bytes, Thumb
 * func_ov054_02261a94 @ 0x02261a94, 0x64 bytes, Thumb
 * func_ov054_02261a00 @ 0x02261a00, 0x94 bytes, Thumb
 * func_ov054_0226194c @ 0x0226194c, 0xb4 bytes, Thumb
 * func_ov054_02261878 @ 0x02261878, 0xd4 bytes, Thumb
 * func_ov054_02261850 @ 0x02261850, 0x28 bytes, Thumb
 * func_ov054_0226175c @ 0x0226175c, 0xf4 bytes, Thumb
 * func_ov054_02261738 @ 0x02261738, 0x22 bytes, Thumb
 * func_ov054_022616c4 @ 0x022616c4, 0x74 bytes, Thumb
 * func_ov054_022616ac @ 0x022616ac, 0x16 bytes, Thumb
 * func_ov054_02261534 @ 0x02261534, 0x178 bytes, Thumb
 * func_ov054_022614b4 @ 0x022614b4, 0x80 bytes, Thumb
 * func_ov054_02261490 @ 0x02261490, 0x22 bytes, Thumb
 * func_ov054_02261428 @ 0x02261428, 0x68 bytes, Thumb
 * func_ov054_02261380 @ 0x02261380, 0xa8 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned int a;
    unsigned int b;
    unsigned int c;
} DataEntry;

struct UnkStruct_02261af8 {
    unsigned char pad_00[0x40];
    void *unk_40;
    unsigned char pad_44[0x6c];
    unsigned char *unk_B0;
    unsigned char pad_B4[0x10];
    int unk_C4;
};

typedef struct UnkStruct_02261a94 {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xb0 - 0x44];
    void *unk_B0;
} UnkStruct_02261a94;

typedef struct Elem {
    int a;
    int b;
    int c;
} Elem;

struct PType {
    char pad_00[0x40];
    void *unk_40;
    char pad_44[0x6c];
    int *unk_B0;
};

struct DataElem {
    int a;
    int b;
    int c;
};

struct LocalInfo {
    unsigned char flag;
    char pad_01[3];
    int data[2];
};

typedef struct {
    u32 a;
    u32 b;
    u32 c;
} TblEntry;

typedef struct UnkStruct_0226194c UnkStruct_0226194c;

struct UnkStruct_0226194c {
    u8 pad_00[0x40];
    void *unk_40;
    u8 pad_44[0x6c];
    void *unk_B0;
};

struct UnkStruct_0226194c_2 {
    u8 unk_00;
    u8 pad_01;
    u16 unk_02;
};

typedef struct DataEntry_02261878 {
    int unk_00;
    char pad[8];
} DataEntry_02261878;

typedef struct UnkStruct_02261878 {
    char pad[0x808];
    int val;
} UnkStruct_02261878;

typedef struct UnkStruct_02261878_2 {
    char pad_00[0x40];
    void *unk_40;
    char pad_44[0xb0 - 0x44];
    UnkStruct_02261878 *unk_B0;
    char pad_B4[0xc0 - 0xb4];
    int unk_C0;
} UnkStruct_02261878_2;

typedef struct LocalBuf {
    u8 unk_00;
    u16 b1;
    u16 b2;
} LocalBuf;

typedef struct UnkStruct_0226175c {
    char pad_00[0x808];
    int unk_808;
} UnkStruct_0226175c;

typedef struct UnkStruct_0226175c_2 {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xb0 - 0x44];
    UnkStruct_0226175c *unk_B0;
} UnkStruct_0226175c_2;

typedef struct Msg {
    u8 b;
    u8 pad_01;
    u16 unk_02;
    u16 unk_04;
} Msg;

typedef struct UnkStruct_0226175c_3 {
    int a;
    int b;
    int c;
} UnkStruct_0226175c_3;

struct func_ov054_02261738_data {
    char pad_00[0xb0];
    int unk_B0;
};

typedef struct UnkStruct_022616c4 {
    char pad_00[0x808];
    int n;
} UnkStruct_022616c4;

typedef struct UnkStruct_022616c4_2 {
    char pad_00[0x40];
    void *obj;
    char pad_44[0x6c];
    UnkStruct_022616c4 *unk_B0;
} UnkStruct_022616c4_2;

typedef struct UnkStruct_02261534_2 {
    char pad_00[0x808];
    int unk_808;
} UnkStruct_02261534_2;

typedef struct UnkStruct_02261534_3 {
    char pad_00[0x40];
    void *unk_40;
    char pad_44[0xb0 - 0x44];
    UnkStruct_02261534_2 *unk_B0;
    char pad_B4[0xc8 - 0xb4];
    char unk_C8;
} UnkStruct_02261534_3;

typedef struct UnkStruct_02261534 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03;
    u8 buf[0x10];
} UnkStruct_02261534;

typedef struct Inner_808 {
    unsigned char pad_808[0x808];
    unsigned int id;
} Inner_808;

typedef struct TabEntry12 {
    unsigned int a;
    unsigned char pad_12[8];
} TabEntry12;

typedef struct ArgType {
    unsigned char pad_00[0x40];
    unsigned int unk_40;
    unsigned char pad_44[0x6c];
    void *unk_B0;
    unsigned char pad_B4[0x14];
    unsigned char unk_C8;
} ArgType;

struct UnkStruct_02261490 {
    char pad_00[0xB0];
    void *unk_B0;
};

struct UnkStruct_02261428 {
    char pad_00[0x40];
    void *unk_40;
    char pad_44[0xb0 - 0x44];
    void *unk_B0;
};

struct UnkStruct_02261428_2 {
    int value;
    char pad_04[8];
};

typedef struct UnkStruct_02261380 {
    unsigned char pad_00[0x1e];
    unsigned char b;
} UnkStruct_02261380;

extern int func_0206fc6c(void);
extern int func_0206f83c(void);
extern void func_02015fb0(void *, int, int, int, int, int);
extern int func_02015330(void *, void *, int, int, int);
extern void func_ov054_02261cc4(void *, int);
extern int func_020984e8(void);
extern int func_020992fc(int);
extern int func_020983e0(void);
extern void func_020983c8(int);
extern int func_020155cc(void *);
extern DataEntry data_ov054_02262fac[];
extern unsigned char func_ov054_02260484(void *receiver);
extern void func_0206f80c(void *);
extern void func_02015ed0(void *, int, int);
extern void func_02015ea0(void *, int, int);
extern void func_0206f910(void);
extern void func_0206844c(void *, void *, int);
extern u8 data_021ebcd4;
extern u8 data_021dc7a8;
extern int func_02060d3c(void *ptr);
extern int func_0208602c(void);
extern void func_020860f0(int a, int b);
extern void func_0209f100(void *a, int b);
extern int func_020983f0(int *);
extern int _s32_div_f(int a, int b);
extern int func_020154b4(void *self, void *p, int a, int b, int c);
extern int func_02099640(int a);
extern int func_0209a850(int a);
extern int func_0202e9fc(void);
extern int func_0206fc8c(void);
extern int func_0209a034(int a);
extern void func_0209a050(int a);
extern int func_0204bcdc(u16 *p);
extern int func_0204bc64(u16 *p);
extern int func_0209af80(int v, char *q);
extern void *func_0209b0f0(void *record);
extern void func_0209bb90(void *a, int b);
extern int func_ov054_02260498(int);
extern void func_020a190c(void);
extern int func_020a1848(void);
extern int func_020a186c(void);
extern void func_02068358(void *);
extern void func_02068434(void *);
extern int func_02074308(void);
extern int func_020ec148(void);
extern int func_020e8840(char *);
extern void func_ov054_02261f44(UnkStruct_02261534_3 *);
extern void func_020730c8(void);
extern void **func_020eb92c(void);
extern void *func_020641c8(int *);
extern void *func_02064170(int *);
extern void *func_02064158(int *);
extern void *func_020641b0(int *);
extern int func_020eb998(void *);
extern void *func_020eb9c4(void *);
extern void MI_CpuCopy8(void *, u8 *, int);
extern void func_020a8874(int *, u8 *, int);
extern int func_020a8a70(int *, int *, int, int);
extern void func_02068404(void *, int, int *);
extern int func_020eb8d8(void *);
extern unsigned int func_02073044(void);
extern int func_020ec920(void);
extern void func_020a1894(void);
extern int func_020a17a8(void);
extern int func_020a17d0(void);
extern int func_02098a18(int);
extern unsigned char *func_02097e08(int);
extern int func_020a12e8(void);
extern int func_020988a4(void *, int);
extern int func_020984d4(void);
extern void *func_02098844(void *, int);
extern void *func_02099870(void *);
extern void func_02015e40(void *, void *, int);
extern unsigned char data_021dc7bc[];

void func_ov054_02261af8(struct UnkStruct_02261af8 *self)
{
    void *p40;
    unsigned int value;
    int r;
    unsigned char state;
    unsigned char buf[4];

    p40 = self->unk_40;
    value = data_ov054_02262fac[*(unsigned int *) (self->unk_B0 + 0x808)].a;

    if (func_0206fc6c() != 0) {
        r = func_0206f83c();
        func_02015fb0(self, r, 7, 10, 0, 0);
        if (r >= 0x1388) {
            state = 0x1d;
        } else {
            state = 0x1e;
        }
        *(unsigned short *) (buf + 2) = 0x149b;
        func_02015330(self, buf + 2, 0, 5, 1);
        func_ov054_02261cc4(self, 10);
        func_020992fc((int) func_020984e8());
        self->unk_C4 = func_020983e0();
        func_020983c8(self->unk_C4 + r);
    } else {
        state = 0x1c;
        func_020155cc(self);
        func_ov054_02261cc4(self, 0);
    }

    buf[0] = state;
    func_0206844c(p40, (void *) buf, value);
}

void func_ov054_02261a94(UnkStruct_02261a94 *self)
{
    u8 arg;
    int h;
    int code;
    int k;
    void *p;

    h = self->unk_40;
    p = self->unk_B0;
    k = ((Elem *) data_ov054_02262fac)[*(int *) ((char *) p + 0x808)].a;
    if (func_ov054_02260484(p) != 0) {
        if (func_0206fc6c() != 0) {
            code = 0x63;
        } else {
            code = 0x64;
        }
    } else {
        if (func_0206fc6c() != 0) {
            code = 0x5d;
        } else {
            code = 0x5e;
        }
    }
    func_ov054_02261cc4((void *) self, 0);
    arg = (u8) code;
    func_0206844c((void *) h, (void *) (&arg), k);
}

void func_ov054_02261a00(struct PType *p)
{
    void *saved;
    unsigned char val;
    unsigned char flag;
    unsigned char b7;
    unsigned char b8;
    int local_c;
    struct LocalInfo info;
    saved = p->unk_40;
    local_c = ((struct DataElem *) data_ov054_02262fac)[p->unk_B0[0x202]].a;
    if (func_0206fc6c() != 0) {
        flag = 12;
        info.data[0] = 0;
        info.data[1] = 0;
        func_0206f80c(info.data);
        val = ((unsigned char *) (&info.data[1]))[0];
        b7 = ((unsigned char *) (&info.data[0]))[3];
        b8 = val;
        func_02015fb0(p, ((unsigned char *) (&info.data[1]))[1] + 0x7d0, 1, 4, 0, 0);
        func_02015ed0(p, b8, 2);
        func_02015ea0(p, b7, 3);
    } else {
        flag = 14;
        func_0206f910();
    }
    func_ov054_02261cc4(p, 0);
    info.flag = flag;
    func_0206844c(saved, &info, local_c);
}

void func_ov054_0226194c(UnkStruct_0226194c *self)
{
    struct UnkStruct_0226194c_2 local;
    int r5;
    void *r6;
    int r7;
    u32 idx;

    r6 = self->unk_40;
    idx = *(u32 *) ((char *) self->unk_B0 + 0x808);
    r7 = (int) ((TblEntry *) data_ov054_02262fac)[idx].a;

    if (func_0206fc6c() != 0) {
        r5 = func_02060d3c(&data_021ebcd4);
        func_02015fb0(self, r5, 4, 0xa, 0, 0);
        if (r5 == 0) {
            r5 = 0x15;
            func_020860f0(func_0208602c(), 0);
            func_0209f100(&data_021dc7a8, 0x10);
        } else {
            r5 = 0x14;
        }
        local.unk_02 = 0x149b;
        func_02015330(self, &local.unk_02, 0, 5, 1);
        func_ov054_02261cc4(self, 0xa);
    } else {
        r5 = 0x13;
        func_020155cc(self);
        func_ov054_02261cc4(self, 0);
    }
    local.unk_00 = (u8) r5;
    func_0206844c(r6, &local, r7);
}

void func_ov054_02261878(UnkStruct_02261878_2 *self)
{
    void *tmp;
    int data;
    int val;
    int r6;
    int act;
    LocalBuf buf;

    tmp = self->unk_40;
    val = self->unk_B0->val;
    data = ((DataEntry_02261878 *) data_ov054_02262fac)[val].unk_00;

    if (func_0206fc6c() != 0) {
        r6 = func_020983f0((int *) func_020992fc((int) func_020984e8()));
        func_02015fb0(self, r6, 5, 10, 0, 0);
        val = _s32_div_f(r6, 0xc8);
        func_02015fb0(self, val, 6, 10, 0, 0);
        act = 0x17;
        if (r6 > self->unk_C0) {
            buf.b1 = 0x149b;
            func_02015330(self, &buf.b1, 0, 5, 1);
        } else {
            buf.b2 = 0x149b;
            func_020154b4(self, &buf.b2, 0, 5, 1);
        }
        func_ov054_02261cc4(self, 10);
    } else {
        act = 0x18;
        func_020155cc(self);
        func_ov054_02261cc4(self, 0);
    }

    buf.unk_00 = (u8) act;
    func_0206844c(tmp, &buf, data);
}

unsigned short func_ov054_02261850(unsigned short *r0, int r1)
{
    unsigned short result;
    unsigned short value;

    if (r1 == 2) {
        result = 0;
        value = *r0;
        if (value >= 0x155f && value <= 0x1560) {
            result = 1;
        }
        return result;
    }
    return 0;
}

void func_ov054_0226175c(UnkStruct_0226175c_2 *self)
{
    Msg m;
    int h;
    int v;
    int k;
    int t;
    int r;
    u8 code;
    unsigned int ok;

    h = self->unk_40;
    k = ((UnkStruct_0226175c_3 *) data_ov054_02262fac)[self->unk_B0->unk_808].a;
    code = 0x51;
    if (func_0206fc6c() != 0) {
        v = func_0209a850(func_02099640(func_020984e8()));
        if (func_0202e9fc() != 0) {
            t = func_0206fc8c();
            m.unk_02 = (u16) func_0209a034(t);
            if (t >= 0) {
                func_0209a050(t);
            }
            if (func_0204bcdc(&m.unk_02) != 0) {
                m.unk_04 = 0xfff1;
                r = func_0204bc64(&m.unk_02);
                ok = (r == func_0204bc64(&m.unk_04)) ? 1 : 0;
            } else {
                ok = (m.unk_02 == 0xfff1) ? 1 : 0;
            }
            if (ok == 0) {
                func_02015330((void *) self, (void *) (&m.unk_02), 2, 5, 1);
                if (func_0209af80(v, (char *) self->unk_B0 + 0xea) == 0) {
                    code = 0x57;
                } else {
                    code = 0x50;
                }
                func_0209bb90(func_0209b0f0((void *) v), 1);
            }
        }
    }
    func_ov054_02261cc4((void *) self, 0);
    m.b = code;
    func_0206844c((void *) h, (void *) (&m.b), k);
}

void func_ov054_02261738(struct func_ov054_02261738_data *p)
{
    if (func_ov054_02260498(p->unk_B0)) {
        func_020a190c();
        func_ov054_02261cc4(p, 9);
    }
}

void func_ov054_022616c4(UnkStruct_022616c4_2 *p)
{
    void *obj;
    char c;
    int idx;
    int val;

    obj = p->obj;
    if (func_020a1848() != 0) {
        func_02068358(obj);
        func_02068434(obj);
        c = 2;
        idx = p->unk_B0->n;
        val = *(int *) (((char *) data_ov054_02262fac) + idx * 12);
        func_0206844c(obj, (void *) (&c), val);
        func_ov054_02261cc4((void *) p, 0);
    } else if (func_020a186c() != 0) {
        func_02068358(obj);
        func_02068434(obj);
        func_ov054_02261cc4((void *) p, 0);
    }
}

void func_ov054_022616ac(void *object)
{
    func_020155cc((void *) ((int) object));
    func_ov054_02261cc4(object, 0);
}

void func_ov054_02261534(UnkStruct_02261534_3 *this)
{
    UnkStruct_02261534 m;
    int blkA[8];
    int blkB[8];
    void *o = this->unk_40;
    int cnt;
    void **list;
    void *item;
    int arg3;
    int n;
    int code;
    u8 i;

    arg3 = *(int *) (((char *) data_ov054_02262fac) + 12 * this->unk_B0->unk_808);
    func_02074308();
    cnt = func_020ec148();
    if (func_020e8840(&this->unk_C8) == 0) {
        func_ov054_02261f44(this);
        m.unk_00 = 0x37;
        func_0206844c(o, (void *) (&m.unk_00), *(int *) (((char *) data_ov054_02262fac) + 12 * this->unk_B0->unk_808));
        func_02068358(o);
        func_02068434(o);
        func_ov054_02261cc4((void *) this, 0);
        return;
    }
    if (cnt > 0) {
        func_020730c8();
        list = func_020eb92c();
        func_020641c8(blkA);
        func_02064170(blkB);
        for (i = 0; i < cnt; i++) {
            item = list[i];
            if (item == 0) {
                continue;
            }
            func_020730c8();
            n = func_020eb998(item);
            if (n != 0xe) {
                continue;
            }
            func_020730c8();
            MI_CpuCopy8(func_020eb9c4(item), m.buf, n);
            if (m.buf[0xd] != 1) {
                continue;
            }
            code = 0x38;
            if (m.buf[0xc] == 0) {
                func_020a8874(blkB, m.buf, 6);
                func_020a8a70(blkA, blkB, 0, 0);
                func_02068404(o, 8, blkA);
                code = 0x39;
            }
            m.unk_01 = (u8) code;
            func_0206844c(o, (void *) (&m.unk_01), arg3);
            func_020730c8();
            if (func_020eb8d8(item) != 0) {
                func_ov054_02261cc4((void *) this, 0xd);
                break;
            } else {
                func_ov054_02261f44(this);
                m.unk_02 = 0x37;
                func_0206844c(o, (void *) (&m.unk_02), *(int *) (((char *) data_ov054_02262fac) + 12 * this->unk_B0->unk_808));
                func_02068358(o);
                func_02068434(o);
                func_ov054_02261cc4((void *) this, 0);
                break;
            }
        }
        func_02064158(blkB);
        func_020641b0(blkA);
    }
}

void func_ov054_022614b4(ArgType *arg)
{
    unsigned int field_40;
    int res;
    field_40 = arg->unk_40;
    res = func_020e8840((char *) ((char *) arg + 0xc8));
    if (res == 0) {
        unsigned char local;
        func_ov054_02261f44((UnkStruct_02261534_3 *) arg);
        local = 0x37;
        func_0206844c((void *) field_40, (void *) (&local), ((TabEntry12 *) data_ov054_02262fac)[((Inner_808 *) arg->unk_B0)->id].a);
        func_02068358((void *) field_40);
        func_02068434((void *) field_40);
        func_ov054_02261cc4((void *) arg, 0);
    } else {
        func_02073044();
        if (func_020ec920()) {
            func_02068358((void *) field_40);
            func_02068434((void *) field_40);
            func_ov054_02261cc4((void *) arg, 0);
        }
    }
}

void func_ov054_02261490(struct UnkStruct_02261490 *obj)
{
    if (func_ov054_02260498((int) obj->unk_B0) != 0) {
        func_020a1894();
        func_ov054_02261cc4((void *) obj, 0xF);
    }
}

void func_ov054_02261428(struct UnkStruct_02261428 *p)
{
    void *r4 = p->unk_40;
    if (func_020a17a8()) {
        func_ov054_02261cc4(p, 0);
        return;
    }
    if (func_020a17d0()) {
        char local;
        func_02068358(r4);
        func_02068434(r4);
        local = 0x3c;
        {
            int idx = *(int *) ((char *) p->unk_B0 + 0x808);
            func_0206844c(r4, (void *) (&local), ((struct UnkStruct_02261428_2 *) data_ov054_02262fac)[idx].value);
        }
        func_ov054_02261cc4(p, 0);
    }
    return;
}

void func_ov054_02261380(UnkStruct_02261380 *self)
{
    if (self->b == 0xf) {
        unsigned char *p = func_02097e08(func_02098a18(func_020984e8()));
        unsigned char a = p[1];
        unsigned char b = p[0];
        func_02015fb0(self, p[2] + 0x7d0, 1, 4, 0, 0);
        func_02015ed0(self, a, 2);
        func_02015ea0(self, b, 3);
    }
    if (func_020a12e8() != 0) {
        switch (self->b) {
            case 0x24:
            case 0x25:
            case 0x26: {
                int j = 0;
                int i = j;
                for (; i < 4; i++) {
                    if (func_020988a4(data_021dc7bc, i) != 0 && i != func_020984d4()) {
                        func_02015e40(self, func_02099870(func_02098844(data_021dc7bc, i)), j + 2);
                        j++;
                    }
                }
                break;
            }
            default:
                break;
        }
    }
}
