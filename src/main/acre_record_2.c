/* acre_record_2: 10 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02037f5c @ 0x02037f5c, 0x16 bytes, Thumb
 * func_02037f28 @ 0x02037f28, 0x34 bytes, Thumb
 * func_02037eec @ 0x02037eec, 0x3c bytes, Thumb
 * func_02037ecc @ 0x02037ecc, 0x20 bytes, Thumb
 * func_02037e90 @ 0x02037e90, 0x3c bytes, Thumb
 * func_02037e8c @ 0x02037e8c, 0x4 bytes, Thumb
 * func_02037e88 @ 0x02037e88, 0x4 bytes, Thumb
 * func_02037e84 @ 0x02037e84, 0x4 bytes, Thumb
 * func_02037e70 @ 0x02037e70, 0x12 bytes, Thumb
 * func_02037e44 @ 0x02037e44, 0x2c bytes, Thumb
 */

typedef struct UnkStruct_02037f5c UnkStruct_02037f5c;

struct UnkStruct_02037f5c {
    int unk_00;
    int unk_04;
    int unk_08;
    char pad_0C[12];
    int arr[2];
};

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1C;
    int unk_20;
    int unk_24;
} DST;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
} SRC;

struct Src3 {
    int x;
    int y;
    int z;
};

struct Src2 {
    int a;
    int b;
};

struct UnkStruct_02037eec {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    int x;
    int y;
    int z;
};

typedef struct UnkStruct_02037ecc {
    unsigned char pad_00[0xc];
    int unk_0C;
} UnkStruct_02037ecc;

typedef struct {
    unsigned char pad_00[4];
    int unk_04;
    int unk_08;
    unsigned char pad_0C[0x14];
    UnkStruct_02037ecc *unk_20;
} UnkStruct_02037ecc_2;

extern int func_02030c84(int a, int b, int c, int d);
extern void *func_020e9968(int, int, int);
extern int func_0209d048(int);
extern __arm void *func_02037e0c(void *a, void *b, void *c, unsigned char d);

void func_02037ecc(UnkStruct_02037ecc_2 *p, UnkStruct_02037ecc *v, int flag, int d);

void func_02037f5c(UnkStruct_02037f5c *p)
{
    int i = 0;
    p->unk_04 = 0;
    p->unk_08 = 0;
    for (; i < 2; i++) {
        p->arr[i] = 0;
    }
}

void func_02037f28(DST *dst, int p1, SRC *src, int p4, int p5, int p6, int p7, int p8, int p9, int p10, int p11)
{
    dst->unk_00 = p1;
    dst->unk_0C = src->unk_00;
    dst->unk_10 = src->unk_04;
    dst->unk_14 = src->unk_08;
    dst->unk_18 = p4;
    dst->unk_1C = p5;
    dst->unk_24 = p6;
    dst->unk_04 = p9;
    dst->unk_08 = p10;
    func_02037ecc((UnkStruct_02037ecc_2 *) dst, (UnkStruct_02037ecc *) p7, p8, p11);
}

void func_02037eec(int a, int b, struct Src3 *s, int d, int t0, int t1, int t2, int t3, struct Src2 *p, int t4)
{
    struct Src3 local;

    local.x = s->x;
    local.y = s->y;
    local.z = s->z;

    func_02037f28((DST *) a, b, (SRC *) (&local), d, t0, t1, t2, t3, p->a, p->b, t4);
}

void func_02037ecc(UnkStruct_02037ecc_2 *p, UnkStruct_02037ecc *v, int flag, int d)
{
    p->unk_20 = v;
    if (p->unk_20 != 0) {
        flag = p->unk_20->unk_0C;
    }
    if (flag != 0) {
        func_02030c84(p->unk_04, p->unk_08, flag, d);
    }
}

void *func_02037e90(int count, int arg2, int arg3)
{
    char *base = func_020e9968(arg2, count * 40, arg3);
    int i;

    if (base) {
        for (i = 0; i < count; i++) {
            if (base + i * 40) {
                func_02037f5c((UnkStruct_02037f5c *) (base + i * 40));
            }
        }
    }
    return base;
}

int func_02037e8c(int p0)
{
    return ((int) (p0) + (4));
}

void func_02037e88(int *p0, int p1)
{
    p0[0] = p1;
}

int func_02037e84(int *p0)
{
    return p0[0];
}

int func_02037e70(int *argument0)
{
    return func_0209d048((int) func_02037e84((int *) argument0));
}

int func_02037e44(void *a, unsigned short *b, void *c, void *d, unsigned char e)
{
    void *p = func_02037e0c(a, c, d, e);
    int ret = 0;
    if (p) {
        *(unsigned short *) p = *b;
        ret = 1;
    }
    return ret;
}
