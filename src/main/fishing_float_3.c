/* fishing_float_3: 18 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206094c @ 0x0206094c, 0x28 bytes, Thumb
 * func_02060934 @ 0x02060934, 0x18 bytes, Thumb
 * func_02060924 @ 0x02060924, 0x10 bytes, Thumb
 * func_02060904 @ 0x02060904, 0x20 bytes, Thumb
 * func_020608fc @ 0x020608fc, 0x8 bytes, Thumb
 * func_020608f4 @ 0x020608f4, 0x8 bytes, Thumb
 * func_020608f0 @ 0x020608f0, 0x4 bytes, Thumb
 * func_020608ec @ 0x020608ec, 0x4 bytes, Thumb
 * func_02060878 @ 0x02060878, 0x74 bytes, Thumb
 * func_02060844 @ 0x02060844, 0x34 bytes, Thumb
 * func_02060754 @ 0x02060754, 0xf0 bytes, Thumb
 * func_02060704 @ 0x02060704, 0x50 bytes, Thumb
 * func_020606fc @ 0x020606fc, 0x6 bytes, Thumb
 * func_020606f0 @ 0x020606f0, 0xa bytes, Thumb
 * func_020606e4 @ 0x020606e4, 0xa bytes, Thumb
 * func_020606d4 @ 0x020606d4, 0x10 bytes, Thumb
 * func_020606c0 @ 0x020606c0, 0x12 bytes, Thumb
 * func_020606bc @ 0x020606bc, 0x2 bytes, Thumb
 */

struct UnkStruct_02060844 {
    char pad_00[0x24];
    char unk_24;
    char pad_25[0x1af];
    char unk_1D4;
};

typedef struct {
    int arr0[9];
    struct {
        char data[20];
    } sub[9];
    unsigned char pad_D8[0x678];
    int arr1[9];
} UnkStruct_02060704;

typedef struct {
    unsigned long a[64];
} UnkStruct_020606fc;

typedef struct {
    unsigned char x[0x14];
} UnkStruct_020606f0;

typedef struct {
    unsigned char pad_00[0x24];
    UnkStruct_020606f0 arr[4];
} UnkStruct_020606f0_2;

typedef struct {
    unsigned char x[0x1c];
} UnkStruct_020606e4;

typedef struct {
    unsigned char pad_00[0xd8];
    UnkStruct_020606e4 arr[4];
} UnkStruct_020606e4_2;

typedef struct {
    unsigned char unk_00;
    char pad_01[0x27];
    int unk_28;
    int unk_2C;
    int unk_30;
    int unk_34;
    int unk_38;
    int unk_3C;
} UnkStruct_020606c0;

extern void func_0205c3e4(int);
extern int func_020e9abc(int arg);
extern int data_021c9ac8;
extern void func_0205c3c8(void);
extern unsigned char data_021cad80[];
extern int func_02060508(void *ptr, int arg);
extern int func_02064328(void *a, void *b, void *c);
extern char data_021cad1c;
extern char data_020dd814;
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void *func_020ba01c(unsigned char *);
extern void func_02055ce8(void *);
extern void *func_02055cf4(void *);
extern void *func_02055764(void *);
extern void *func_0205577c(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern unsigned char func_020b65c4(void);
extern unsigned int func_020b5e04(unsigned int);
extern unsigned int func_020b5df8(unsigned int);
extern unsigned int func_02085f08(void);
extern int func_02055c80(unsigned char *, unsigned int, unsigned int, unsigned int);
extern unsigned int func_020e9968(unsigned int, unsigned int, unsigned int);
extern unsigned char *data_020ccf94;
extern void func_02055b40(void *ptr);
extern void func_020e9b9c(void *);

void func_02060754(unsigned int *param0);
void func_02060704(UnkStruct_02060704 *p);

void func_0206094c(int argument0)
{
    func_0205c3e4((int) argument0);
    func_02060754((unsigned int *) (((int *) data_021cad80)));
    if (data_021c9ac8) {
        func_020e9abc(data_021c9ac8);
    }
}

void func_02060934(void)
{
    void *ptr;

    ptr = (void *) data_021cad80;
    func_02060704((UnkStruct_02060704 *) ptr);
    func_0205c3c8();
}

int func_02060924(int arg)
{
    return func_02060508((void *) data_021cad80, arg);
}

void *func_02060904(void *arg)
{
    func_02064328(&data_021cad1c, &data_020dd814, arg);
    return &data_021cad1c;
}

int func_020608fc(void)
{
    return 1240;
}

int func_020608f4(void)
{
    return 512;
}

int func_020608f0(void)
{
    return 0;
}

int func_020608ec(void)
{
    return 32;
}

unsigned char *func_02060878(unsigned char *self)
{
    unsigned char *p;
    unsigned char *end;
    int i;

    __cxa_vec_ctor((void *) (self + 0x24), 9, 0x14, (((void (*)(void *)) func_02055cf4)), (void (*)(void *)) func_02055ce8);
    p = self + 0xd8;
    end = self + 0x1d4;
    do {
        func_020ba01c(p);
        p += 0x1c;
    } while (p != end);
    __cxa_vec_ctor((void *) (end), 9, 0x9c, (((void (*)(void *)) func_0205577c)), (((void (*)(void *)) func_02055764)));
    i = 0;
    do {
        int *p2 = (int *) self + i;
        *p2 = 0;
        *(int *) ((char *) p2 + 0x750) = 0;
        i++;
    } while (i < 9);
    return self;
}

void *func_02060844(struct UnkStruct_02060844 *self)
{
    __cxa_vec_cleanup((void *) (&self->unk_1D4), 9, 156, (((void (*)(void *)) func_02055764)));
    __cxa_vec_cleanup((void *) (&self->unk_24), 9, 20, (void (*)(void *)) func_02055ce8);
    return self;
}

void func_02060754(unsigned int *param0)
{
    unsigned char cnt;
    unsigned int i;
    unsigned int count;
    unsigned int countOrOne;
    unsigned int a, b;
    unsigned int end;
    unsigned int g;
    unsigned int r1, r2, r3;

    cnt = data_020ccf94[0x6c];
    count = func_020b5e04((unsigned int) func_020b65c4());
    if (cnt < count) {
        count = cnt;
    }

    if (count != 0) {
        countOrOne = count;
    } else {
        countOrOne = 1;
    }

    a = func_020b5df8((unsigned int) func_020b65c4());
    b = func_02085f08();
    end = (a + b) - countOrOne;

    for (i = 0; i < count; i++) {
        r1 = (unsigned int) func_020608f4();
        r2 = (unsigned int) func_020608f0();
        r3 = (unsigned int) func_020608ec();
        func_02055c80((unsigned char *) param0 + 0x24 + i * 0x14, r1, r2, r3);
    }

    for (i = 4; i < end + 4; i++) {
        r1 = (unsigned int) func_020608f4();
        r2 = (unsigned int) func_020608f0();
        r3 = (unsigned int) func_020608ec();
        func_02055c80((unsigned char *) param0 + 0x24 + i * 0x14, r1, r2, r3);
    }

    g = (*(unsigned int *) &data_021c9ac8);

    for (i = 0; i < count; i++) {
        param0[i] = func_020e9968(g, (unsigned int) func_020608fc(), 4);
    }

    for (i = 4; i < end + 4; i++) {
        param0[i] = func_020e9968(g, (unsigned int) func_020608fc(), 4);
    }
}

void func_02060704(UnkStruct_02060704 *p)
{
    void *condition_value0;
    int i;

    for (i = 0; i < 9; i++) {
        func_02055b40(&p->sub[i]);
    }

    for (i = 0; i < 9; i++) {
        p->arr0[i] = 0;
        p->arr1[i] = 0;
    }

    if ((condition_value0 = (void *) (data_021c9ac8))) {
        func_020e9b9c(condition_value0);
    }
}

unsigned long func_020606fc(UnkStruct_020606fc *p, int i)
{
    return p->a[i];
}

void *func_020606f0(UnkStruct_020606f0_2 *p, int i)
{
    return &p->arr[i];
}

void *func_020606e4(UnkStruct_020606e4_2 *p, int i)
{
    return &p->arr[i];
}

char *func_020606d4(char *base, int index)
{
    return base + 0x1d4 + index * 0x9c;
}

void func_020606c0(UnkStruct_020606c0 *param)
{
    param->unk_00 = 9;
    param->unk_28 = 0;
    param->unk_2C = 0;
    param->unk_34 = -1;
    param->unk_3C = -1;
}

void func_020606bc(void *object) {}
