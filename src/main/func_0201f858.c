/* func_0201f858 @ 0x0201f858, 0x1bc bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

typedef struct UnkStruct_0201f858 UnkStruct_0201f858;
typedef struct UnkStruct_0201f858_2 UnkStruct_0201f858_2;

typedef struct {
    void *p;
    unsigned char unk_04;
} UnkStruct_0201f858_3;

typedef struct {
    volatile unsigned short h[4];
    int w[2];
} Blk;

struct UnkStruct_0201f858 {
    char pad_00[0xc8];
    int unk_C8;
    int unk_CC;
    char pad_D0[0x30];
    struct UnkStruct_0201f858_4 {
        char pad[0x830];
        int f830;
    } *unk_100;
    int unk_104;
    char pad_108[0x1a];
    unsigned char unk_122;
    char pad_123[5];
    int unk_128;
    int unk_12C;
};

extern UnkStruct_0201f858_2 data_021f3aa4;
typedef struct {
    int unk_00;
    unsigned char unk_04;
} Cfg;
extern Cfg data_020c8bf0;
extern int data_020d90c8[];

extern int func_02020a5c(void);
extern void func_0202d8f8(UnkStruct_0201f858 *s, int *a, int *b, int c, int d);
extern void func_0208674c(volatile unsigned short *dst, UnkStruct_0201f858_2 *t);
extern void func_0209e474(int *v);
extern int func_020819bc(void);
extern int func_020867e0(UnkStruct_0201f858_2 *t);
extern unsigned char *func_020867a0(UnkStruct_0201f858_2 *t);
extern int func_02003704(void);
extern unsigned char *func_0208150c(int t);
extern int memcmp(const void *a, const void *b, int n);
extern int func_0201fc14(int k);
extern void func_02015e10(UnkStruct_0201f858 *s, unsigned char *p, int k);
extern int func_020951bc(int p);
extern void func_02015e40(UnkStruct_0201f858 *s, int p, int k);
extern int func_02086744(UnkStruct_0201f858_2 *t);
extern void func_02015fb0(UnkStruct_0201f858 *s, int a, int b, int c, int d, int e);
extern void func_02015de4(UnkStruct_0201f858 *s, Blk *b, int c, int d);
extern int func_020036e8(unsigned char *p);
extern void func_0202da38(UnkStruct_0201f858 *s, int *a, unsigned char *b, int c, int d, int e, int f, int g, int h);

void func_0201f858(UnkStruct_0201f858 *s, UnkStruct_0201f858_3 *out)
{
    Blk blk;
    int t;
    int k;
    int p2;
    unsigned char *e;
    int kind;
    UnkStruct_0201f858_2 *P;
    volatile unsigned short *q;

    if (func_02020a5c() != 0) {
        func_0202d8f8(s, &s->unk_12C, &s->unk_128, s->unk_100->f830, 0);
        return;
    }

    t = s->unk_100->f830;
    P = &data_021f3aa4;
    if (P != 0) {
        func_0208674c(&blk.h[1], P);
        q = &blk.h[1];
    } else {
        blk.h[2] = 0xfff1;
        q = &blk.h[2];
    }
    blk.h[0] = *q;

    kind = 0;
    blk.w[0] = 0;
    blk.w[1] = 0;
    func_0209e474(&blk.w[0]);
    k = ((unsigned char *) &blk)[0xa];

    if (s->unk_12C == 0 || func_020819bc() == 0) {
        kind = 0;
    } else {
        if (P != 0) {
            unsigned int ok;
            unsigned short v0;
            unsigned short v1;

            ok = 0;
            v0 = blk.h[0];
            v1 = blk.h[0];
            if (v1 >= 0x12b0 && v0 <= 0x12e7) {
                ok = 1;
            }
            if (ok != 0) {
                p2 = func_020867e0(P);
                e = func_020867a0(P);
                if (func_02003704() != 0) {
                    unsigned char *o = func_0208150c(t);
                    if (*(unsigned short *) e == *(unsigned short *) o && memcmp(e + 2, o + 2, 0xc) == 0 && e[0xf] == o[0xf]) {
                        kind = 3;
                    } else {
                        kind = func_0201fc14(k);
                    }
                    func_02015e10(s, e, 1);
                } else if (func_020951bc(p2) != 0) {
                    kind = func_0201fc14(k);
                    func_02015e40(s, func_020867e0(P), 1);
                }
                func_02015fb0(s, func_02086744(P) >> 12, 0, 3, 0, 0);
                func_02015de4(s, &blk, 0, 7);
            }
        }
    }

    func_0202da38(s, &s->unk_104, &s->unk_122, 0x1e, func_020036e8(func_0208150c(t)), data_020c8bf0.unk_00, 1, kind,
                  data_020c8bf0.unk_04);
    out->p = &s->unk_104;
    out->unk_04 = s->unk_122;
    {
        int v0 = data_020d90c8[0];
        int v1 = data_020d90c8[1];
        s->unk_C8 = v0;
        s->unk_CC = v1;
    }
}
