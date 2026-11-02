/* staff_roll_screen: 17 functions, module ov093
 * mwccarm 1.2/base -O4,s
 * func_ov093_022990b8 @ 0x022990b8, 0x30 bytes, Thumb
 * func_ov093_02299090 @ 0x02299090, 0x28 bytes, Thumb
 * func_ov093_02299048 @ 0x02299048, 0x48 bytes, Thumb
 * func_ov093_02298fdc @ 0x02298fdc, 0x6c bytes, Thumb
 * func_ov093_02298fd8 @ 0x02298fd8, 0x2 bytes, Thumb
 * func_ov093_02298fd4 @ 0x02298fd4, 0x2 bytes, Thumb
 * func_ov093_02298fbc @ 0x02298fbc, 0x18 bytes, Thumb
 * func_ov093_02298fac @ 0x02298fac, 0x10 bytes, Thumb
 * func_ov093_02298fa4 @ 0x02298fa4, 0x8 bytes, Thumb
 * func_ov093_02298f9c @ 0x02298f9c, 0x8 bytes, Thumb
 * func_ov093_02298f8c @ 0x02298f8c, 0x10 bytes, Thumb
 * func_ov093_02298f84 @ 0x02298f84, 0x8 bytes, Thumb
 * func_ov093_02298f64 @ 0x02298f64, 0x20 bytes, Thumb
 * func_ov093_02298f4c @ 0x02298f4c, 0x18 bytes, Thumb
 * func_ov093_02298f2c @ 0x02298f2c, 0x20 bytes, Thumb
 * func_ov093_02298f24 @ 0x02298f24, 0x8 bytes, Thumb
 * func_ov093_02298f20 @ 0x02298f20, 0x4 bytes, Thumb
 */

typedef struct {
    char pad_00[4];
    unsigned char unk_04;
    char pad_05[0x19e0 - 5];
    char arr[26][0x6c];
} UnkStruct_02299090;

struct UnkStruct_02299048 {
    char data[0x6c];
};

struct UnkStruct_02299048_2 {
    char data[0x24];
};

struct UnkStruct_02299048_3 {
    unsigned int unk_00;
    unsigned char flag;
    unsigned char pad_05[0x19e0 - 5];
    struct UnkStruct_02299048 arr1[26];
    struct UnkStruct_02299048_2 arr2[2];
};

struct UnkStruct_02298fbc {
    short unk_00;
    short unk_02;
    char unk_04;
    char unk_05;
    char unk_06;
};

typedef struct {
    char pad_00[5];
    unsigned char unk_05;
} UnkStruct_02298fac;

struct UnkStruct_02298f2c {
    void *vtable;
};

extern void func_ov093_022993c0(void *param1, int param2, int param3);
extern void func_02070b84(void *ptr);
extern void func_020b9ccc(void *ptr);
extern int func_02002ca4(int a, int b, int c);
extern int func_02002c6c(int a, int b, int c, int d, int e, int f);
extern int data_021fbe94;
extern int data_ov093_02299884;
extern unsigned char data_ov093_022998c8[];
extern unsigned char data_ov093_022998dc[];
extern unsigned char data_ov093_022998f4[];
extern void *func_020a8cac(void *p);
extern void func_020a8c1c(void *p);
extern int data_ov093_022998b8;
extern void *func_020a8c38(void *);
extern void func_020edb3c(struct UnkStruct_02298f2c *p);

void func_ov093_02298fa4(unsigned char *p0, int p1);

void func_ov093_022990b8(void *param0, int param1)
{
    int temp;
    int val;

    val = *(int *) ((char *) param0 + 8) + *(int *) ((char *) param0 + 0x10);
    *(int *) ((char *) param0 + 8) = val;
    temp = *(int *) ((char *) param0 + 8) >> 12;

    func_ov093_022993c0(param0, 4, temp - 0xc0);

    if (param1 != 0) {
        func_ov093_022993c0(param0, 0, temp);
    }
}

void *func_ov093_02299090(UnkStruct_02299090 *obj)
{
    if (obj->unk_04 >= 26) {
        return &obj->arr[25];
    } else {
        obj->unk_04++;
        return &obj->arr[obj->unk_04 - 1];
    }
}

void func_ov093_02299048(struct UnkStruct_02299048_3 *self)
{
    int i;
    self->flag = 0;
    for (i = 0; i < 26; i++) {
        func_02070b84(&self->arr1[i]);
    }
    for (i = 0; i < 2; i++) {
        func_020b9ccc(&self->arr2[i]);
    }
}

void func_ov093_02298fdc(void *self)
{
    int r4 = data_021fbe94;
    func_02002ca4((unsigned int) data_ov093_022998c8, r4, 0);
    func_02002c6c(data_ov093_02299884, r4, 0, 0x10, 0x10, 0x78);
    func_02002c6c((unsigned int) data_ov093_022998dc, r4, 0, 0x79, 0x79, 0xf0);
    func_02002c6c((unsigned int) data_ov093_022998f4, r4, 0, 0xf1, 0xf1, 0x15f);
}

void func_ov093_02298fd8(void *object) {}

void func_ov093_02298fd4(void *object) {}

void func_ov093_02298fbc(struct UnkStruct_02298fbc *s)
{
    s->unk_00 = -1;
    s->unk_02 = -1;
    s->unk_05 = 0;
    s->unk_06 = 0;
    func_ov093_02298fa4((unsigned char *) s, 3);
}

int func_ov093_02298fac(UnkStruct_02298fac *p, int mask)
{
    if (p->unk_05 & mask) {
        return 1;
    }
    return 0;
}

void func_ov093_02298fa4(unsigned char *p0, int p1)
{
    p0[5] = (p0[5] | p1);
}

void func_ov093_02298f9c(unsigned char *p, unsigned char m)
{
    p[5] &= ~m;
}

int func_ov093_02298f8c(unsigned short *ptr, unsigned short mask)
{
    if ((*ptr & mask) != 0) {
        return 1;
    } else {
        return 0;
    }
}

void func_ov093_02298f84(unsigned short *p0, int p1)
{
    p0[0] = (p0[0] | p1);
}

void *func_ov093_02298f64(void **p)
{
    func_020a8cac(p);
    *p = &data_ov093_022998b8;
    func_020a8c1c(p);
    return p;
}

void *func_ov093_02298f4c(void *p)
{
    *(void **) p = ((char *) &data_ov093_022998b8);
    func_020a8c38(p);
    return p;
}

struct UnkStruct_02298f2c *func_ov093_02298f2c(struct UnkStruct_02298f2c *p)
{
    p->vtable = ((char *) &data_ov093_022998b8);
    func_020a8c38((void *) p);
    func_020edb3c(p);
    return p;
}

int func_ov093_02298f24(void)
{
    return 422;
}

int func_ov093_02298f20(int p0)
{
    return ((int) (p0) + (18));
}
