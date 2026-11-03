/* villager_talk_topics: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02021410 @ 0x02021410, 0xd0 bytes, Thumb
 * func_02021284 @ 0x02021284, 0x18c bytes, Thumb
 * func_020211dc @ 0x020211dc, 0xa8 bytes, Thumb
 * func_02021168 @ 0x02021168, 0x74 bytes, Thumb
 * func_0202114c @ 0x0202114c, 0x1c bytes, Thumb
 * func_02021118 @ 0x02021118, 0x34 bytes, Thumb
 */

#include "types.h"

typedef struct {
    u8 a : 2;
    u8 b : 3;
    u8 c : 3;
} Flags;

typedef struct UnkStruct_02021410 {
    char pad[0x830];
    int unk_830;
} UnkStruct_02021410;

typedef struct {
    int unk_00;
    unsigned char unk_04;
} Cfg;

typedef struct UnkStruct_02021410_2 {
    char pad_00[0x100];
    UnkStruct_02021410 *unk_100;
    char unk_104[0x1e];
    unsigned char unk_122;
} UnkStruct_02021410_2;

typedef struct {
    Flags unk_00;
    u8 pad[3];
    int b0;
    int b1;
} Agg;

typedef struct Rec {
    u16 unk_00;
    char name[0xc];
    char rest[0x3c];
} Rec;

typedef struct Big {
    char pad_00[0x830];
    void *unk_830;
} Big;

typedef struct UnkStruct_02021284_3 {
    char unk_00[0x40];
    void *unk_40;
    char unk_44[0x100 - 0x44];
    Big *unk_100;
    char unk_104[0x1e];
    char unk_122[0x1e];
} UnkStruct_02021284_3;

typedef struct Gd {
    void *unk_00;
    u8 unk_04;
} Gd;

typedef struct UnkStruct_02021284 {
    char pad_00[0x1c];
} UnkStruct_02021284;

typedef struct UnkStruct_02021284_2 {
    char pad_00[0x20];
} UnkStruct_02021284_2;

typedef struct UnkStruct_020211dc {
    u8 pad_00[0x100];
    void *unk_100;
    u8 arr[0x1e];
    u8 unk_122;
    u8 pad_123[0x49];
    u32 unk_16C;
    u32 unk_170;
    u32 unk_174;
    u32 unk_178;
} UnkStruct_020211dc;

struct UnkStruct_02021168 {
    char pad_00[0x830];
    int unk_830;
};

struct UnkStruct_02021168_2 {
    char pad_00[0x100];
    struct UnkStruct_02021168 *unk_100;
    char unk_104[0x122 - 0x104];
    char unk_122[1];
};

struct Global {
    int a;
    unsigned char b;
};

extern Cfg data_020c8bb8;
extern u8 data_020c8934[];
extern void func_0209e474(void *p);
extern int func_02088470(int a, int b, int c, Flags *d);
extern int func_0208150c(int x);
extern int func_020036e8(int x);
extern int func_0202da38(UnkStruct_02021410_2 *self, char *a, unsigned char *b, int n, int e, int f, int g, int h, int i);
extern u8 data_020e54a8;
extern Gd data_020c8b98;
extern Rec *func_020b15b0(void);
extern int func_020b120c(void);
extern void *func_020984e8(void);
extern int func_020b1974(Rec *, int);
extern int func_020951bc(Rec *);
extern Rec *func_02099870(void *);
extern int memcmp(const char *, const char *, int);
extern int func_0209518c(Rec *, Rec *);
extern int func_02094ffc(Rec *);
extern int func_02094fec(Rec *);
extern void *func_020b18fc(UnkStruct_02021284 *);
extern void *func_020b1954(UnkStruct_02021284_2 *);
extern void func_020a8874(UnkStruct_02021284 *, void *, int);
extern int func_020a8a70(UnkStruct_02021284_2 *, UnkStruct_02021284 *, int, int);
extern void func_02068404(void *, int, UnkStruct_02021284_2 *);
extern void *func_020b193c(UnkStruct_02021284_2 *);
extern void *func_020b18e4(UnkStruct_02021284 *);
extern void func_02015e40(UnkStruct_02021284_3 *, void *, int);
extern int func_02095040(void *);
extern void *func_02015e70(UnkStruct_02021284_3 *, int, int);
extern int func_020991c8(int);
extern void func_020991a0(int);
extern int func_02073d90(int);
extern int func_0200368c(void *, int, int, int);
extern int data_020ccf94;
extern int data_020c8c20;
extern u32 data_020d9078[2];
extern u32 data_020d9498[2];
extern int func_020644cc(int);
extern int func_0201cddc(int);
extern struct Global data_020c8b80;
extern int func_0202d6e4(int a, int b);
extern int func_0202bd7c(void *param0, int param1, int param2);
extern void func_0202bd40(void *param0, int param1, int param2);

int func_02021410(UnkStruct_02021410_2 *self)
{
    // DECLS
    int ret;
    int mode;
    int sel;
    int idx;
    Agg agg;
    unsigned int k;
    // ENDDECLS

    mode = data_020c8bb8.unk_04;
    idx = 0;
    agg.b0 = 0;
    agg.b1 = 0;
    sel = -1;
    ret = 0;
    func_0209e474(&agg.b0);
    if (func_02088470(((u8 *) &agg)[9], ((u8 *) &agg)[8], ((u8 *) &agg)[7], &agg.unk_00) != 0) {
        if (agg.unk_00.a == 2 && agg.unk_00.b == 3) {
            sel = 1;
        } else {
            sel = 0;
        }
    }
    switch (sel) {
        case 0:
            k = agg.unk_00.a;
            if (k >= 4) {
                k = 0;
            }
            idx = data_020c8934[k];
            ret = 1;
            break;
        case 1:
            mode = 1;
            idx = agg.unk_00.c + 0xc;
            ret = mode;
            break;
    }
    if (ret == 1) {
        func_0202da38(self, self->unk_104, &self->unk_122, 0x1e, func_020036e8(func_0208150c(self->unk_100->unk_830)),
                      data_020c8bb8.unk_00, mode, idx, 0);
    }
    return ret;
}

int func_02021284(UnkStruct_02021284_3 *self)
{
    void *pa;
    UnkStruct_02021284 o1;
    void *ctx;
    int st;
    unsigned int ok;
    Rec *o;
    void *pb;
    int ret;
    int idx;
    Rec *base;
    UnkStruct_02021284_2 o2;
    Rec *e;

    if (data_020e54a8 == 0) {
        ok = 1;
    } else {
        ok = 0;
    }
    if (ok == 0) {
        return 0;
    }
    base = func_020b15b0();
    idx = func_020b120c();
    ctx = func_020984e8();
    pa = 0;
    pb = 0;
    st = -1;
    ret = 0;
    if (idx != st) {
        if (func_020b1974(base, idx) != 0) {
            if (ctx != 0) {
                e = &base[idx];
                if (func_020951bc(e) != 0) {
                    o = func_02099870(ctx);
                    if (e->unk_00 == o->unk_00 && memcmp(e->name, o->name, 0xc) == 0 && func_0209518c(e, o) != 0) {
                        st = 0;
                    } else if (func_02094ffc(e) == 0) {
                        if (func_02094fec(e) != -1) {
                            st = 1;
                        }
                    } else if (func_0209518c(e, func_02099870(ctx)) == 0) {
                        st = 2;
                    }
                    if (st != -1) {
                        pa = e;
                        pb = e;
                        e = (Rec *) ((char *) e + 0x1e);
                        pb = e;
                    }
                }
            }
        }
    }
    if (st == -1) {
        goto done;
    }
    func_0202da38((UnkStruct_02021410_2 *) self, self->unk_104, (unsigned char *) self->unk_122, 0x1e, func_020036e8((int) ((unsigned char *) (unsigned int) func_0208150c((int) self->unk_100->unk_830))), (int) data_020c8b98.unk_00, data_020c8b98.unk_04, st, 0);
    ret = 1;
    if (pb != 0) {
        func_020b18fc(&o1);
        func_020b1954(&o2);
        func_020a8874(&o1, pb, 6);
        func_020a8a70(&o2, &o1, 0, 0);
        func_02068404(self->unk_40, 0, &o2);
        func_020b193c(&o2);
        func_020b18e4(&o1);
    }
    if (pa != 0) {
        func_02015e40(self, pa, 1);
        func_02015e70(self, func_02095040(pa), 2);
    }
done:
    return ret;
}

int func_020211dc(UnkStruct_020211dc *self)
{
    int r4;
    int ret1;
    int ret2;
    UnkStruct_020211dc *ptr;
    r4 = func_020991c8((int) func_020984e8());
    if (func_02073d90(data_020ccf94) != 0) {
        r4 = 10;
    }
    ptr = self;
    if (r4 < 10) {
        if (1) {
            int v = *((int *) (((char *) self->unk_100) + 0x830));
            ret1 = func_0208150c(v);
            ret2 = func_020036e8(ret1);
            func_0200368c(ptr->arr, 30, data_020c8c20, ret2);
            self->unk_122 = r4;
            func_020991a0((int) func_020984e8());
        }
        {
            volatile u32 *srcA = (volatile u32 *) data_020d9078;
            u32 a0;
            u32 a1;
            volatile u32 *srcB;
            u32 b0;
            u32 b1;
            a0 = srcA[0];
            a1 = srcA[1];
            self->unk_16C = a0;
            self->unk_170 = a1;
            srcB = (volatile u32 *) data_020d9498;
            b0 = srcB[0];
            b1 = srcB[1];
            self->unk_174 = b0;
            self->unk_178 = b1;
        }
        return 1;
    } else {
        return 0;
    }
}

int func_02021168(struct UnkStruct_02021168_2 *self)
{
    int ret = func_020644cc(2);
    if (func_0201cddc((int) self->unk_100) != 10) {
        goto fail;
    }
    if (ret != 0) {
        goto fail;
    }
    func_0202da38((UnkStruct_02021410_2 *) self, (char *) (&self->unk_104), (unsigned char *) (&self->unk_122), 30, func_020036e8(func_0208150c(self->unk_100->unk_830)), data_020c8b80.a, data_020c8b80.b, 0, 0);
    return 1;
fail:
    return 0;
}

int func_0202114c(int, int a, int b)
{
    int result;
    result = func_0202d6e4(a, b);
    if (result == -1) {
        return 4;
    }
    return result;
}

int func_02021118(void *param0)
{
    func_0202bd7c(param0, 4, 3);
    func_0202bd40(param0, 5, *(int *) (*(int *) ((char *) param0 + 0x100) + 0x830));
    return func_0202bd7c(param0, 6, 4);
}
