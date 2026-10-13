/* func_02021284 @ 0x02021284, 0x18c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

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
extern void func_0208150c(void *);
extern int func_020036e8(void);
extern void func_0202da38(UnkStruct_02021284_3 *, char *, char *, int, int, void *, int, int, int);
extern void func_020b18fc(UnkStruct_02021284 *);
extern void func_020b1954(UnkStruct_02021284_2 *);
extern void func_020a8874(UnkStruct_02021284 *, void *, int);
extern void func_020a8a70(UnkStruct_02021284_2 *, UnkStruct_02021284 *, int, int);
extern void func_02068404(void *, int, UnkStruct_02021284_2 *);
extern void func_020b193c(UnkStruct_02021284_2 *);
extern void func_020b18e4(UnkStruct_02021284 *);
extern void func_02015e40(UnkStruct_02021284_3 *, void *, int);
extern int func_02095040(void *);
extern void func_02015e70(UnkStruct_02021284_3 *, int, int);

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
    func_0208150c(self->unk_100->unk_830);
    func_0202da38(self, self->unk_104, self->unk_122, 0x1e, func_020036e8(), data_020c8b98.unk_00, data_020c8b98.unk_04, st,
                  0);
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
