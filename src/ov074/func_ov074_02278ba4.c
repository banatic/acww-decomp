/* func_ov074_02278ba4 @ 0x02278ba4, 0x1a0 bytes, Thumb, module ov074
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned short v[6];
} UnkStruct_02278ba4;
typedef struct {
    unsigned short v[10];
} V10;

typedef struct Hdr {
    unsigned short a;
    UnkStruct_02278ba4 b;
    unsigned short c;
    UnkStruct_02278ba4 d;
    signed char e;
    unsigned char unk_1D;
} Hdr;

typedef struct Rec {
    unsigned short a;
    UnkStruct_02278ba4 b;
    unsigned short c;
    UnkStruct_02278ba4 d;
    signed char e;
    unsigned char unk_1D;
    V10 g;
    unsigned char h;
} Rec;

typedef struct UnkStruct_02278ba4_2 {
    char pad_00[0x1e];
    unsigned char unk_1E;
    char pad_1F[0x40 - 0x1f];
    int unk_40;
} UnkStruct_02278ba4_2;

extern int data_021f3278;
extern int data_ov074_02279d14;

extern void func_020160b4(void);
extern int func_020ab504(void);
extern void func_02088220(int *p);
extern Rec *func_02072d4c(void);
extern Hdr *func_02072ee8(Rec *r);
extern int func_020951bc(Hdr *h);
extern void func_020984e8(void);
extern Hdr *func_02099870(void);
extern int memcmp(const void *a, const void *b, unsigned long n);
extern int func_0209518c(Hdr *h, Hdr *q);
extern void func_0206844c(int a, unsigned char *p, int *t);
extern void func_0209526c(Hdr *h);
extern void func_02072fac(Rec *r);

void func_ov074_02278ba4(UnkStruct_02278ba4_2 *self)
{
    unsigned char code;
    Rec a;
    Hdr b;
    int ok;
    Hdr *q;
    Rec *r;
    Hdr *p;
    int *tail;
    int status;

    func_020160b4();
    ok = func_020ab504();
    func_02088220(&data_021f3278);
    r = func_02072d4c();
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
    tail = &data_ov074_02279d14;
    status = 0xff;
    switch (self->unk_1E) {
        case 3:
            if (ok == 0) {
                if (func_020951bc(&b) != 0) {
                    func_020984e8();
                    q = func_02099870();
                    if (b.a == q->a) {
                        if (memcmp(&b.b, &q->b, 0xc) == 0) {
                            if (func_0209518c(&b, q) != 0) {
                                status = 0xa;
                                break;
                            }
                        }
                    }
                }
                status = 9;
            } else {
                if (func_020951bc(&b) != 0) {
                    func_020984e8();
                    q = func_02099870();
                    if (b.a == q->a) {
                        if (memcmp(&b.b, &q->b, 0xc) == 0) {
                            if (func_0209518c(&b, q) != 0) {
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
        func_0206844c(self->unk_40, &code, tail);
    }
    func_0209526c(&b);
    func_02072fac(&a);
}
