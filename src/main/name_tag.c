/* name_tag: 17 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208e2ac @ 0x0208e2ac, 0x18 bytes, Thumb
 * func_0208e2a4 @ 0x0208e2a4, 0x8 bytes, Thumb
 * func_0208e29c @ 0x0208e29c, 0x6 bytes, Thumb
 * func_0208e290 @ 0x0208e290, 0xc bytes, Thumb
 * func_0208e278 @ 0x0208e278, 0x18 bytes, Thumb
 * func_0208e260 @ 0x0208e260, 0x18 bytes, Thumb
 * func_0208e24c @ 0x0208e24c, 0x14 bytes, Thumb
 * func_0208e240 @ 0x0208e240, 0xa bytes, Thumb
 * func_0208e214 @ 0x0208e214, 0x2c bytes, Thumb
 * func_0208e200 @ 0x0208e200, 0x14 bytes, Thumb
 * func_0208e1cc @ 0x0208e1cc, 0x32 bytes, Thumb
 * func_0208e1bc @ 0x0208e1bc, 0x10 bytes, Thumb
 * func_0208e1a8 @ 0x0208e1a8, 0x14 bytes, Thumb
 * func_0208e19c @ 0x0208e19c, 0xc bytes, Thumb
 * func_0208e174 @ 0x0208e174, 0x26 bytes, Thumb
 * func_0208e144 @ 0x0208e144, 0x30 bytes, Thumb
 * func_0208e0dc @ 0x0208e0dc, 0x66 bytes, Thumb
 */

typedef struct {
    char pad_00[0xC];
    int unk_0C;
    int unk_10;
} UnkStruct_0208e2ac;

typedef struct {
    unsigned char pad_00[0x70];
    int unk_70;
    unsigned char pad_74[8];
    unsigned char unk_7C;
} UnkStruct_0208e240;

typedef struct {
    unsigned char pad_00[0xc];
    int unk_0C;
    unsigned char pad_10[0x64];
    int unk_74;
} UnkStruct_0208e214;

typedef struct {
    char pad_00[0x70];
    int unk_70;
    char pad_74[4];
    int unk_78;
    unsigned char unk_7C;
} UnkStruct_0208e1bc;

typedef struct {
    char pad_00[0x74];
    int unk_74;
} UnkStruct_0208e1a8;

struct UnkStruct_0208e19c {
    char pad_00[0x70];
    int unk_70;
    char pad_74[0x8];
    unsigned char unk_7C;
};

struct UnkStruct_0208e174;

struct UnkStruct_0208e174 {
    char pad_00[0x30];
    int unk_30;
    char pad_34[0x44];
    int unk_78;
};

typedef struct {
    char data[8];
} DataElem;

typedef struct {
    char pad_00[0x10];
    int unk_10;
    char unk_14;
} UnkStruct_0208e144;

struct UnkStruct_0208e0dc {
    char c;
};

struct UnkStruct_0208e0dc_2 {
    int unk_00;
    int unk_04;
};

struct UnkStruct_0208e0dc_3;

typedef unsigned int (*InnerFunc)(struct UnkStruct_0208e0dc_3 *);

struct UnkStruct_0208e0dc_3 {
    InnerFunc *funcs;
    char pad_04[0x30 - 4];
    unsigned int unk_30;
};

struct UnkStruct_0208e0dc_4 {
    char pad_00[0x0c];
    void *unk_0C;
    char pad_10[0x14 - 0x10];
    struct UnkStruct_0208e0dc y;
    char pad_after_y[0x34 - (0x14 + sizeof(struct UnkStruct_0208e0dc))];
    int unk_34;
    char pad_after_34[0x6c - (0x34 + 4)];
    struct UnkStruct_0208e0dc_3 *unk_6C;
};

extern int data_020d0ac8[];
extern void func_0208e044(void *);
extern void *func_020a8bb8(char *ptr, char *);
extern unsigned char data_020d0adc[];
extern void GX_LoadOBJPltt(void *dst, int size, int value);
extern void func_0208e05c(UnkStruct_0208e214 *);
extern void func_0208a1f0(void *a, void *b);
extern void func_0208a1ec(void *a, int b);
extern void *func_0208a1e8(void *a, int b);
extern DataElem data_020d5b3c[];
extern struct UnkStruct_0208e0dc_2 *func_0208a1c8(struct UnkStruct_0208e0dc *);
extern void *func_0208a1e0(struct UnkStruct_0208e0dc *, int, int);

void func_0208e200(void *r0);
void func_0208e1bc(UnkStruct_0208e1bc *obj);
void func_0208e19c(struct UnkStruct_0208e19c *s);
void func_0208e144(UnkStruct_0208e144 *p);
void func_0208e0dc(struct UnkStruct_0208e0dc_4 *self);

void func_0208e2ac(UnkStruct_0208e2ac *a, int index)
{
    int val;

    a->unk_0C = index;
    val = data_020d0ac8[index];
    a->unk_10 = val;
    func_0208e144((UnkStruct_0208e144 *) a);
}

void func_0208e2a4(void *argument0)
{
    func_0208e044((void *) argument0);
}

void func_0208e29c(int *p, int a, int b)
{
    p[10] = a;
    p[11] = b;
}

void *func_0208e290(char *ptr, char *argument1)
{
    return func_020a8bb8(ptr + 0x38, (char *) argument1);
}

int func_0208e278(void *arg0)
{
    int r2;
    int r1;

    r1 = *(int *) ((char *) arg0 + 0x70);
    if (r1 == 0) {
        r2 = 1;
    } else {
        r2 = 0;
    }
    if (r2 != 0) {
        *(int *) ((char *) arg0 + 0x74) = 2;
    }
    return r2;
}

void *func_0208e260(void *r0)
{
    int r1;
    int r2;

    r1 = *(int *) ((char *) r0 + 0x70);
    if (r1 != 0) {
        r2 = 1;
    } else {
        r2 = 0;
    }
    if (r2 != 0) {
        *(int *) ((char *) r0 + 0x74) = 0;
    }
    return (void *) r2;
}

void func_0208e24c(void)
{
    GX_LoadOBJPltt(data_020d0adc, 0xbc, 2);
}

void func_0208e240(UnkStruct_0208e240 *p)
{
    p->unk_70 = 0;
    p->unk_7C = 0;
}

void func_0208e214(UnkStruct_0208e214 *s)
{
    if (s->unk_74 != 0) {
        if (s->unk_0C == 4) {
            func_0208e24c();
        }
        func_0208e05c(s);
        func_0208e0dc((struct UnkStruct_0208e0dc_4 *) s);
        func_0208e200((void *) s);
    }
}

void func_0208e200(void *r0)
{
    unsigned char *r1;
    unsigned int *r0_32;
    unsigned int *r1_32;

    r0_32 = (unsigned int *) r0;
    r0_32[0x1C] = 1; // offset 0x70
    r1 = (unsigned char *) r0 + 0x7C;
    *r1 = 1;
    r1_32 = (unsigned int *) r0;
    r1_32[0x1E] = 3; // offset 0x78
    r1_32[0x0C] = 5; // offset 0x30
}

void func_0208e1cc(void *r0)
{
    if (*(int *) ((char *) r0 + 0x78) > 2) {
        *(int *) ((char *) r0 + 0x30) -= 6;
    } else {
        *(int *) ((char *) r0 + 0x30) += 2;
    }
    *(int *) ((char *) r0 + 0x78) -= 1;
    if (*(int *) ((char *) r0 + 0x78) <= 0) {
        *(int *) ((char *) r0 + 0x30) = 0;
        func_0208e1bc((UnkStruct_0208e1bc *) r0);
    }
}

void func_0208e1bc(UnkStruct_0208e1bc *obj)
{
    obj->unk_70 = 2;
    obj->unk_7C = 1;
    obj->unk_78 = 2;
}

void func_0208e1a8(UnkStruct_0208e1a8 *self)
{
    if (self->unk_74 == 0) {
        func_0208e19c((struct UnkStruct_0208e19c *) self);
    }
}

void func_0208e19c(struct UnkStruct_0208e19c *s)
{
    s->unk_70 = 3;
    s->unk_7C = 1;
}

void func_0208e174(struct UnkStruct_0208e174 *self)
{
    self->unk_30 += 0xb;
    self->unk_78 -= 1;
    if (self->unk_78 > 0) {
        return;
    }
    func_0208e044((void *) self);
    func_0208e240((UnkStruct_0208e240 *) self);
}

void func_0208e144(UnkStruct_0208e144 *p)
{
    func_0208a1f0(&p->unk_14, &data_020d5b3c[p->unk_10]);
    func_0208a1ec(&p->unk_14, 1);
    func_0208a1e8(&p->unk_14, 0);
}

void func_0208e0dc(struct UnkStruct_0208e0dc_4 *self)
{
    unsigned int r7;
    unsigned int r6;
    int r4;
    int limit;

    if (self->unk_6C == 0) {
        return;
    }
    r7 = self->unk_6C->funcs[3](self->unk_6C);
    r6 = (r7 + 7) >> 3;
    r4 = func_0208a1c8(&self->y)->unk_04 - 1;
    limit = (int) (r6 - 1);
    if (limit < 0) {
        r4 = 0;
    } else if (limit <= r4) {
        r4 = limit;
    }
    func_0208a1e0(&self->y, r4, 0);
    self->unk_6C->unk_30 = ((r6 << 3) - r7) >> 1;
    if (self->unk_0C == 0) {
        self->unk_34 = 0;
    } else {
        self->unk_34 = r4 * -4 + 0x24;
    }
}
