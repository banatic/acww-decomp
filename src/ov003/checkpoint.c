/* checkpoint: 19 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0221c6cc @ 0x0221c6cc, 0x1c bytes, Thumb
 * func_ov003_0221c69c @ 0x0221c69c, 0x30 bytes, Thumb
 * func_ov003_0221c668 @ 0x0221c668, 0x34 bytes, Thumb
 * func_ov003_0221c630 @ 0x0221c630, 0x38 bytes, Thumb
 * func_ov003_0221c5d4 @ 0x0221c5d4, 0x5c bytes, Thumb
 * func_ov003_0221c5bc @ 0x0221c5bc, 0x18 bytes, Thumb
 * func_ov003_0221c5b8 @ 0x0221c5b8, 0x4 bytes, Thumb
 * func_ov003_0221c5a0 @ 0x0221c5a0, 0x18 bytes, Thumb
 * func_ov003_0221c588 @ 0x0221c588, 0x18 bytes, Thumb
 * func_ov003_0221c570 @ 0x0221c570, 0x18 bytes, Thumb
 * func_ov003_0221c548 @ 0x0221c548, 0x28 bytes, Thumb
 * func_ov003_0221c520 @ 0x0221c520, 0x28 bytes, Thumb
 * func_ov003_0221c4f8 @ 0x0221c4f8, 0x28 bytes, Thumb
 * func_ov003_0221c4f4 @ 0x0221c4f4, 0x4 bytes, Thumb
 * func_ov003_0221c4bc @ 0x0221c4bc, 0x38 bytes, Thumb
 * func_ov003_0221c4a4 @ 0x0221c4a4, 0x18 bytes, Thumb
 * func_ov003_0221c490 @ 0x0221c490, 0x12 bytes, Thumb
 * func_ov003_0221c438 @ 0x0221c438, 0x58 bytes, Thumb
 * func_ov003_0221c430 @ 0x0221c430, 0x8 bytes, Thumb
 */

typedef struct {
    void *unk_00;
    unsigned char pad_04[0xe8];
    void *unk_EC;
    unsigned char pad_F0[0x1c4];
    unsigned char unk_2B4;
} UnkStruct_0221c630;

typedef struct {
    unsigned char pad_00[0x5c];
    unsigned char unk_5C;
    unsigned char pad_5D[0x198 - 0x5d];
    unsigned int unk_198;
    unsigned char pad_19C[0x2b4 - 0x19c];
    unsigned char unk_2B4;
} UnkStruct_0221c5d4;

typedef struct UnkStruct_0221c4bc {
    char pad_00[0x198];
    int unk_198;
    char pad_19C[0x118];
    char unk_2B4[1];
} UnkStruct_0221c4bc;

typedef struct {
    char pad_00[0x28];
    int unk_28;
} UnkStruct_0221c438;

extern int func_020edf70(int);
extern void *func_ov009_0226552c(void *p);
extern unsigned char data_ov003_02238934[];
extern unsigned char data_ov003_022389f8[];
extern void *func_ov009_0226539c(void *p);
extern void func_020edf54(void *obj);
extern int func_020b374c(void *);
extern void *func_020b3848(void *record);
extern void func_0204f818(int *, int *, void *);
extern int func_02030920(int, int, int);
extern unsigned char data_021f34b0[];
extern void func_02055124(void *ptr);
extern int func_020b3858(void *);
extern int data_ov003_02238908[];
extern int data_ov003_0223c868;
extern int data_ov003_02238aa4;
extern int func_ov003_022203dc(void);
extern int func_02064328(void *, void *, int, int);
extern char data_ov003_0223c844[];
extern char data_ov003_02238a8c[];
extern int data_ov003_0223c88c;
extern int data_ov003_02238a74;
extern void *func_020b9e58(void *);
extern void func_0203d228(void *object);
extern void func_0203d224(void *ptr);
extern int func_0203cff8(void *, int);
extern int func_0203cfc8(void *);
extern int func_020b9d3c(void *, int, int *, int, int, int);
extern void func_020b3850(int, int);
extern int data_ov003_02238a70;
extern void func_020b9e2c(int argument0);

void *func_ov003_0221c69c(void *obj);
void *func_ov003_0221c4a4(void *self);
void *func_ov003_0221c490(void *self);
int func_ov003_0221c438(UnkStruct_0221c438 *a, int b, int c);
void func_ov003_0221c430(int argument0);

void func_ov003_0221c6cc(void)
{
    void *condition_value_6;
    condition_value_6 = (void *) (func_020edf70(0x5a0));
    if (condition_value_6 != 0) {
        func_ov003_0221c69c(condition_value_6);
    }
}

void *func_ov003_0221c69c(void *obj)
{
    func_ov009_0226552c(obj);
    *(unsigned int *) obj = (unsigned int) data_ov003_02238934;
    *(unsigned int *) ((char *) obj + 0xEC) = (unsigned int) data_ov003_022389f8;
    func_ov003_0221c4a4((char *) obj + 0x2B4);
    return obj;
}

void *func_ov003_0221c668(void *obj)
{
    unsigned int *p;

    *(unsigned int *) obj = (unsigned int) data_ov003_02238934;
    p = (unsigned int *) obj;
    p = (unsigned int *) ((char *) p + 0xec);
    *p = (unsigned int) data_ov003_022389f8;
    func_ov003_0221c490((char *) obj + 0x2b4);
    func_ov009_0226539c(obj);
    return obj;
}

void *func_ov003_0221c630(UnkStruct_0221c630 *obj)
{
    obj->unk_00 = ((char *) data_ov003_02238934);
    obj->unk_EC = ((char *) data_ov003_022389f8);
    func_ov003_0221c490(&obj->unk_2B4);
    func_ov009_0226539c(obj);
    func_020edf54(obj);
    return obj;
}

int func_ov003_0221c5d4(UnkStruct_0221c5d4 *self)
{
    unsigned int old;
    int v0;
    int v1;
    int i;
    int result;

    old = self->unk_198;
    result = (int) func_020b3848((void *) func_020b374c((void *) data_021f34b0));
    func_ov003_0221c438((UnkStruct_0221c438 *) (&self->unk_2B4), old, result);
    func_0204f818(&v0, &v1, &self->unk_5C);
    for (i = -2; i <= 2; i++) {
        func_02030920(v0 + i, v1 - 1, 15);
    }
    return 1;
}

int func_ov003_0221c5bc(void *arg0)
{
    func_02055124((char *) arg0 + 0x13c);
    return 1;
}

int func_ov003_0221c5b8(void)
{
    return 1;
}

int func_ov003_0221c5a0(void *p)
{
    func_ov003_0221c430((int) ((char *) p + 0x2b4));
    return 1;
}

int func_ov003_0221c588(void)
{
    return func_020b3858((void *) func_020b374c(((int *) data_021f34b0)));
}

int func_ov003_0221c570(void)
{
    int index;
    int value;

    index = func_ov003_0221c588();
    value = data_ov003_02238908[index];
    return value;
}

int *func_ov003_0221c548(void)
{
    int a, b;
    a = func_ov003_0221c570();
    b = func_ov003_022203dc();
    func_02064328((void *) (&data_ov003_0223c868), (void *) (&data_ov003_02238aa4), a, b);
    return &data_ov003_0223c868;
}

void *func_ov003_0221c520(void)
{
    int a = func_ov003_0221c570();
    int b = func_ov003_022203dc();
    func_02064328(data_ov003_0223c844, data_ov003_02238a8c, a, b);
    return data_ov003_0223c844;
}

void *func_ov003_0221c4f8(void)
{
    int n = func_ov003_0221c570();
    int m = func_ov003_022203dc();

    func_02064328(&data_ov003_0223c88c, &data_ov003_02238a74, n, m);

    return &data_ov003_0223c88c;
}

int func_ov003_0221c4f4(void)
{
    return 0;
}

int func_ov003_0221c4bc(UnkStruct_0221c4bc *self)
{
    int a = self->unk_198;
    int result = (int) func_020b3848((void *) func_020b374c((void *) ((unsigned int) data_021f34b0)));
    func_ov003_0221c438((UnkStruct_0221c438 *) (&self->unk_2B4), a, result);
    return 1;
}

void *func_ov003_0221c4a4(void *self)
{
    func_020b9e58(self);
    func_0203d228((char *) self + 0x28);
    return self;
}

void *func_ov003_0221c490(void *self)
{
    func_0203d224((char *) self + 0x28);
    return self;
}

int func_ov003_0221c438(UnkStruct_0221c438 *a, int b, int c)
{
    if (func_0203cff8(&a->unk_28, c) != 0) {
        int tmp = func_0203cfc8(&a->unk_28);
        if (func_020b9d3c(a, b, &data_ov003_02238a70, tmp, 0, 0) != 0) {
            func_020b3850(func_020b374c((void *) (((int *) data_021f34b0))), c);
            return 1;
        }
    }
    return 0;
}

void func_ov003_0221c430(int argument0)
{
    func_020b9e2c(argument0);
}
