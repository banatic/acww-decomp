/* head_look_2: 20 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0205e700 @ 0x0205e700, 0x8 bytes, Thumb
 * func_0205e6f8 @ 0x0205e6f8, 0x8 bytes, Thumb
 * func_0205e6f4 @ 0x0205e6f4, 0x4 bytes, Thumb
 * func_0205e6f0 @ 0x0205e6f0, 0x4 bytes, Thumb
 * func_0205e678 @ 0x0205e678, 0x78 bytes, Thumb
 * func_0205e65c @ 0x0205e65c, 0x1c bytes, Thumb
 * func_0205e5ec @ 0x0205e5ec, 0x70 bytes, Thumb
 * func_0205e568 @ 0x0205e568, 0x84 bytes, Thumb
 * func_0205e560 @ 0x0205e560, 0x6 bytes, Thumb
 * func_0205e54c @ 0x0205e54c, 0x14 bytes, Thumb
 * func_0205e538 @ 0x0205e538, 0x14 bytes, Thumb
 * func_0205e528 @ 0x0205e528, 0x10 bytes, Thumb
 * func_0205e518 @ 0x0205e518, 0x10 bytes, Thumb
 * func_0205e508 @ 0x0205e508, 0x10 bytes, Thumb
 * func_0205e4f8 @ 0x0205e4f8, 0x10 bytes, Thumb
 * func_0205e4f0 @ 0x0205e4f0, 0x6 bytes, Thumb
 * func_0205e4ec @ 0x0205e4ec, 0x2 bytes, Thumb
 * func_0205e4e8 @ 0x0205e4e8, 0x4 bytes, Thumb
 * func_0205e4b0 @ 0x0205e4b0, 0x36 bytes, Thumb
 * func_0205e444 @ 0x0205e444, 0x6c bytes, Thumb
 */

struct SubElem {
    char data[0x1c];
};

struct Pair8 {
    int a;
    int b;
};

struct UnkStruct_0205e678 {
    int arr[4];               // 0x00
    char pad_10[0xb0 - 0x10]; // 0x10
    struct SubElem sub[8];    // 0xb0
    struct Pair8 p8[4];       // 0x190
    unsigned char p2[4][2];   // 0x1b0
};

typedef struct {
    char pad_00[40];
} Elem;

typedef struct {
    int arr[4];
    Elem elems[8];
} UnkStruct_0205e5ec;

typedef struct {
    unsigned char data[0x14];
    unsigned char sub[0x14];
} Elem_0205e568;

typedef struct {
    unsigned int a;
    unsigned int b;
} Pair;

typedef struct {
    unsigned int arr0[4];
    Elem_0205e568 arr[4];
    unsigned char pad_B0[0x190 - (0x10 + 4 * 0x28)];
    Pair arr2[4];
    unsigned char bytes[8];
} UnkStruct_0205e568;

typedef struct {
    unsigned long a[64];
} UnkStruct_0205e560;

typedef struct {
    unsigned char unk_00;
} UnkStruct_0205e4f0;

struct RetStruct {
    unsigned char pad_00[13];
    unsigned char unk_0D;
};

extern void func_02055ce8(void *);
extern void *func_02055cf4(void *);
extern void *func_020ba01c(void *ptr);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern unsigned char *data_020ccf94;
extern void *data_021c9ae4;
extern int func_02055c80(void *dst, int a, int b, int c);
extern int func_020e9968(void *a, int b, int c);
extern void func_02055b40(void *p);
extern void func_020e9b9c(void *);
extern void func_0205e174(void *param, int param2, int param3);
extern void func_0205e118(void *param, int param2, int param3);
extern struct RetStruct *func_0205e14c(void *p, int n);
extern void func_020b9ec4(struct RetStruct *);
extern void func_020ba004(struct RetStruct *);

void func_0205e444(void *p);

int func_0205e700(void)
{
    return 10340;
}

int func_0205e6f8(void)
{
    return 4640;
}

int func_0205e6f4(void)
{
    return 0;
}

int func_0205e6f0(void)
{
    return 192;
}

struct UnkStruct_0205e678 *func_0205e678(struct UnkStruct_0205e678 *self)
{
    struct SubElem *p, *end;
    int i;

    __cxa_vec_ctor((void *) ((char *) self + 0x10), 8, 0x14, (((void (*)(void *)) func_02055cf4)),
                   (void (*)(void *)) func_02055ce8);

    p = &self->sub[0];
    end = &self->sub[8];
    do {
        func_020ba01c(p);
        p++;
    } while (p != end);

    for (i = 0; i < 4; i++) {
        self->arr[i] = 0;
        self->p8[i].a = 0;
        self->p8[i].b = 0;
        self->p2[i][0] = 0x9e;
        self->p2[i][1] = 0x9e;
    }

    return self;
}

void *func_0205e65c(void *p)
{
    __cxa_vec_cleanup((void *) ((void *) ((char *) p + 0x10)), 8, 0x14, (void (*)(void *)) func_02055ce8);
    return p;
}

void func_0205e5ec(UnkStruct_0205e5ec *obj)
{
    unsigned int count;
    unsigned int i;
    int v1;
    int v2;
    int v3;
    void *base;

    count = data_020ccf94[0x6c];

    for (i = 0; i < count; i++) {
        v1 = func_0205e6f8();
        v2 = func_0205e6f4();
        v3 = func_0205e6f0();
        func_02055c80(&obj->elems[i], v1, v2, v3);
    }

    base = data_021c9ae4;
    for (i = 0; i < count; i++) {
        obj->arr[i] = func_020e9968(base, func_0205e700(), 4);
    }
}

void func_0205e568(UnkStruct_0205e568 *obj)
{
    void *condition_value0;
    int i;

    for (i = 0; i < 4; i++) {
        func_02055b40(&obj->arr[i]);
        func_02055b40(obj->arr[i].sub);
    }

    for (i = 0; i < 4; i++) {
        obj->arr0[i] = 0;
        obj->arr2[i].a = 0;
        obj->arr2[i].b = 0;
    }

    if ((condition_value0 = (void *) ((*(int *) &data_021c9ae4)))) {
        func_020e9b9c(condition_value0);
    }

    for (i = 0; i < 4; i++) {
        unsigned char *base = (unsigned char *) obj + 2 * i;
        base[0x1b0] = 0x9e;
        base[0x1b1] = 0x9e;
    }
}

unsigned long func_0205e560(UnkStruct_0205e560 *p, int i)
{
    return p->a[i];
}

int func_0205e54c(char *base, int a, int b)
{
    char *p = base + (a << 3);
    p += (b << 2);
    return *(int *) (p + 0x190);
}

void func_0205e538(char *base, int i, int j, int val)
{
    char *p;
    p = base + (i << 3);
    p += (j << 2);
    *((int *) (p + 0x190)) = val;
}

void *func_0205e528(void *r0, int r1, int r2)
{
    return (void *) ((char *) r0 + 0x10 + 0x28 * r1 + 0x14 * r2);
}

void *func_0205e518(void *arg0, int arg1, int arg2)
{
    return (void *) ((char *) arg0 + 0xb0 + 0x38 * arg1 + 0x1c * arg2);
}

unsigned char func_0205e508(unsigned char *ptr, int a, int b)
{
    return (ptr + a * 2 + b)[0x1b0];
}

void func_0205e4f8(unsigned char *p, int a, int b, unsigned char v)
{
    *(p + (a * 2) + b + 0x1b0) = v;
}

void func_0205e4f0(UnkStruct_0205e4f0 *p)
{
    p->unk_00 = 4;
}

void func_0205e4ec(void *object) {}

void func_0205e4e8(unsigned char *p0, int p1)
{
    p0[0] = p1;
}

void func_0205e4b0(void *param)
{
    func_0205e444(param);
    func_0205e174(param, 0, 0);
    func_0205e174(param, 1, 0);
    func_0205e118(param, 0, 0x9e);
    func_0205e118(param, 1, 0x9e);
}

void func_0205e444(void *p)
{
    int flag;
    flag = (func_0205e14c(p, 0)->unk_0D == 1);
    if (flag) {
        func_020b9ec4(func_0205e14c(p, 0));
    } else {
        func_020ba004(func_0205e14c(p, 0));
    }
    flag = (func_0205e14c(p, 1)->unk_0D == 1);
    if (flag) {
        func_020b9ec4(func_0205e14c(p, 1));
    } else {
        func_020ba004(func_0205e14c(p, 1));
    }
}
