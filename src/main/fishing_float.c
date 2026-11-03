/* fishing_float: 14 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02060134 @ 0x02060134, 0xe0 bytes, Thumb
 * func_02060130 @ 0x02060130, 0x2 bytes, Thumb
 * func_0206012c @ 0x0206012c, 0x2 bytes, Thumb
 * func_020600bc @ 0x020600bc, 0x70 bytes, Thumb
 * func_0205fff4 @ 0x0205fff4, 0xc8 bytes, Thumb
 * func_0205fe6c @ 0x0205fe6c, 0x188 bytes, Thumb
 * func_0205fe24 @ 0x0205fe24, 0x48 bytes, Thumb
 * func_0205fd40 @ 0x0205fd40, 0xe4 bytes, Thumb
 * func_0205fd04 @ 0x0205fd04, 0x3a bytes, Thumb
 * func_0205fcc8 @ 0x0205fcc8, 0x3a bytes, Thumb
 * func_0205fca0 @ 0x0205fca0, 0x28 bytes, Thumb
 * func_0205fc3c @ 0x0205fc3c, 0x64 bytes, Thumb
 * func_0205fbc4 @ 0x0205fbc4, 0x78 bytes, Thumb
 * func_0205fb28 @ 0x0205fb28, 0x9c bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02060134_2 {
    u8 unk_00;
    int unk_04;
    u32 unk_08;
    u32 unk_0C;
    u32 unk_10;
};

struct UnkStruct_02060134_3 {
    u8 pad_00[0x24];
    u32 unk_24;
    u32 unk_28;
    u32 unk_2C;
};

struct Vec {
    u32 x, y, z;
};

struct UnkStruct_02060134 {
    u32 a, b, c;
};

typedef struct {
    unsigned char pad_00[0x08];
    int unk_08;
    unsigned char pad_0C[0x04];
    int unk_10;
    unsigned char pad_14[0x14];
    char *unk_28;
    unsigned char pad_2C[0x04];
    int unk_30;
} UnkStruct_020600bc;

typedef struct UnkStruct_0205fff4 UnkStruct_0205fff4;

struct UnkStruct_0205fff4 {
    u8 pad_00[8];
    u32 unk_08;
    int unk_0C;
    u32 unk_10;
    u32 unk_14;
    u32 unk_18;
    u32 unk_1C;
    u32 unk_20;
    u32 unk_24;
    u8 pad1[8];
    int unk_30;
    u8 pad_34[4];
    u8 unk_38;
};

typedef struct DStruct DStruct;

struct DStruct {
    u8 pad_00[0x30];
    int unk_30;
    u8 pad1[8];
    int unk_3C;
};

typedef struct {
    int a;
    int b;
    int c;
} UnkStruct_0205fe6c;

typedef struct {
    u8 pad_00[0x5c];
    UnkStruct_0205fe6c vec;
} UnkStruct_0205fe6c_2;

typedef struct {
    u8 pad_00[8];
    UnkStruct_0205fe6c pos;
    u8 pad_14[0x14];
    UnkStruct_0205fe6c_2 *unk_28;
    u8 pad_2C[8];
    int unk_34;
} UnkStruct_0205fe6c_3;

struct Vec3;

struct UnkStruct_0205fd40;

struct UnkStruct_0205fd40_2;

struct Vec3 {
    int x;
    int y;
    int z;
};

struct UnkStruct_0205fd40 {
    unsigned char pad_00[0x30];
    unsigned int flag;
    unsigned int pad_34;
    unsigned int pad_38;
    int value;
    struct Vec3 vec;
};

struct UnkStruct_0205fd40_2 {
    unsigned int pad_00[2];
    int x;
    int y;
    int z;
    unsigned int pad_14[6];
    unsigned int unk_2C;
    unsigned int pad_30;
    int unk_34;
    unsigned int pad_38;
    unsigned int unk_3C;
};

typedef struct {
    char pad_00[0x8];
    char unk_08;
    char pad_09[0x14 - 0x9];
    int unk_14;
    char unk_18;
    char pad_19[0x1c - 0x19];
    int unk_1C;
    int unk_20;
    int unk_24;
} Param;

struct UnkStruct_0205fcc8 {
    char pad_00[0x08];
    int unk_08;
    char pad_0C[0x08];
    int unk_14;
    int unk_18;
    int unk_1C;
    int unk_20;
    int unk_24;
};

typedef struct {
    char pad_00[0xc];
    int unk_0C;
} UnkStruct_0205fca0;

typedef struct {
    char pad_00[0x8e];
    short unk_8E;
} InnerStruct;

typedef struct {
    char pad_00[8];
    int unk_08;
    char pad_0C[4];
    int unk_10;
    char pad_14[20];
    InnerStruct *unk_28;
    char pad_2C[4];
    int unk_30;
} UnkStruct_0205fc3c;

struct UnkStruct_0205fbc4 {
    int unk_00;
    int unk_04;
};

extern int func_020606d4(u32 addr, u8 byte1);
extern int func_0203f7d0(void *ptr, struct Vec *vec);
extern void *func_020604f8(struct UnkStruct_02060134_2 *self);
extern void VEC_Subtract(struct UnkStruct_02060134 *a, struct Vec *b, struct UnkStruct_02060134 *c);
extern void func_020eaaa8(struct UnkStruct_02060134 *a, int b);
extern void VEC_Add(struct Vec *a, struct UnkStruct_02060134 *b, struct Vec *c);
extern int func_0203f8d0(struct Vec *a, struct Vec *b);
extern void func_020e96c8(struct UnkStruct_02060134_3 *out, u32 x, u32 y, u32 z);
extern void func_02055e7c(void *a, void *b);
extern unsigned char data_021cad80[];
extern void func_0206026c(UnkStruct_020600bc *s, int arg);
extern short FX_SinCosTable_[];
extern int FX_MulFunc(int a, int b);
extern int func_02034270(void *d, void *src, int a, int b);
extern void func_0203423c(void *d);
extern int func_020912d4(int size, void *ptr, int a, int b);
extern void func_ov003_0222a56c(void);
extern void func_020eaad0(int *dst, void *src, int n);
extern int func_020e8ed8(int a, int b);
extern int func_020ea990(UnkStruct_0205fe6c *v, UnkStruct_0205fe6c *p);
extern void func_02091278(int a, UnkStruct_0205fe6c *v, u16 *h, int d);
extern void func_0209129c(int a);
extern void *data_020ccf94;
extern int func_02073918(void *, unsigned int);
extern int func_020e8bb0(int *, int, int, int, int);

void func_0205fc3c(UnkStruct_0205fc3c *self);
void func_0205fbc4(struct UnkStruct_0205fbc4 *a, struct UnkStruct_0205fbc4 *b, int *out1, int *out2, unsigned char choice);
int func_0205fb28(int *a, int b, int *c, int *d, unsigned char flag);

void func_02060134(struct UnkStruct_02060134_2 *self, struct UnkStruct_02060134_3 *src, void *arg2)
{
    struct UnkStruct_02060134_3 local_data;
    struct Vec vec;
    struct UnkStruct_02060134 tmp;
    struct UnkStruct_02060134_3 out_data;
    void *r6;
    struct UnkStruct_02060134 *tp;
    void *p;

    if (self->unk_04 == 0) {
        return;
    }

    r6 = (void *) func_020606d4((unsigned int) data_021cad80, self->unk_00);

    local_data = *src;

    if (self->unk_04 <= 1) {
        vec.x = local_data.unk_24;
        vec.y = local_data.unk_28;
        vec.z = local_data.unk_2C;
        func_0203f7d0(&self->unk_08, &vec);
    } else {
        vec.x = self->unk_08;
        vec.y = self->unk_0C;
        vec.z = self->unk_10;
        if (self->unk_04 == 6) {
            p = func_020604f8(self);
            if (p != 0) {
                tp = (struct UnkStruct_02060134 *) ((char *) p + 0x120);
                tmp.a = tp->a;
                tmp.b = tp->b;
                tmp.c = tp->c;
                VEC_Subtract(&tmp, &vec, &tmp);
                func_020eaaa8(&tmp, 3);
                tmp.b = 0;
                VEC_Add(&vec, &tmp, &vec);
            }
        }
        func_0203f8d0(&vec, &vec);
        func_020e96c8(&out_data, vec.x, vec.y, vec.z);
        local_data = out_data;
    }

    *(struct UnkStruct_02060134_3 *) ((char *) r6 + 0x64) = local_data;
    func_02055e7c(r6, arg2);
}

void func_02060130(void) {}

void func_0206012c(void) {}

void func_020600bc(UnkStruct_020600bc *s)
{
    if (s->unk_30 < 15) {
        func_0205fc3c((UnkStruct_0205fc3c *) s);
        return;
    } else if (s->unk_30 >= 21) {
        func_0206026c(s, 1);
        return;
    } else {
        short value0;
        short v;
        int idx;
        int base;

        value0 = *((short *) (s->unk_28 + 0x8e));
        v = value0 - 0x1838;
        idx = ((unsigned short) v) >> 4;
        base = idx * 2;
        s->unk_08 += FX_MulFunc(FX_SinCosTable_[base], 1600);
        s->unk_10 += FX_MulFunc(FX_SinCosTable_[base + 1], 1600);
    }
}

void func_0205fff4(UnkStruct_0205fff4 *self)
{
    int zero = 0;
    DStruct D;
    u32 E[3];
    u32 A[3];
    u32 B[3];
    u32 C[3];

    if (self->unk_30 < 15) {
        func_0205fc3c((UnkStruct_0205fc3c *) self);
        if (self->unk_30 == 14) {
            A[0] = self->unk_1C;
            A[1] = self->unk_20;
            A[2] = self->unk_24;
            B[0] = self->unk_08;
            B[1] = self->unk_0C;
            B[2] = self->unk_10;
            func_0205fbc4((struct UnkStruct_0205fbc4 *) A, (struct UnkStruct_0205fbc4 *) B, (int *) (&self->unk_14), (int *) (&self->unk_18), zero);
        }
        return;
    } else {
        C[0] = self->unk_1C;
        C[1] = self->unk_20;
        C[2] = self->unk_24;
        func_0205fb28((int *) C, self->unk_14, (int *) (&self->unk_08), (int *) (&self->unk_18), zero);
        func_02034270(&D, &self->unk_08, 1, 1);
        if (D.unk_30 == 0) {
            goto cleanup;
        }
        {
            int val = D.unk_3C;
            if (val < self->unk_0C) {
                goto cleanup;
            }
            func_0206026c((UnkStruct_020600bc *) self, 4);
            self->unk_0C = D.unk_3C - 819;
            E[0] = self->unk_08;
            E[1] = self->unk_0C;
            E[2] = self->unk_10;
            E[1] = val;
            func_020912d4(12, E, 0, 0);
            self->unk_38 = 1;
            func_ov003_0222a56c();
        }
    cleanup:
        func_0203423c(&D);
        return;
    }
}

void func_0205fe6c(UnkStruct_0205fe6c_3 *self)
{
    u16 h;
    UnkStruct_0205fe6c v0;
    char buf[0x40];
    UnkStruct_0205fe6c v1;
    int m[4];
    UnkStruct_0205fe6c_2 *o;
    UnkStruct_0205fe6c *q;
    int t;
    int d;
    int r;
    int idx;

    o = self->unk_28;
    q = &o->vec;
    v0.a = o->vec.a;
    v0.b = q->b;
    v0.c = q->c;
    func_02034270(buf, (void *) (&self->pos), 0, 1);
    h = 0;
    if (*(int *) (buf + 0x30) != 0) {
        func_020eaad0(m, buf + 0x24, 5);
        h = (u16) func_020e8ed8(m[0], m[2]);
        VEC_Add((struct Vec *) (&self->pos), (struct UnkStruct_02060134 *) m, (struct Vec *) (&self->pos));
        t = *(int *) (buf + 0x3c);
        d = self->pos.b;
        if (d < t + 0x333) {
            if (d < t + 0x19a) {
                self->pos.b = d + 0x66;
                if (self->pos.b >= t + 0x19a) {
                    v1.a = self->pos.a;
                    v1.b = self->pos.b;
                    v1.c = self->pos.c;
                    v1.b = t;
                    func_020912d4(0xf, (void *) (&v1), 0, 0);
                }
            } else {
                self->pos.b = d + 0x66;
            }
        } else {
            self->pos.b = t + 0x30a;
        }
    }
    r = func_020ea990(&v0, &self->pos);
    if (r >= 0x8000) {
        idx = ((int) (u16) func_020e8ed8(self->pos.a - v0.a, self->pos.c - v0.c) >> 4) * 2;
        self->pos.a = v0.a + FX_MulFunc(0x7f33, FX_SinCosTable_[idx]);
        self->pos.c = v0.c + FX_MulFunc(0x7f33, FX_SinCosTable_[idx + 1]);
        if (*(int *) (buf + 0x30) != 0) {
            v1.a = self->pos.a;
            v1.b = self->pos.b;
            v1.c = self->pos.c;
            v1.b = *(int *) (buf + 0x3c);
            if (self->unk_34 == -1) {
                self->unk_34 = func_020912d4(0xe, (void *) (&v1), (int) (&h), 0);
            } else {
                func_02091278(self->unk_34, &v1, &h, 0);
            }
        }
    } else if (self->unk_34 != -1) {
        if (r < 0x7e66) {
            func_0209129c(self->unk_34);
            self->unk_34 = -1;
        } else if (*(int *) (buf + 0x30) != 0) {
            v1.a = self->pos.a;
            v1.b = self->pos.b;
            v1.c = self->pos.c;
            v1.b = *(int *) (buf + 0x3c);
            func_02091278(self->unk_34, &v1, &h, 0);
        }
    }
    func_0203423c(buf);
}

void func_0205fe24(void *arg)
{
    struct {
        char pad[0x30];
        int field_30;
        char pad2[0x8];
        int field_3c;
    } local;
    int tmp;
    int *p = (int *) arg;

    func_02034270(&local, (char *) arg + 8, 1, 1);
    if (local.field_30 != 0) {
        tmp = local.field_3c - 0x333;
        if (p[3] > tmp) {
            p[3] = p[3] - 0x19a;
        } else {
            p[3] = tmp;
        }
    }
    func_0203423c(&local);
}

void func_0205fd40(struct UnkStruct_0205fd40_2 *self)
{
    struct UnkStruct_0205fd40 data, data2;

    if (self->unk_2C == 0) {
        if (func_02073918(data_020ccf94, self->unk_3C) != 0) {
            func_0206026c((UnkStruct_020600bc *) self, 4);
            return;
        }

        func_02034270(&data, &self->x, 1, 1);

        if (data.flag != 0) {
            data.vec.x = self->x;
            data.vec.y = self->y;
            data.vec.z = self->z;
            data.vec.y = data.value;

            if (self->unk_34 == -1) {
                self->unk_34 = func_020912d4(0x11, (void *) (&data.vec), 0, 0);
            } else {
                func_02091278(self->unk_34, (UnkStruct_0205fe6c *) (&data.vec), 0, 0);
            }
        }

        func_0203423c(&data);
    } else {
        func_02034270(&data2, &self->x, 1, 1);

        if (data2.flag != 0) {
            if (self->y < (data2.value + 1229)) {
                self->y = self->y + 410;
            } else {
                self->y = data2.value + 1229;
            }

            data2.vec.x = self->x;
            data2.vec.y = self->y;
            data2.vec.z = self->z;
            data2.vec.y = data2.value;

            if (self->unk_34 == -1) {
                self->unk_34 = func_020912d4(0x11, (void *) (&data2.vec), 0, 0);
            } else {
                func_02091278(self->unk_34, (UnkStruct_0205fe6c *) (&data2.vec), 0, 0);
            }
        }

        func_0203423c(&data2);
    }
}

void func_0205fd04(Param *param)
{
    struct {
        int vec[3];
    } local;

    local.vec[0] = param->unk_1C;
    local.vec[1] = param->unk_20;
    local.vec[2] = param->unk_24;
    if (func_0205fb28(local.vec, param->unk_14, (int *) (&param->unk_08), (int *) (&param->unk_18), 1) != 0) {
        func_0206026c((UnkStruct_020600bc *) param, 1);
    }
}

void func_0205fcc8(struct UnkStruct_0205fcc8 *s)
{
    int local_array[3];
    local_array[0] = s->unk_1C;
    local_array[1] = s->unk_20;
    local_array[2] = s->unk_24;
    if (func_0205fb28(local_array, s->unk_14, &s->unk_08, &s->unk_18, 1)) {
        func_0206026c((UnkStruct_020600bc *) s, 1);
    }
}

void func_0205fca0(UnkStruct_0205fca0 *s)
{
    s->unk_0C += 0x1000;
    if (s->unk_0C >= 0x28000) {
        func_0206026c((UnkStruct_020600bc *) s, 0);
    }
}

void func_0205fc3c(UnkStruct_0205fc3c *self)
{
    int temp;
    int diff;
    int index;
    int base;
    int result;

    temp = (self->unk_30 * self->unk_30 * 0x4800) / 0xe1;
    diff = self->unk_28->unk_8E - temp;
    index = ((unsigned short) (short) diff) >> 4;
    base = index * 2;
    result = FX_MulFunc(FX_SinCosTable_[base], 0x2ee);
    self->unk_08 -= result;
    result = FX_MulFunc(FX_SinCosTable_[base + 1], 0x2ee);
    self->unk_10 -= result;
}

void func_0205fbc4(struct UnkStruct_0205fbc4 *a, struct UnkStruct_0205fbc4 *b, int *out1, int *out2, unsigned char choice)
{
    int diff;
    switch (choice) {
        case 0:
            *out1 = 0xa3;
            break;
        case 1:
        case 3:
            diff = b->unk_04 - a->unk_04;
            if (diff < 0) {
                diff = -diff;
            }
            *out1 = (diff + 0x4000) / 100;
            break;
        case 2:
            diff = b->unk_04 - a->unk_04;
            if (diff < 0) {
                diff = -diff;
            }
            *out1 = (diff + 0x8000) / 100;
            break;
    }
    *out2 = *out1 * 10;
}

int func_0205fb28(int *a, int b, int *c, int *d, unsigned char flag)
{
    int key;
    int mode;
    int alloc;
    int result1;
    int result2;
    int sum;

    if (flag) {
        key = 0xccd;
        mode = 5;
    } else {
        key = 0xccd;
        mode = 10;
    }

    alloc = 0x1000 / mode;
    result1 = func_020e8bb0(c, a[0], alloc, key, 0x19a);
    result2 = func_020e8bb0(c + 2, a[2], alloc, key, 0x19a);
    sum = result1 + result2;

    if (*d < 0 && flag) {
        func_020e8bb0(c + 1, a[1], alloc, 0xccd, 0x52);
    } else {
        c[1] += *d;
        *d -= b;
    }

    return sum == 0;
}
