/* glasses_look_2: 25 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0205e0f0 @ 0x0205e0f0, 0x28 bytes, Thumb
 * func_0205e0d8 @ 0x0205e0d8, 0x18 bytes, Thumb
 * func_0205e0b8 @ 0x0205e0b8, 0x20 bytes, Thumb
 * func_0205e0b0 @ 0x0205e0b0, 0x8 bytes, Thumb
 * func_0205e0a4 @ 0x0205e0a4, 0xc bytes, Thumb
 * func_0205e098 @ 0x0205e098, 0xc bytes, Thumb
 * func_0205e090 @ 0x0205e090, 0x8 bytes, Thumb
 * func_0205e08c @ 0x0205e08c, 0x4 bytes, Thumb
 * func_0205e088 @ 0x0205e088, 0x4 bytes, Thumb
 * func_0205e034 @ 0x0205e034, 0x54 bytes, Thumb
 * func_0205e018 @ 0x0205e018, 0x1c bytes, Thumb
 * func_0205dfa8 @ 0x0205dfa8, 0x70 bytes, Thumb
 * func_0205df54 @ 0x0205df54, 0x54 bytes, Thumb
 * func_0205df4c @ 0x0205df4c, 0x6 bytes, Thumb
 * func_0205df40 @ 0x0205df40, 0xa bytes, Thumb
 * func_0205df34 @ 0x0205df34, 0xa bytes, Thumb
 * func_0205df2c @ 0x0205df2c, 0x8 bytes, Thumb
 * func_0205df24 @ 0x0205df24, 0x8 bytes, Thumb
 * func_0205df1c @ 0x0205df1c, 0x6 bytes, Thumb
 * func_0205df18 @ 0x0205df18, 0x2 bytes, Thumb
 * func_0205df14 @ 0x0205df14, 0x4 bytes, Thumb
 * func_0205defc @ 0x0205defc, 0x16 bytes, Thumb
 * func_0205dec8 @ 0x0205dec8, 0x34 bytes, Thumb
 * func_0205de94 @ 0x0205de94, 0x34 bytes, Thumb
 * func_0205de70 @ 0x0205de70, 0x24 bytes, Thumb
 */

typedef struct {
    char pad_00[20];
} Elem;

typedef struct {
    int arr[4];
    Elem elems[8];
} UnkStruct_0205dfa8;

typedef struct {
    int unk_00[4];
    struct {
        char data[20];
    } inner[4];
    char pad_60[0x70];
    char unk_D0[4];
} UnkStruct_0205df54;

typedef struct {
    unsigned long a[64];
} UnkStruct_0205df4c;

typedef struct {
    unsigned char x[0x14];
} UnkStruct_0205df40;

typedef struct {
    unsigned char pad_00[0x10];
    UnkStruct_0205df40 arr[4];
} UnkStruct_0205df40_2;

typedef struct {
    unsigned char x[0x1c];
} UnkStruct_0205df34;

typedef struct {
    unsigned char pad_00[0x60];
    UnkStruct_0205df34 arr[4];
} UnkStruct_0205df34_2;

typedef struct {
    unsigned char unk_00;
} UnkStruct_0205df1c;

struct UnkStruct_0205dec8 {
    unsigned char pad_00[13];
    unsigned char unk_0D;
};

extern unsigned int func_0205c5bc(int);
extern int func_020e9abc(void *);
extern unsigned char data_021c9adc[];
extern unsigned char data_021c9e68[];
extern void func_0205c5a0(void);
extern int func_02064328(void *, void *, unsigned int, unsigned int);
extern char data_021c9e54[];
extern char data_020dd718[];
extern unsigned char data_020cc7e0[];
extern unsigned char data_020cc7d4[];
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void *func_020ba01c(void *p);
extern void func_02055ce8(void *);
extern void *func_02055cf4(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern unsigned char *data_020ccf94;
extern int func_02055c80(void *dst, int a, int b, int c);
extern int func_020e9968(void *a, int b, int c);
extern void func_02055b40(void *);
extern void func_020e9b9c(void *);
extern void func_0205ddc0(int arg, int param);
extern struct UnkStruct_0205dec8 *func_0205dde8(void *p);
extern void func_020b9ec4(struct UnkStruct_0205dec8 *p);
extern void func_020ba004(struct UnkStruct_0205dec8 *p);
extern int func_0205de10(int);
extern int func_02064af4(int, int, int);
extern int func_0205ddfc(int a);
extern void func_02055b50(int a, int b);
extern int func_021077e8(int a) __attribute__((arm));

void func_0205dfa8(UnkStruct_0205dfa8 *obj);
void func_0205df54(UnkStruct_0205df54 *self);
void func_0205dec8(void *p);

void func_0205e0f0(unsigned int val)
{
    unsigned int *ptr;

    func_0205c5bc(val);
    func_0205dfa8((UnkStruct_0205dfa8 *) ((void *) data_021c9e68));
    ptr = (unsigned int *) data_021c9adc;
    val = *ptr;
    if (val != 0) {
        func_020e9abc((void *) val);
    }
}

void func_0205e0d8(void)
{
    unsigned int sp;
    sp = (unsigned int) data_021c9e68;
    func_0205df54((UnkStruct_0205df54 *) sp);
    func_0205c5a0();
}

void *func_0205e0b8(unsigned int param)
{
    func_02064328(data_021c9e54, data_020dd718, param >> 5, param);
    return data_021c9e54;
}

int func_0205e0b0(void)
{
    return 3188;
}

unsigned char func_0205e0a4(unsigned int r0)
{
    return data_020cc7e0[r0];
}

unsigned char func_0205e098(unsigned int r0)
{
    return data_020cc7d4[r0];
}

int func_0205e090(void)
{
    return 1536;
}

int func_0205e08c(void)
{
    return 0;
}

int func_0205e088(void)
{
    return 96;
}

void *func_0205e034(void *self)
{
    char *p;
    char *end;
    int i;
    int zero;

    __cxa_vec_ctor((void *) ((char *) self + 0x10), 4, 0x14, (((void (*)(void *)) func_02055cf4)),
                   (void (*)(void *)) func_02055ce8);

    p = (char *) self + 0x60;
    end = (char *) self + 0xd0;
    do {
        func_020ba01c(p);
        p += 0x1c;
    } while (p != end);

    i = 0;
    zero = i;
    for (; i < 4; i++) {
        ((int *) self)[i] = zero;
        ((char *) self + i)[0xd0] = 0x4b;
    }

    return self;
}

void *func_0205e018(void *arg)
{
    __cxa_vec_cleanup((void *) ((char *) arg + 16), 4, 20, (void (*)(void *)) func_02055ce8);
    return arg;
}

void func_0205dfa8(UnkStruct_0205dfa8 *obj)
{
    unsigned int count;
    unsigned int i;
    int v1;
    int v2;
    int v3;
    void *base;

    count = data_020ccf94[0x6c];

    for (i = 0; i < count; i++) {
        v1 = func_0205e090();
        v2 = func_0205e08c();
        v3 = func_0205e088();
        func_02055c80(&obj->elems[i], v1, v2, v3);
    }

    base = (*(void **) data_021c9adc);
    for (i = 0; i < count; i++) {
        obj->arr[i] = func_020e9968(base, func_0205e0b0(), 4);
    }
}

void func_0205df54(UnkStruct_0205df54 *self)
{
    int i;

    for (i = 0; i < 4; i++) {
        func_02055b40(&self->inner[i]);
    }
    for (i = 0; i < 4; i++) {
        self->unk_00[i] = 0;
    }
    if ((*(void **) data_021c9adc)) {
        func_020e9b9c((*(void **) data_021c9adc));
    }
    for (i = 0; i < 4; i++) {
        self->unk_D0[i] = 0x4b;
    }
}

unsigned long func_0205df4c(UnkStruct_0205df4c *p, int i)
{
    return p->a[i];
}

void *func_0205df40(UnkStruct_0205df40_2 *p, int i)
{
    return &p->arr[i];
}

void *func_0205df34(UnkStruct_0205df34_2 *p, int i)
{
    return &p->arr[i];
}

int func_0205df2c(int p0, int p1)
{
    return *(unsigned char *) ((char *) (((int) (((int) (p0) + (p1))) + (208))) + (0));
}

void func_0205df24(int p0, int p1, int p2)
{
    *(unsigned char *) ((char *) (((int) (((int) (p0) + (p1))) + (208))) + (0)) = p2;
}

void func_0205df1c(UnkStruct_0205df1c *p)
{
    p->unk_00 = 4;
}

void func_0205df18(void *object) {}

void func_0205df14(unsigned char *p0, int p1)
{
    p0[0] = p1;
}

void func_0205defc(int arg)
{
    func_0205dec8((void *) arg);
    func_0205ddc0(arg, 0x4B);
}

void func_0205dec8(void *p)
{
    int flag;

    flag = (func_0205dde8(p)->unk_0D == 1) ? 1 : 0;
    if (flag != 0) {
        func_020b9ec4(func_0205dde8(p));
    } else {
        func_020ba004(func_0205dde8(p));
    }
}

void func_0205de94(int a0, int a1)
{
    int v1, v3, v4;
    v1 = func_0205de10(a0);
    func_0205ddc0(a0, a1);
    if (a1 >= 0x4B) {
        return;
    }
    v3 = (int) func_0205e0b8(a1);
    v4 = func_0205e0b0();
    func_02064af4(v3, v1, v4);
}

void func_0205de70(int a)
{
    int tmp;
    tmp = func_021077e8(func_0205de10(a));
    func_02055b50(func_0205ddfc(a), tmp);
}
