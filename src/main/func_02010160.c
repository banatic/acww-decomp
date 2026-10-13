/* func_02010160 @ 0x02010160, 0x260 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02010160 {
    char pad_00[0x38c];
    char unk_38C;
    char pad_38D[0x428 - 0x38d];
    char unk_428;
    char pad_429[0x464 - 0x429];
    char unk_464;
    char pad_465[0x70c - 0x465];
    unsigned char unk_70C;
    char unk_70D;
    char unk_70E;
    char unk_70F;
    char unk_710;
    char pad_711[0x718 - 0x711];
    int unk_718;
    char pad_71C[0x73c - 0x71c];
    char unk_73C;
    char pad_73D[0x744 - 0x73d];
    int unk_744;
    char pad_748[0x7a0 - 0x748];
    char unk_7A0;
    char pad_7A1[0xc94 - 0x7a1];
    int unk_C94;
    unsigned short unk_C98;
    unsigned char unk_C9A;
    unsigned char unk_C9B;
    unsigned char unk_C9C;
} UnkStruct_02010160;

extern int func_0200f290(UnkStruct_02010160 *, int);
extern int func_02011340(UnkStruct_02010160 *);
extern void func_0205e708(int, int, unsigned short *, int *, int *);
extern int func_02011368(UnkStruct_02010160 *);
extern void func_0205e348(void *, int, int, unsigned short *, int);
extern int func_02011150(UnkStruct_02010160 *, int);
extern void func_020106a8(UnkStruct_02010160 *, int, int);
extern int func_0205e194(void *, int);
extern int func_021077e8(int);
extern int func_0205dc80(void *);
extern void func_020100d0(UnkStruct_02010160 *, int, int, void *, void *);
extern int func_0205f8b4(void *);
extern int func_0205f8a0(void *);
extern void func_020100b8(UnkStruct_02010160 *, int, int, void *, void *);
extern void func_0205e274(void *);
extern void func_0205e444(void *);
extern void func_0205e1bc(void *);
extern void func_02055454(void *);
extern void func_020554b0(void *, int);
extern int func_0205e138(void *, int);
extern void func_0205682c(void *);
extern int func_0205db38(void *);
extern void func_020e9b9c(int);
extern void func_02010c34(UnkStruct_02010160 *);
extern int func_0205d8a0(void *);
extern int func_0205d894(void *);
extern void func_0205678c(void *, int, int, int, int, int);
extern int data_020d83f8;
extern int data_020d83fc;
extern int data_020d83f0;
extern int data_020d8400;

void func_02010160(UnkStruct_02010160 *s)
{
    int d;
    unsigned short a[2];
    int b;
    int c;
    int u;
    int v;
    int w;
    int p;
    int q;

    if (s->unk_C94 != 0) {
        return;
    }
    a[0] = 0xfff1;
    if (func_0200f290(s, 0xc)) {
        a[0] = 0xfff1;
    } else {
        a[0] = s->unk_C98;
    }
    func_0205e708(func_02011340(s), s->unk_C9A, a, &c, &b);
    a[1] = s->unk_C98;
    func_0205e348(&s->unk_428, c, b, &a[1], func_02011368(s));
    func_020106a8(s, s->unk_C9B, func_02011150(s, 0));
    u = func_021077e8(func_0205e194(&s->unk_428, 0));
    v = 0;
    if (b < 0x9e) {
        v = func_021077e8(func_0205e194(&s->unk_428, 1));
    }
    if (s->unk_C9C) {
        w = func_021077e8(func_0205dc80(&s->unk_70D));
        func_020100d0(s, w, u, &data_020d83f8, &data_020d83f8);
        func_020100d0(s, w, u, &data_020d83fc, &data_020d83fc);
    }
    w = func_021077e8(func_0205f8b4(&s->unk_7A0));
    d = func_021077e8(func_0205f8a0(&s->unk_7A0));
    func_020100b8(s, w, u, &data_020d83f0, &data_020d83f0);
    func_020100b8(s, d, u, &data_020d8400, &data_020d8400);
    if (v != 0) {
        func_020100b8(s, w, v, &data_020d83f0, &data_020d83f0);
    }
    func_0205e274(&s->unk_428);
    func_0205e444(&s->unk_428);
    func_0205e1bc(&s->unk_428);
    func_02055454(&s->unk_38C);
    func_02055454(&s->unk_464);
    func_020554b0(&s->unk_38C, func_0205e194(&s->unk_428, 0));
    if (func_0205e138(&s->unk_428, 1) < 0x9e) {
        func_020554b0(&s->unk_464, func_0205e194(&s->unk_428, 1));
    }
    if (!s->unk_C9C) {
        p = ((unsigned int) s->unk_718 << 4) >> 16;
        q = ((unsigned int) s->unk_744 << 4) >> 16;
        func_0205682c(&s->unk_710);
        func_0205682c(&s->unk_73C);
        func_020e9b9c(func_0205db38(&s->unk_70F));
        func_02010c34(s);
        func_0205678c(&s->unk_710, func_0205d8a0(&s->unk_70E), p, 0, s->unk_70C, 0x1000);
        func_0205678c(&s->unk_73C, func_0205d894(&s->unk_70E), q, 0, s->unk_70C, 0x1000);
    }
    s->unk_C94 = 1;
}
