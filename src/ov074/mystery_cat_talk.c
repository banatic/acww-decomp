/* mystery_cat_talk: 3 functions, module ov074
 * mwccarm 1.2/base -O4,s
 * func_ov074_02278de8 @ 0x02278de8, 0x1c0 bytes, Thumb
 * func_ov074_02278d44 @ 0x02278d44, 0xa4 bytes, Thumb
 * func_ov074_02278ba4 @ 0x02278ba4, 0x1a0 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned short v[6];
} UnkStruct_02278de8;

typedef struct {
    unsigned short v[10];
} V10;

typedef struct Hdr {
    unsigned short a;
    UnkStruct_02278de8 b;
    unsigned short c;
    UnkStruct_02278de8 d;
    signed char e;
    unsigned char unk_1D;
} Hdr;

typedef struct Rec {
    unsigned short a;
    UnkStruct_02278de8 b;
    unsigned short c;
    UnkStruct_02278de8 d;
    signed char e;
    unsigned char unk_1D;
    V10 g;
    unsigned char h;
} Rec;

typedef struct Blob {
    int w[10];
} Blob;

typedef struct Owner {
    int unk_00;
} Owner;

typedef struct UnkStruct_02278de8_2 {
    char pad_00[0x40];
    Owner *unk_40;
} UnkStruct_02278de8_2;

typedef struct UnkStruct_02278de8_3 {
    int unk_00;
    unsigned char unk_04;
} UnkStruct_02278de8_3;

typedef struct UnkStruct_02278d44 {
    char pad_00[0x1e];
    u8 unk_1E;
    char pad_1F[0x40 - 0x1f];
    int unk_40;
    char pad_44[0xb0 - 0x44];
    char *unk_B0;
} UnkStruct_02278d44;

typedef struct {
    unsigned short v[6];
} UnkStruct_02278ba4;

typedef struct Hdr_02278ba4 {
    unsigned short a;
    UnkStruct_02278ba4 b;
    unsigned short c;
    UnkStruct_02278ba4 d;
    signed char e;
    unsigned char unk_1D;
} Hdr_02278ba4;

typedef struct Rec_02278ba4 {
    unsigned short a;
    UnkStruct_02278ba4 b;
    unsigned short c;
    UnkStruct_02278ba4 d;
    signed char e;
    unsigned char unk_1D;
    V10 g;
    unsigned char h;
} Rec_02278ba4;

typedef struct UnkStruct_02278ba4_2 {
    char pad_00[0x1e];
    unsigned char unk_1E;
    char pad_1F[0x40 - 0x1f];
    int unk_40;
} UnkStruct_02278ba4_2;

extern int data_ov074_02279d14;
extern int data_021f3278;
extern int data_ov074_02279d28;
extern void *func_02088220(void *record);
extern Rec *func_02072d4c(void *record);
extern Hdr *func_02072ee8(Rec *record);
extern int func_020644cc(int a);
extern int func_0202ea80(int a, int b);
extern int func_020951bc(Hdr *h);
extern int func_020984e8(void);
extern Hdr *func_02099870(int argument0);
extern int memcmp(const void *a, const void *b, unsigned long n);
extern int func_0209518c(Hdr *h, Hdr *q);
extern void *func_02062fbc(Blob *t);
extern void func_02015e40(UnkStruct_02278de8_2 *self, Hdr *h, int a);
extern int func_02095040(Hdr *h);
extern void *func_02015e70(UnkStruct_02278de8_2 *self, int a, int b);
extern int func_020881f0(int *p);
extern int func_020683e4(Owner *o, int a, unsigned char *p, int *t);
extern void func_02072eb8(Rec *r, Blob *t);
extern void func_02068404(Owner *o, int a, Blob *t);
extern void *func_02062f4c(Blob *t);
extern int func_0209526c(Hdr *h);
extern int func_02072fac(Rec *r);
extern void func_ov074_02278a90(char *a, char *b);
extern void func_020157c8(UnkStruct_02278d44 *self, int a, int b);
extern int func_02015828(UnkStruct_02278d44 *self, int a);
extern void func_ov074_022790b4(UnkStruct_02278d44 *self, int a);
extern void func_0206844c(int h, u8 *p, int k);
extern int func_020160b4(void *argument0);
extern int func_020ab504(void *argument0);

void func_ov074_02278de8(UnkStruct_02278de8_2 *self, UnkStruct_02278de8_3 *out)
{
    unsigned char code;
    Rec a;
    Hdr b;
    Blob t;
    Rec *r;
    void *record;
    Hdr *p;
    Hdr *q;
    int *g;

    out->unk_00 = (int) &data_ov074_02279d14;
    g = &data_021f3278;
    record = func_02088220(g);
    r = func_02072d4c(record);
    a.a = r->a;
    a.b = r->b;
    a.c = r->c;
    a.d = r->d;
    a.e = r->e;
    a.unk_1D = r->unk_1D;
    a.g = r->g;
    a.h = r->h;
    p = func_02072ee8(&a);
    b.a = p->a;
    b.b = p->b;
    b.c = p->c;
    b.d = p->d;
    b.e = p->e;
    b.unk_1D = p->unk_1D;
    if (func_020644cc(2) == 0 || func_0202ea80(0x2b, 0) == 0) {
        out->unk_04 = 3;
    } else {
        if (func_020951bc(&b) != 0) {

            q = func_02099870((int) func_020984e8());
            if (b.a == q->a) {
                if (memcmp(&b.b, &q->b, 0xc) == 0) {
                    if (func_0209518c(&b, q) != 0) {
                        out->unk_04 = (unsigned char) (func_020644cc(4) + 0x18);
                        goto done;
                    }
                }
            }
        }
        out->unk_04 = (unsigned char) (func_020644cc(4) + 0x11);
    }
done:
    func_02062fbc(&t);
    if (func_020951bc(&b) != 0) {
        func_02015e40(self, &b, 1);
        func_02015e70(self, func_02095040(&b), 0);
        code = (unsigned char) func_020881f0(g);
        func_020683e4(self->unk_40, 2, &code, &data_ov074_02279d28);
        func_02072eb8(&a, &t);
        func_02068404(self->unk_40, 3, &t);
    }
    func_02062f4c(&t);
    func_0209526c(&b);
    func_02072fac(&a);
}

void func_ov074_02278d44(UnkStruct_02278d44 *self)
{
    u8 arg;
    int code;
    int k;

    k = (int) &data_ov074_02279d14;
    code = 0xff;
    switch (self->unk_1E) {
        case 9:
        case 10:
        case 11:
        case 12:
            code = 0xd;
            break;
        case 14:
            func_ov074_02278a90(self->unk_B0 + 0x714, self->unk_B0 + 0xec);
            func_020157c8(self, 3, 0);
            func_02015828(self, 2);
            func_ov074_022790b4(self, 0);
            break;
        case 0x1c:
            func_020157c8(self, 0x14, 0);
            func_02015828(self, 2);
            func_ov074_022790b4(self, 1);
            break;
    }
    if (code != 0xff) {
        arg = (u8) code;
        func_0206844c(self->unk_40, &arg, k);
    }
}

void func_ov074_02278ba4(UnkStruct_02278ba4_2 *self)
{
    unsigned char code;
    Rec_02278ba4 a;
    Hdr_02278ba4 b;
    int ok;
    Hdr_02278ba4 *q;
    Rec_02278ba4 *r;
    Hdr_02278ba4 *p;
    int *tail;
    int status;

    ok = func_020ab504((void *) func_020160b4(self));
    r = (Rec_02278ba4 *) func_02072d4c(func_02088220(&data_021f3278));
    a.a = r->a;
    a.b = r->b;
    a.c = r->c;
    a.d = r->d;
    a.e = r->e;
    a.unk_1D = r->unk_1D;
    a.g = r->g;
    a.h = r->h;
    p = (Hdr_02278ba4 *) func_02072ee8((Rec *) (&a));
    b.a = p->a;
    b.b = p->b;
    b.c = p->c;
    b.d = p->d;
    b.e = p->e;
    b.unk_1D = p->unk_1D;
    tail = &data_ov074_02279d14;
    status = 0xff;
    switch (self->unk_1E) {
        case 3:
            if (ok == 0) {
                if (func_020951bc((Hdr *) (&b)) != 0) {

                    q = (Hdr_02278ba4 *) func_02099870((int) func_020984e8());
                    if (b.a == q->a) {
                        if (memcmp(&b.b, &q->b, 0xc) == 0) {
                            if (func_0209518c((Hdr *) (&b), (Hdr *) q) != 0) {
                                status = 0xa;
                                break;
                            }
                        }
                    }
                }
                status = 9;
            } else {
                if (func_020951bc((Hdr *) (&b)) != 0) {

                    q = (Hdr_02278ba4 *) func_02099870((int) func_020984e8());
                    if (b.a == q->a) {
                        if (memcmp(&b.b, &q->b, 0xc) == 0) {
                            if (func_0209518c((Hdr *) (&b), (Hdr *) q) != 0) {
                                status = 0xc;
                                break;
                            }
                        }
                    }
                }
                status = 0xb;
            }
            break;
        case 0xd:
            if (ok != 0) {
                status = 0xe;
            }
            break;
    }
    if (status != 0xff) {
        code = (unsigned char) status;
        func_0206844c(self->unk_40, (u8 *) (&code), (int) tail);
    }
    func_0209526c((Hdr *) (&b));
    func_02072fac((Rec *) (&a));
}
