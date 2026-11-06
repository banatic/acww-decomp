/* actor_palettes: 19 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0205f9ac @ 0x0205f9ac, 0x28 bytes, Thumb
 * func_0205f994 @ 0x0205f994, 0x18 bytes, Thumb
 * func_0205f974 @ 0x0205f974, 0x20 bytes, Thumb
 * func_0205f970 @ 0x0205f970, 0x4 bytes, Thumb
 * func_0205f96c @ 0x0205f96c, 0x4 bytes, Thumb
 * func_0205f958 @ 0x0205f958, 0x14 bytes, Thumb
 * func_0205f954 @ 0x0205f954, 0x2 bytes, Thumb
 * func_0205f950 @ 0x0205f950, 0x2 bytes, Thumb
 * func_0205f910 @ 0x0205f910, 0x40 bytes, Thumb
 * func_0205f8e8 @ 0x0205f8e8, 0x28 bytes, Thumb
 * func_0205f8e0 @ 0x0205f8e0, 0x6 bytes, Thumb
 * func_0205f8d8 @ 0x0205f8d8, 0x6 bytes, Thumb
 * func_0205f8d4 @ 0x0205f8d4, 0x2 bytes, Thumb
 * func_0205f8cc @ 0x0205f8cc, 0x8 bytes, Thumb
 * func_0205f8c8 @ 0x0205f8c8, 0x4 bytes, Thumb
 * func_0205f8b4 @ 0x0205f8b4, 0x14 bytes, Thumb
 * func_0205f8a0 @ 0x0205f8a0, 0x14 bytes, Thumb
 * func_0205f874 @ 0x0205f874, 0x2a bytes, Thumb
 * func_0205f848 @ 0x0205f848, 0x2a bytes, Thumb
 */

typedef struct {
    unsigned long a[64];
} UnkStruct_0205f8e0;

typedef struct {
    unsigned char unk_00;
} UnkStruct_0205f8d8;

extern unsigned int func_0205c610(int);
extern int func_020e9abc(void *);
extern unsigned char data_021c9ae0[];
extern unsigned char data_021cacec[];
extern void func_0205c5f4(void);
extern int data_021cacfc;
extern int data_020dd7b0;
extern int func_02064328(int *obj, int *tbl, unsigned int hi, unsigned int raw);
extern int func_020e9968(int *p, int val, int n);
extern unsigned char *data_020ccf94;
extern void func_020e9b9c(void *p);
extern int func_02064af4(int, int, int);

void func_0205f910(int *out);
void func_0205f8e8(int *arr);
void func_0205f8c8(unsigned char *p0, int p1);

void func_0205f9ac(int argument0)
{
    void *p;

    func_0205c610((int) argument0);
    func_0205f910((int *) ((void *) data_021cacec));
    p = *(void **) data_021c9ae0;
    if (p) {
        func_020e9abc(p);
    }
}

void func_0205f994(void)
{
    func_0205f8e8((int *) (((int *) data_021cacec)));
    func_0205c5f4();
}

int *func_0205f974(unsigned int raw)
{
    func_02064328(&data_021cacfc, &data_020dd7b0, raw >> 5, raw);
    return &data_021cacfc;
}

int func_0205f970(void)
{
    return 228;
}

int func_0205f96c(void)
{
    return 212;
}

int func_0205f958(void)
{
    int r4;
    int r0;

    r4 = func_0205f970();
    r0 = func_0205f96c();
    return r4 + r0;
}

void func_0205f954(void *self) {}

void func_0205f950(void *object) {}

void func_0205f910(int *out)
{
    int *p = (*(int **) data_021c9ae0);
    unsigned int count = data_020ccf94[0x6c];
    unsigned int i;

    for (i = 0; i < count; i++) {
        out[i] = func_020e9968(p, func_0205f958(), 4);
    }
}

void func_0205f8e8(int *arr)
{
    int i;
    for (i = 0; i < 4; i++) {
        arr[i] = 0;
    }
    if ((*(void **) data_021c9ae0)) {
        func_020e9b9c((*(void **) data_021c9ae0));
    }
}

unsigned long func_0205f8e0(UnkStruct_0205f8e0 *p, int i)
{
    return p->a[i];
}

void func_0205f8d8(UnkStruct_0205f8d8 *p)
{
    p->unk_00 = 4;
}

void func_0205f8d4(void *object) {}

void func_0205f8cc(unsigned char *argument0, int argument1)
{
    func_0205f8c8((unsigned char *) argument0, (int) argument1);
}

void func_0205f8c8(unsigned char *p0, int p1)
{
    p0[0] = p1;
}

unsigned long func_0205f8b4(unsigned char *p)
{
    return func_0205f8e0((UnkStruct_0205f8e0 *) data_021cacec, (unsigned char) (*p));
}

int func_0205f8a0(unsigned char *argument0)
{
    int r4;
    int result;

    r4 = (int) func_0205f8b4((unsigned char *) argument0);
    result = func_0205f970();
    return r4 + result;
}

int func_0205f874(int param1, int param2)
{
    int val;
    int val2;
    int val3;
    int val4;

    val = (int) func_0205f8b4((unsigned char *) param1);
    val2 = (int) func_0205f974(param2);
    val3 = func_0205f970();
    val4 = func_02064af4(val2, val, val3);
    return val4;
}

int func_0205f848(int arg1, int arg2)
{
    int a, b, c;
    b = func_0205f8a0((unsigned char *) arg1);
    a = (int) func_0205f974(arg2);
    c = func_0205f96c();
    return func_02064af4(a, b, c);
}
