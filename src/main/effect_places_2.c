/* effect_places_2: 12 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02094f28 @ 0x02094f28, 0x8 bytes, Thumb
 * func_02094ef4 @ 0x02094ef4, 0x34 bytes, Thumb
 * func_02094ea0 @ 0x02094ea0, 0x54 bytes, Thumb
 * func_02094e90 @ 0x02094e90, 0x10 bytes, Thumb
 * func_02094e2c @ 0x02094e2c, 0x64 bytes, Thumb
 * func_02094e1c @ 0x02094e1c, 0x10 bytes, Thumb
 * func_02094e04 @ 0x02094e04, 0x16 bytes, Thumb
 * func_02094d6c @ 0x02094d6c, 0x98 bytes, Thumb
 * func_02094d48 @ 0x02094d48, 0x24 bytes, Thumb
 * func_02094cf8 @ 0x02094cf8, 0x50 bytes, Thumb
 * func_02094ce4 @ 0x02094ce4, 0x14 bytes, Thumb
 * func_02094c8c @ 0x02094c8c, 0x58 bytes, Thumb
 */

typedef struct {
    int x, y, z;
    unsigned short idx;
} EmitSrc;

typedef struct {
    void *pad_00;
    int x, y, z;
} QVec;

typedef struct {
    QVec *q;
} UnkStruct_02094ea0;

typedef struct {
    unsigned char pad_00[0x18];
    UnkStruct_02094ea0 *base;
    unsigned char pad_1C[0x20 - 0x1c];
    int wx, wy, wz;
    unsigned char pad_2C[0x3c - 0x2c];
    short sinv;
    short zero;
    short cosv;
} UnkStruct_02094ea0_2;

typedef struct {
    int unk_00;
    int v1;
    int v2;
    short angle;
} In;

typedef struct {
    int *arr;
} UnkStruct_02094e2c;

typedef struct {
    char pad_00[0x18];
    UnkStruct_02094e2c *inner;
    char pad_1C[0x04];
    int pos[3];
    char pad_2C[0x10];
    short s1;
    short s2;
    short s3;
} UnkStruct_02094e2c_2;

typedef struct Vec {
    int x, y, z, w;
} Vec;

typedef struct Input {
    int a[3];
    short b;
} Input;

typedef struct UnkStruct_02094d6c {
    char pad_00[0x18];
    Vec **obj;
    char pad_1C[0x04];
    int unk_20;
    int unk_24;
    int unk_28;
    char pad_2C[0x10];
    short unk_3C;
    short unk_3E;
    short unk_40;
} UnkStruct_02094d6c;

typedef struct {
    char pad_00[0xE];
    short unk_0E;
    char pad_10[0x4];
    int unk_14;
    char pad_18[0x4];
} Entry;

typedef struct {
    unsigned char b[4];
} Key;

extern void func_02090db0(void *);
extern unsigned char data_021d5658[];
extern short FX_SinCosTable_[];
extern void func_020ea6e0(int *v, int s);
extern void VEC_Add(int *a, int *b, int *c);
extern int func_020ea838(int *v);
extern int data_020e29fc;
extern void func_02091494(int, int, int, int, int, int, int);
extern int func_02090c2c(int, int, int, int);
extern char data_021d52d8[];
extern void func_020913c8(void *p, int a, int b);
extern void func_020914dc(Entry *);

void func_02094f28(void *argument0)
{
    func_02090db0((void *) argument0);
}

void func_02094ef4(void *arg0)
{
    unsigned int *puVar1;
    unsigned int *puVar2;
    unsigned int val;
    unsigned int val2;
    unsigned int val3;
    unsigned int *puVar6;

    puVar6 = (unsigned int *) data_021d5658;
    val = *puVar6;
    puVar1 = *(unsigned int **) ((int) arg0 + 0x18);
    val2 = *(unsigned int *) (*puVar1 + 4);
    *(unsigned int *) ((int) arg0 + 0x20) = val + val2;
    val = *(puVar6 + 1);
    puVar1 = *(unsigned int **) ((int) arg0 + 0x18);
    val2 = *(unsigned int *) (*puVar1 + 8);
    *(unsigned int *) ((int) arg0 + 0x24) = val + val2;
    val = *(puVar6 + 2);
    puVar1 = *(unsigned int **) ((int) arg0 + 0x18);
    val2 = *(unsigned int *) (*puVar1 + 0xc);
    *(unsigned int *) ((int) arg0 + 0x28) = val + val2;
    func_02090db0(arg0);
    return;
}

void func_02094ea0(UnkStruct_02094ea0_2 *self, EmitSrc *src)
{
    unsigned short idx = src->idx;
    int idx2;

    self->wx = src->x + self->base->q->x;
    self->wy = src->y + self->base->q->y;
    self->wz = src->z + self->base->q->z;
    idx2 = (idx >> 4) << 1;
    self->sinv = FX_SinCosTable_[idx2];
    self->zero = 0;
    self->cosv = FX_SinCosTable_[idx2 + 1];
    func_02090db0((void *) self);
}

void func_02094e90(int a)
{
    func_02094ea0((UnkStruct_02094ea0_2 *) a, (EmitSrc *) ((void *) data_021d5658));
}

void func_02094e2c(UnkStruct_02094e2c_2 *out, In *in)
{
    short t;
    unsigned short x;
    t = (short) (in->angle + 0x8000);
    out->pos[0] = in->unk_00 + out->inner->arr[1];
    out->pos[1] = in->v1 + out->inner->arr[2];
    out->pos[2] = in->v2 + out->inner->arr[3];
    x = (unsigned short) t;
    out->s1 = FX_SinCosTable_[(x >> 4) * 2];
    out->s2 = 0;
    out->s3 = FX_SinCosTable_[(x >> 4) * 2 + 1];
    func_02090db0(out);
}

void func_02094e1c(int arg0)
{
    func_02094e2c((UnkStruct_02094e2c_2 *) arg0, (In *) ((void *) data_021d5658));
}

void func_02094e04(void *arg0, int arg1)
{
    func_02094ef4(arg0);
    *(int *) ((char *) arg0 + 0x54) = arg1;
}

void func_02094d6c(UnkStruct_02094d6c *self, Input *in, int *v2, int *v3)
{
    int src[3];
    int copy[3];
    int cand[3];

    src[0] = in->a[0];
    src[1] = in->a[1];
    src[2] = in->a[2];

    if (v2) {
        copy[0] = v2[0];
        copy[1] = v2[1];
        copy[2] = v2[2];
        func_020ea6e0(copy, in->b);
        VEC_Add(src, copy, src);
    }

    self->unk_20 = src[0] + (*self->obj)->y;
    self->unk_24 = src[1] + (*self->obj)->z;
    self->unk_28 = src[2] + (*self->obj)->w;

    if (v3) {
        cand[0] = v3[0];
        cand[1] = v3[1];
        cand[2] = v3[2];
        func_020ea6e0(cand, in->b);
        if (func_020ea838(cand) != 0) {
            int c1 = cand[1];
            int c2 = cand[2];
            int c0 = cand[0];
            self->unk_3C = (short) c0;
            self->unk_3E = (short) c1;
            self->unk_40 = (short) c2;
        }
    }
}

void func_02094d48(unsigned int a, unsigned int b, unsigned int c)
{
    func_02094d6c((UnkStruct_02094d6c *) a, (Input *) (((unsigned int *) data_021d5658)), (int *) b, (int *) c);
    func_02090db0((void *) a);
}

int func_02094cf8(int a0, int a1, int a2, int a3, int a4, int a5)
{
    int saved_a0 = a0;
    int saved_a1 = a1;
    int r4 = a5;
    int result;
    if (r4 == 0) {
        r4 = (int) &data_020e29fc;
    }
    result = 3;
    func_02091494((int) ((int *) data_021d5658), -1, saved_a1, a2, a3, a4, -1);
    if (func_02090c2c(saved_a0, a2, a3, r4) != 0) {
        result = 1;
    }
    return result;
}

void func_02094ce4(int a)
{
    func_020913c8(data_021d52d8, a, 0);
}

int func_02094c8c(unsigned char *param)
{
    Key tmp;
    Entry *e;
    int flag;

    tmp = *(Key *) (param + 4);
    e = &((Entry *) data_021d52d8)[tmp.b[0]];
    flag = 0;
    if (e->unk_14 != -1) {
        if (e->unk_0E != 0) {
            if (e->unk_0E > 0) {
                e->unk_0E--;
            }
            flag = 1;
        }
    }

    if (flag == 0) {
        func_020914dc(e);
    }
    return flag;
}
