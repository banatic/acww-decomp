/* villager_talk_offers_7: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02028d04 @ 0x02028d04, 0x258 bytes, Thumb
 * func_02028c04 @ 0x02028c04, 0x100 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_02028d04 UnkStruct_02028d04;

struct UnkStruct_02028d04 {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xbc];
    void *unk_100;
    char pad_104[0x20];
    unsigned short unk_124;
    char pad_126[0x3e];
    int unk_164;
};

typedef struct {
    unsigned char zb[0x28];
} UnkStruct_02028d04_2;

typedef struct {
    int unk_00, w1;
} Pair8;

typedef struct {
    int a;
    int b;
} UnkStruct_02028c04;

typedef struct {
    int pad_00[8];
    u8 a;
    u8 b;
    u8 pad_22[2];
} ST;

typedef struct {
    int x;
    int y;
} UnkStruct_02028c04_2;

typedef struct {
    u8 pad_00[0x64];
    int unk_64;
} GS;

typedef struct {
    u8 pad_00[0x10];
    int unk_10;
} SUB;

typedef struct {
    u8 pad_00[0xa4];
    SUB sub;
} UnkStruct_02028c04_3;

typedef struct {
    u8 pad_00[0x40];
    int unk_40;
    u8 pad_44[0x100 - 0x44];
    void *unk_100;
} CTX;

extern unsigned char data_020e54a8;
extern const int data_021c2c8c;
extern const Pair8 data_020d8db8;
extern int func_0207f270(void *);
extern int func_020794d0(int);
extern unsigned int func_0207f1c8(void *);
extern int func_0209b5e8(int);
extern int func_0201cddc(void *);
extern int func_0209bc40(int);
extern void func_0202e118(unsigned short *, void *);
extern void func_020266d8(unsigned short *, UnkStruct_02028d04 *, int);
extern void func_02026584(unsigned short *, UnkStruct_02028d04 *, int);
extern void func_0201cfb4(UnkStruct_02028d04 *, UnkStruct_02028d04_2 *);
extern void func_0201cf74(UnkStruct_02028d04 *, UnkStruct_02028d04_2 *, int, const int *, const int *);
extern void func_0202d9d0(UnkStruct_02028d04 *, int);
extern void func_0201cec8(UnkStruct_02028d04 *, UnkStruct_02028d04_2 *);
extern void func_0202da74(UnkStruct_02028d04 *, Pair8);
extern void func_02068388(int, int);
extern GS *data_020ccf94;
extern int data_020c8928;
extern int data_021c2fec;
extern int data_020c8924;
extern int data_021c1d6c;
extern UnkStruct_02028c04_2 data_020d8eb8;
extern void func_0209e474(UnkStruct_02028c04 *);
extern int func_02073dd4(GS *, int);
extern int func_0209bd44(int *);
extern int func_0207ef54(void *, UnkStruct_02028c04_3 *);
extern int func_0207f150(void *);
extern int func_02080998(void *, int, UnkStruct_02028c04 *);
extern int func_0207aeac(int, UnkStruct_02028c04 *);

int func_02028d04(UnkStruct_02028d04 *p, void *arg, int value)
{
    unsigned short q[8];
    UnkStruct_02028d04_2 z;
    int changed;
    int r6;
    unsigned int ok2;
    unsigned short hv, lv;

    r6 = func_020794d0((int) func_0207f270(arg));
    q[0] = 0xfff1;
    changed = 0;
    p->unk_164 = func_0209b5e8((int) func_0207f1c8(arg));
    if (func_0201cddc(p->unk_100) != 0xb) {
        goto end;
    }
    switch (func_0209bc40(r6)) {
        case 0:
            if ((unsigned int) (data_020e54a8 == 0) + (unsigned int) changed) {
                func_0202e118(&q[1], p->unk_100);
                ok2 = 0;
                hv = *(volatile unsigned short *) &q[1];
                lv = *(volatile unsigned short *) &q[1];
                if (lv >= 0x1376 && hv <= 0x1376) {
                    ok2 = 1;
                }
                if (ok2 == 0) {
                    goto end;
                }
            }
            func_020266d8(&q[2], p, 0);
            q[0] = q[2];
            ok2 = 0;
            hv = *(volatile unsigned short *) &q[0];
            lv = *(volatile unsigned short *) &q[0];
            if (lv >= 0x12b0 && hv <= 0x12e7) {
                ok2 = 1;
            }
            if (ok2) {
                p->unk_124 = hv;
                changed = 1;
            }
            break;
        case 1:
            if ((unsigned int) (data_020e54a8 == 0) + (unsigned int) changed) {
                func_0202e118(&q[3], p->unk_100);
                ok2 = 0;
                hv = *(volatile unsigned short *) &q[3];
                lv = *(volatile unsigned short *) &q[3];
                if (lv >= 0x1374 && hv <= 0x1374) {
                    ok2 = 1;
                }
                if (ok2 == 0) {
                    goto end;
                }
            }
            func_02026584(&q[4], p, 0);
            q[0] = q[4];
            ok2 = 0;
            hv = *(volatile unsigned short *) &q[0];
            lv = *(volatile unsigned short *) &q[0];
            if (lv >= 0x12e8 && hv <= 0x131f) {
                ok2 = 1;
            }
            if (ok2) {
                p->unk_124 = hv;
                changed = 1;
            }
            break;
        case 2:
            if ((unsigned int) (data_020e54a8 == 0) + (unsigned int) changed) {
                func_0202e118(&q[5], p->unk_100);
                ok2 = 0;
                hv = *(volatile unsigned short *) &q[5];
                lv = *(volatile unsigned short *) &q[5];
                if (lv >= 0x1369 && hv <= 0x1369) {
                    ok2 = 1;
                }
                if (ok2 == 0) {
                    goto end;
                }
            }
            changed = 1;
            break;
        default:
            if ((unsigned int) (data_020e54a8 == 0) + (unsigned int) changed) {
                func_0202e118(&q[6], p->unk_100);
                if (q[6] != 0xfff1) {
                    func_0202e118(&q[7], p->unk_100);
                    ok2 = 0;
                    hv = *(volatile unsigned short *) &q[7];
                    lv = *(volatile unsigned short *) &q[7];
                    if (lv >= 0x1380 && hv <= 0x139f) {
                        ok2 = 1;
                    }
                    if (ok2 == 0) {
                        goto end;
                    }
                }
            }
            changed = 1;
            break;
    }
end:
    if (changed) {
        func_0201cfb4(p, &z);
        func_0201cf74(p, &z, 0, ((const int *) &data_020c8928), &data_021c2c8c);
        func_0202d9d0(p, r6);
        func_0201cf74(p, &z, 1, ((const int *) &data_020c8924), ((const int *) &data_021c1d6c));
        z.zb[0x20] = 2;
        z.zb[0x21] = (char) (z.zb[0x20] - 1);
        func_0201cec8(p, &z);
        func_0202da74(p, data_020d8db8);
        func_02068388(p->unk_40, 1);
        return 1;
    }
    return 0;
}

int func_02028c04(CTX *a1, void *a2, UnkStruct_02028c04_3 *a3)
{
    int x;
    UnkStruct_02028c04 s;
    ST st;
    SUB *p;

    x = func_020794d0((int) func_0207f270(a2));
    p = &a3->sub;
    s.a = 0;
    s.b = 0;
    func_0209e474(&s);
    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) == 0 && func_0209bd44(&p->unk_10) == 0 &&
        func_0207ef54(a2, a3) == 0 && func_0207f150(a2) == 3 && func_0201cddc(a1->unk_100) == 0xb &&
        func_02080998(a2, 1, &s) == -1 && func_0207aeac(1, &s) == 0xb) {
        func_0201cfb4((UnkStruct_02028d04 *) a1, (UnkStruct_02028d04_2 *) (&st));
        func_0201cf74((UnkStruct_02028d04 *) a1, (UnkStruct_02028d04_2 *) (&st), 0, (const int *) (&data_020c8928), (const int *) (&data_021c2fec));
        func_0201cf74((UnkStruct_02028d04 *) a1, (UnkStruct_02028d04_2 *) (&st), 1, (const int *) (&data_020c8924), (const int *) (&data_021c1d6c));
        func_0202d9d0((UnkStruct_02028d04 *) a1, x);
        st.a = 2;
        st.b = st.a - 1;
        func_0201cec8((UnkStruct_02028d04 *) a1, (UnkStruct_02028d04_2 *) (&st));
        func_0202da74((UnkStruct_02028d04 *) a1, *(Pair8 *) &data_020d8eb8);
        func_02068388(a1->unk_40, 1);
        return 1;
    }
    return 0;
}
