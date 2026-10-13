/* func_ov068_022680a4 @ 0x022680a4, 0x1b0 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec;
typedef struct {
    char pad_00[0x34];
    int unk_34;
    char pad_38[0x40 - 0x38];
} Big;

typedef struct UnkStruct_022680a4 UnkStruct_022680a4;
struct UnkStruct_022680a4 {
    char pad_00[0x1c];
    unsigned char unk_1C;
    char pad_1D[0x2c - 0x1d];
    short unk_2C;
    char pad_2E[0x30 - 0x2e];
    int unk_30;
};

typedef struct UnkStruct_022680a4_2 UnkStruct_022680a4_2;
struct UnkStruct_022680a4_2 {
    char pad_00[0x5c];
    Vec unk_5C;
    char pad_68[0x198 - 0x68];
    int unk_198;
    char pad_19C[0x334 - 0x19c];
    int unk_334;
    char pad_338[0x514 - 0x338];
    int unk_514;
    char pad_518[0x564 - 0x518];
    int unk_564;
    char pad_568[0x9b4 - 0x568];
    int unk_9B4;
    char pad_9B8[0xa00 - 0x9b8];
    int unk_A00;
    unsigned char unk_A04;
};

#define IN(v, lo, hi) ((v) >= (lo) && (v) <= (hi))

extern unsigned short data_020c80f8;
extern int func_020164a0(int *p, int a);
extern void func_0201651c(void *p, int a);
extern void func_0202e194(UnkStruct_022680a4_2 *b);
extern void func_0209129c(int a);
extern void func_0202e118(unsigned short *p, UnkStruct_022680a4_2 *b);
extern void func_02019c20(void *p, int a, int b, int c, int d, int e);
extern void func_0201228c(void *p, int a, int b);
extern void func_02034270(Big *p, Vec *v, int a, int b);
extern void func_ov003_02220b44(int a, Vec *v);
extern void func_02091254(int a, Vec *v, int b, int c);
extern void func_0200442c(void *p, int a, int b, int c);
extern void func_0203423c(Big *p);
extern void func_02091278(int a, Vec *v, int b, int c);

void func_ov068_022680a4(UnkStruct_022680a4 *a, UnkStruct_022680a4_2 *b)
{
    unsigned short w;
    Vec v;
    Big big;
    Vec v2;
    int gh;
    unsigned int t;
    Vec *q;
    unsigned short wv;

    if (func_020164a0(&b->unk_334, 0) != 0x129) {
        return;
    }
    if (a->unk_2C != 0) {
        goto other;
    }
    func_0201651c(&b->unk_334, 0);
    func_0202e194(b);
    b->unk_A04 = 0;
    if (b->unk_A00 != -1) {
        func_0209129c(b->unk_A00);
        b->unk_A00 = -1;
    }
    func_0202e118(&w, b);
    t = 0;
    wv = w;
    if (*(volatile unsigned short *) &w >= 0x1376 && wv <= 0x1376) {
        t = 1;
    }
    if (t > 0 || IN(wv, 0x1377, 0x1377) || IN(wv, 0x1380, 0x139f) || IN(wv, 0x1374, 0x1374) || IN(wv, 0x1375, 0x1375)) {
        gh = data_020c80f8;
        func_02019c20(&b->unk_564, 1, 0x12b, 1, gh, 0);
        func_0201228c(&b->unk_9B4, gh, 0);
    } else {
        func_02019c20(&b->unk_564, 1, 0x12a, 1, data_020c80f8, 0);
    }
    q = &b->unk_5C;
    v.x = b->unk_5C.x;
    v.y = q->y;
    v.z = q->z;
    func_02034270(&big, &v, 0, 0);
    gh = big.unk_34;
    v2.x = v.x;
    v2.y = v.y;
    v2.z = v.z;
    func_ov003_02220b44(0, &v2);
    if (gh == 0x13) {
        func_02091254(0x91, &v, 0, 0);
    } else {
        func_02091254(0x90, &v, 0, 0);
    }
    func_0200442c(&b->unk_514, 0x7e9, 0x7f, 0);
    a->unk_1C = 4;
    func_0203423c(&big);
    return;
other:
    b->unk_198 = a->unk_30;
    if (b->unk_A00 != -1) {
        func_02091278(b->unk_A00, &b->unk_5C, 0, 0);
    }
}
