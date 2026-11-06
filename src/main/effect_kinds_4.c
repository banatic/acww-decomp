/* effect_kinds_4: 9 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02092898 @ 0x02092898, 0x2a bytes, Thumb
 * func_02092830 @ 0x02092830, 0x68 bytes, Thumb
 * func_020927c4 @ 0x020927c4, 0x6c bytes, Thumb
 * func_02092758 @ 0x02092758, 0x6c bytes, Thumb
 * func_02092748 @ 0x02092748, 0x10 bytes, Thumb
 * func_02092720 @ 0x02092720, 0x28 bytes, Thumb
 * func_020926f8 @ 0x020926f8, 0x28 bytes, Thumb
 * func_02092644 @ 0x02092644, 0xb4 bytes, Thumb
 * func_020925d0 @ 0x020925d0, 0x74 bytes, Thumb
 */

struct UnkStruct_02092830_2 {
    int pad_00;
    int x;
    int y;
    int z;
};

typedef struct UnkStruct_02092830_3 {
    char pad_00[0x18];
    struct UnkStruct_02092830_2 **ptr;
    char pad_1C[4];
    int mat[3];
    char pad_2C[0x10];
    short s0;
    short s1;
    short s2;
    char pad_42[0x36];
    void (*func)(struct UnkStruct_02092830_3 *a, int b);
} UnkStruct_02092830_3;

typedef struct {
    char pad_00[0x34];
    int unk_34;
    char pad_38[0xc];
} UnkStruct_020927c4;

typedef struct {
    unsigned char pad_00[0x34];
    int id;
    unsigned char pad_38[8];
} UnkStruct_02092644;

typedef struct {
    unsigned char b[4];
} Key;

typedef struct {
    int x;
    int y;
    int z;
} Vec;

typedef struct {
    int pad_00;
    int unk_04;
    int unk_08;
    int unk_0C;
} UnkStruct_020925d0;

typedef struct {
    UnkStruct_020925d0 *p;
} Mid;

typedef struct {
    char pad_00[0x18];
    Mid *unk_18;
    int pad_1C;
    int unk_20;
    int unk_24;
    int unk_28;
} UnkStruct_020925d0_2;

typedef struct {
    char pad_00[4];
    Key key;
    char pad_08[4];
    UnkStruct_020925d0_2 *unk_0C;
} UnkStruct_020925d0_3;

typedef struct {
    char pad_00[0x1c];
} UnkStruct_020925d0_4;

extern int func_020e8ed8(int, int);
extern struct UnkStruct_02092830 {
    int a;
    int b;
    int c;
    unsigned short d;
} data_021d5658;
extern signed short FX_SinCosTable_[];
extern void func_02090db0(UnkStruct_02092830_3 *ctx);
extern int func_02034270(void *ptr, int a, int b, int c);
extern int func_020b6598(void);
extern int func_02094cf8(int x, void *a, int b, int c, int d, void *e);
extern void func_0203423c(void *ptr);
extern char data_020e27a8;
extern void func_02094c38(void *a, int b, char *c);
extern char data_020d1798;
extern int func_020948b8(int, int, int, int, int, int, int, int, int);
extern int data_020e29dc[];
extern int func_020ba4e4(void);
extern int func_02094b58(int p1, int p2, int p3, int p4, int p5, char *p6);
extern char data_020e2864[];
extern char data_020e285c[];
extern UnkStruct_020925d0_4 data_021d52d8[];
extern void MI_CpuCopy8(void *dst, const void *src, unsigned int size);

void func_02092898(char *a, int b)
{
    char *p;
    short v1, v2;
    if (b == 1) {
        p = *(char **) (a + 8);
        if (p != 0) {
            v1 = *(short *) (a + 0x3c);
            v2 = *(short *) (a + 0x40);
            *(unsigned short *) (p + 0x20) = (unsigned short) func_020e8ed8(v1, v2);
            *(unsigned int *) (a + 0x78) = 0;
        }
    }
}

void func_02092830(UnkStruct_02092830_3 *ctx)
{
    unsigned short d;
    int idx2;

    d = data_021d5658.d;
    ctx->mat[0] = data_021d5658.a + (*ctx->ptr)->x;
    ctx->mat[1] = data_021d5658.b + (*ctx->ptr)->y;
    ctx->mat[2] = data_021d5658.c + (*ctx->ptr)->z;
    idx2 = (d >> 4) * 2;
    ctx->s0 = FX_SinCosTable_[idx2];
    ctx->s1 = 0;
    ctx->s2 = FX_SinCosTable_[idx2 + 1];
    func_02090db0(ctx);
    ctx->func = (void (*)(UnkStruct_02092830_3 *, int)) func_02092898;
}

int func_020927c4(void *a, int b, int c, int d)
{
    UnkStruct_020927c4 local;
    int kind;
    int msg;

    func_02034270(&local, b, 0, 0);
    kind = local.unk_34;
    msg = -1;
    if (func_020b6598() != 0 && kind == 3) {
        msg = 0x88;
    } else if (kind == 0x13) {
        msg = 0x87;
    }
    if (msg != -1) {
        msg = func_02094cf8(msg, a, b, c, d, &data_020e27a8);
        func_0203423c(&local);
        return msg;
    }
    func_0203423c(&local);
    return 3;
}

int func_02092758(int a0, int a1, int a2, int a3)
{
    int arr[17];
    int v;
    int result;

    func_02034270(arr, a1, 0, 0);
    v = arr[13];
    result = -1;
    if (func_020b6598() != 0 && v == 3) {
        result = 0x8a;
    } else if (v == 0x13) {
        result = 0x89;
    }
    if (result != -1) {
        result = func_02094cf8(result, (void *) a0, a1, a2, a3, (void *) (((int *) &data_020e27a8)));
        func_0203423c(arr);
        return result;
    } else {
        func_0203423c(arr);
        return 3;
    }
}

void func_02092748(void *a)
{
    func_02094c38(a, 0, &data_020d1798);
}

void func_02092720(int param)
{
    func_020948b8(param, 31, (int) ((unsigned int *) data_020e29dc), 29, (int) ((unsigned int *) data_020e29dc), 29,
                  (int) ((unsigned int *) data_020e29dc), -1, 0);
}

void func_020926f8(int a)
{
    func_020948b8(a, 31, (int) data_020e29dc, 29, (int) data_020e29dc, 29, (int) data_020e29dc, -1, 0);
}

int func_02092644(int a, int b, int c, int d)
{
    UnkStruct_02092644 st;
    int id;
    int result;

    func_02034270((void *) (&st), b, 0, 0);
    id = st.id;
    result = 3;

    if ((id == 0x16) || (func_020ba4e4() == 1)) {
        if (func_02094b58(0x85, a, b, c, d, data_020e2864) == 0) {
            result = 2;
        }
    } else if ((id == 3) && (func_020b6598() != 0)) {
        if (func_02094b58(0x86, a, b, c, d, data_020e285c) == 0) {
            result = 2;
        }
    } else if (id == 0x13) {
        result = func_02094cf8(0x84, (void *) a, b, c, d, 0);
    } else {
        result = func_02094cf8(0x83, (void *) a, b, c, d, 0);
    }

    func_0203423c((void *) (&st));
    return result;
}

void func_020925d0(UnkStruct_020925d0_3 *o)
{
    struct {
        Key k;
        Vec v;
    } L;
    UnkStruct_020925d0_2 *s;
    Vec *g;

    g = (Vec *) ((Vec *) &data_021d5658);
    L.k = o->key;
    L.v.x = g->x;
    L.v.y = g->y;
    L.v.z = g->z;
    s = o->unk_0C;
    s->unk_20 = L.v.x + s->unk_18->p->unk_04;
    s->unk_24 = L.v.y + s->unk_18->p->unk_08;
    s->unk_28 = L.v.z + s->unk_18->p->unk_0C;
    func_02090db0((UnkStruct_02092830_3 *) o->unk_0C);
    MI_CpuCopy8(g, &data_021d52d8[*(unsigned char *) &L], 0x1c);
}
