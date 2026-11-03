/* view_frustum: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0203a9b4 @ 0x0203a9b4, 0x18 bytes, Thumb
 * func_0203a9a8 @ 0x0203a9a8, 0xc bytes, Thumb
 * func_0203a970 @ 0x0203a970, 0x38 bytes, Thumb
 * func_0203a958 @ 0x0203a958, 0x18 bytes, Thumb
 * func_0203a89c @ 0x0203a89c, 0xbc bytes, Thumb
 * func_0203a7b8 @ 0x0203a7b8, 0xe4 bytes, Thumb
 */

typedef struct {
    char pad_00[0x4C];
    int unk_4C;
    int unk_50;
    int unk_54;
    unsigned short unk_58;
} UnkStruct_0203a958;

struct UnkStruct_0203a89c {
    int pad_00;
    int unk_04[3];
    int unk_10[3];
    int unk_1C[3];
    int unk_28[3];
    int pad_34[6];
    int unk_4C;
    int unk_50;
    int pad_54;
    unsigned short unk_58;
};

typedef struct Vec {
    int x;
    int y;
    int z;
} Vec;

typedef struct UnkStruct_0203a7b8 {
    int pad_00;
    int m[4][3];
    int pad_34[7];
    int low;
    int high;
} UnkStruct_0203a7b8;

extern void func_020edb3c(void *);
extern char data_020da70c[];
extern int FX_Div(int, int);
extern int FX_MulFunc(int, int);
extern void VEC_CrossProduct(int *, int *, int *);
extern void VEC_Normalize(int *, int *);
extern short FX_SinCosTable_[];
extern void MTX_MultVec43(int a, int b, Vec *c);

void func_0203a958(UnkStruct_0203a958 *self, int a1, unsigned short a2, int a3, int a4);
void func_0203a89c(struct UnkStruct_0203a89c *self);

void *func_0203a9b4(void *p)
{
    *(void **) p = &data_020da70c;
    func_020edb3c(p);
    return p;
}

void func_0203a9a8(char **p)
{
    *p = ((char *) data_020da70c);
}

void *func_0203a970(void *p)
{
    *((unsigned int *) p) = (unsigned int) ((unsigned char *) data_020da70c);
    func_0203a958((UnkStruct_0203a958 *) p, 0x00001555, 0x00000e38, 0x00001000, 0x01388000);
    return p;
}

void func_0203a958(UnkStruct_0203a958 *self, int a1, unsigned short a2, int a3, int a4)
{
    self->unk_4C = a1;
    self->unk_58 = a2;
    self->unk_50 = a3;
    self->unk_54 = a4;
    func_0203a89c((struct UnkStruct_0203a89c *) self);
}

void func_0203a89c(struct UnkStruct_0203a89c *self)
{
    int i = self->unk_58 >> 4;
    int t1 = FX_Div(FX_SinCosTable_[i * 2], FX_SinCosTable_[i * 2 + 1]);
    int t2 = FX_MulFunc(self->unk_50, t1);
    int t3 = FX_MulFunc(self->unk_4C, t2);
    int buf[12];

    buf[0] = -t3;
    buf[1] = -t2;
    buf[2] = -self->unk_50;
    buf[3] = -t3;
    buf[4] = t2;
    buf[5] = -self->unk_50;
    buf[6] = t3;
    buf[7] = t2;
    buf[8] = -self->unk_50;
    buf[9] = t3;
    buf[10] = -t2;
    buf[11] = -self->unk_50;

    VEC_CrossProduct(&buf[3], &buf[0], self->unk_04);
    VEC_CrossProduct(&buf[6], &buf[3], self->unk_10);
    VEC_CrossProduct(&buf[9], &buf[6], self->unk_1C);
    VEC_CrossProduct(&buf[0], &buf[9], self->unk_28);

    VEC_Normalize(self->unk_04, self->unk_04);
    VEC_Normalize(self->unk_10, self->unk_10);
    VEC_Normalize(self->unk_1C, self->unk_1C);
    VEC_Normalize(self->unk_28, self->unk_28);
}

int func_0203a7b8(UnkStruct_0203a7b8 *self, int a1, int a2, int threshold, Vec *vec)
{
    int s1, t1, u1;
    int s2, t2, u2;
    int s3, t3, u3;
    int s4, t4, u4;

    MTX_MultVec43(a2, a1, vec);

    if (-vec->z < self->low - threshold) {
        return 0x7fffffff;
    }
    if (-vec->z > self->high + threshold) {
        return 0x7fffffff;
    }

    s1 = FX_MulFunc(vec->z, self->m[0][2]);
    t1 = FX_MulFunc(vec->x, self->m[0][0]);
    u1 = FX_MulFunc(vec->y, self->m[0][1]);
    if (s1 + (t1 + u1) > threshold) {
        return 0x7fffffff;
    }

    s2 = FX_MulFunc(vec->z, self->m[1][2]);
    t2 = FX_MulFunc(vec->x, self->m[1][0]);
    u2 = FX_MulFunc(vec->y, self->m[1][1]);
    if (s2 + (t2 + u2) > threshold) {
        return 0x7fffffff;
    }

    s3 = FX_MulFunc(vec->z, self->m[2][2]);
    t3 = FX_MulFunc(vec->x, self->m[2][0]);
    u3 = FX_MulFunc(vec->y, self->m[2][1]);
    if (s3 + (t3 + u3) > threshold) {
        return 0x7fffffff;
    }

    s4 = FX_MulFunc(vec->z, self->m[3][2]);
    t4 = FX_MulFunc(vec->x, self->m[3][0]);
    u4 = FX_MulFunc(vec->y, self->m[3][1]);
    if (s4 + (t4 + u4) > threshold) {
        return 0x7fffffff;
    }

    return -vec->z;
}
