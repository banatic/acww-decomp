/* body_look_2: 18 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0205d234 @ 0x0205d234, 0x28 bytes, Thumb
 * func_0205d21c @ 0x0205d21c, 0x18 bytes, Thumb
 * func_0205d210 @ 0x0205d210, 0xc bytes, Thumb
 * func_0205d208 @ 0x0205d208, 0x8 bytes, Thumb
 * func_0205d200 @ 0x0205d200, 0x8 bytes, Thumb
 * func_0205d1fc @ 0x0205d1fc, 0x4 bytes, Thumb
 * func_0205d1f8 @ 0x0205d1f8, 0x4 bytes, Thumb
 * func_0205d1b8 @ 0x0205d1b8, 0x40 bytes, Thumb
 * func_0205d19c @ 0x0205d19c, 0x1c bytes, Thumb
 * func_0205d12c @ 0x0205d12c, 0x70 bytes, Thumb
 * func_0205d0e8 @ 0x0205d0e8, 0x44 bytes, Thumb
 * func_0205d0e0 @ 0x0205d0e0, 0x6 bytes, Thumb
 * func_0205d0d4 @ 0x0205d0d4, 0xa bytes, Thumb
 * func_0205d0c8 @ 0x0205d0c8, 0xa bytes, Thumb
 * func_0205d0c0 @ 0x0205d0c0, 0x6 bytes, Thumb
 * func_0205d0bc @ 0x0205d0bc, 0x2 bytes, Thumb
 * func_0205d0b8 @ 0x0205d0b8, 0x4 bytes, Thumb
 * func_0205d084 @ 0x0205d084, 0x34 bytes, Thumb
 */

typedef struct {
    char pad_00[20];
} Elem;

typedef struct {
    int arr[4];
    Elem elems[8];
} UnkStruct_0205d12c;

struct UnkStruct_0205d0e8 {
    char pad_00[0x14];
};

struct UnkStruct_0205d0e8_2 {
    int arr[4];
    struct UnkStruct_0205d0e8 sub[4];
};

typedef struct {
    unsigned long a[64];
} UnkStruct_0205d0e0;

typedef struct {
    unsigned char x[0x14];
} UnkStruct_0205d0d4;

typedef struct {
    unsigned char pad_00[0x10];
    UnkStruct_0205d0d4 arr[4];
} UnkStruct_0205d0d4_2;

typedef struct {
    unsigned char x[0x1c];
} UnkStruct_0205d0c8;

typedef struct {
    unsigned char pad_00[0x60];
    UnkStruct_0205d0c8 arr[4];
} UnkStruct_0205d0c8_2;

typedef struct {
    unsigned char unk_00;
} UnkStruct_0205d0c0;

struct UnkStruct_0205d084 {
    char pad_00[0xD];
    unsigned char unk_0D;
};

extern unsigned int func_0205c6b0(int);
extern int func_020e9abc(void *);
extern int data_021c9ae8;
extern unsigned char data_021c9c2c[];
extern void func_0205c694(void);
extern unsigned int data_020dd6c0[];
extern void *func_02055cf4(void *);
extern void func_02055ce8(void *);
extern void *func_020ba01c(void *p);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern unsigned char *data_020ccf94;
extern int func_02055c80(void *dst, int a, int b, int c);
extern int func_020e9968(void *a, int b, int c);
extern void func_02055b40(void *);
extern void func_020e9b9c(int);
extern struct UnkStruct_0205d084 *func_0205cfac(void *);
extern void func_020b9ec4(struct UnkStruct_0205d084 *);
extern void func_020ba004(struct UnkStruct_0205d084 *);

void func_0205d12c(UnkStruct_0205d12c *obj);
void func_0205d0e8(struct UnkStruct_0205d0e8_2 *p);

void func_0205d234(int argument0)
{
    void *condition_value0;
    func_0205c6b0((int) argument0);
    func_0205d12c((UnkStruct_0205d12c *) ((void *) data_021c9c2c));
    if ((condition_value0 = (void *) (data_021c9ae8))) {
        func_020e9abc(condition_value0);
    }
}

void func_0205d21c(void)
{
    (((int) (func_0205d0e8((struct UnkStruct_0205d0e8_2 *) (((int *) data_021c9c2c))), ((int *) data_021c9c2c))), func_0205c694());
}

unsigned int func_0205d210(unsigned int r0)
{
    return data_020dd6c0[r0];
}

int func_0205d208(void)
{
    return 9088;
}

int func_0205d200(void)
{
    return 1088;
}

int func_0205d1fc(void)
{
    return 0;
}

int func_0205d1f8(void)
{
    return 96;
}

void *func_0205d1b8(void *p)
{
    char *ptr;
    char *end;
    __cxa_vec_ctor((void *) ((char *) p + 0x10), 4, 0x14, (((void (*)(void *)) func_02055cf4)),
                   (void (*)(void *)) func_02055ce8);
    ptr = (char *) p + 0x60;
    end = (char *) p + 0xd0;
    do {
        func_020ba01c(ptr);
        ptr += 0x1c;
    } while (ptr != end);
    return p;
}

char *func_0205d19c(char *arg0)
{
    __cxa_vec_cleanup((void *) (arg0 + 0x10), 4, 0x14, (void (*)(void *)) func_02055ce8);
    return arg0;
}

void func_0205d12c(UnkStruct_0205d12c *obj)
{
    unsigned int count;
    unsigned int i;
    int v1;
    int v2;
    int v3;
    void *base;

    count = data_020ccf94[0x6c];

    for (i = 0; i < count; i++) {
        v1 = func_0205d200();
        v2 = func_0205d1fc();
        v3 = func_0205d1f8();
        func_02055c80(&obj->elems[i], v1, v2, v3);
    }

    base = (*(void * *) &data_021c9ae8);
    for (i = 0; i < count; i++) {
        obj->arr[i] = func_020e9968(base, func_0205d208(), 4);
    }
}

void func_0205d0e8(struct UnkStruct_0205d0e8_2 *p)
{
    int i;

    for (i = 0; i < 4; i++) {
        func_02055b40(&p->sub[i]);
    }

    for (i = 0; i < 4; i++) {
        p->arr[i] = 0;
    }

    if (data_021c9ae8) {
        func_020e9b9c(data_021c9ae8);
    }
}

unsigned long func_0205d0e0(UnkStruct_0205d0e0 *p, int i)
{
    return p->a[i];
}

void *func_0205d0d4(UnkStruct_0205d0d4_2 *p, int i)
{
    return &p->arr[i];
}

void *func_0205d0c8(UnkStruct_0205d0c8_2 *p, int i)
{
    return &p->arr[i];
}

void func_0205d0c0(UnkStruct_0205d0c0 *p)
{
    p->unk_00 = 4;
}

void func_0205d0bc(void *object) {}

void func_0205d0b8(unsigned char *p0, int p1)
{
    p0[0] = p1;
}

void func_0205d084(void *arg)
{
    int cond = (func_0205cfac(arg)->unk_0D == 1);
    if (cond) {
        func_020b9ec4(func_0205cfac(arg));
    } else {
        func_020ba004(func_0205cfac(arg));
    }
}
