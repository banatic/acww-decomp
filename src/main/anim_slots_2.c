/* anim_slots_2: 14 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0205ce98 @ 0x0205ce98, 0x18 bytes, Thumb
 * func_0205ce94 @ 0x0205ce94, 0x2 bytes, Thumb
 * func_0205cda0 @ 0x0205cda0, 0xf4 bytes, Thumb
 * func_0205cd60 @ 0x0205cd60, 0x40 bytes, Thumb
 * func_0205cd58 @ 0x0205cd58, 0x6 bytes, Thumb
 * func_0205cd4c @ 0x0205cd4c, 0xa bytes, Thumb
 * func_0205cd40 @ 0x0205cd40, 0xa bytes, Thumb
 * func_0205cd08 @ 0x0205cd08, 0x38 bytes, Thumb
 * func_0205ccfc @ 0x0205ccfc, 0xa bytes, Thumb
 * func_0205ccf0 @ 0x0205ccf0, 0xa bytes, Thumb
 * func_0205cce8 @ 0x0205cce8, 0x6 bytes, Thumb
 * func_0205cce4 @ 0x0205cce4, 0x2 bytes, Thumb
 * func_0205ccc4 @ 0x0205ccc4, 0x20 bytes, Thumb
 * func_0205ccc0 @ 0x0205ccc0, 0x4 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x64];
    unsigned short arr[25];
} UnkStruct_0205ce98;

typedef struct {
    int arr0[25];
    unsigned short arr1[25];
    unsigned short arr2[25];
} my_struct;

typedef struct {
    unsigned long a[64];
} UnkStruct_0205cd58;

typedef struct {
    unsigned char pad_00[0x64];
    unsigned short arr[8];
} UnkStruct_0205cd4c;

typedef struct {
    unsigned char pad_00[0x64];
    unsigned short arr[8];
} UnkStruct_0205cd40;

typedef struct {
    unsigned char pad_00[0x96];
    unsigned short arr[8];
} UnkStruct_0205ccfc;

typedef struct {
    unsigned char pad_00[0x96];
    unsigned short arr[8];
} UnkStruct_0205ccf0;

typedef struct {
    unsigned char unk_00;
} UnkStruct_0205cce8;

extern unsigned int data_021c9af8;
extern unsigned char *data_020ccf94;
extern unsigned char func_020b65c4(void);
extern unsigned int func_020b5e04(unsigned int);
extern unsigned int func_020b5df8(unsigned int);
extern unsigned int func_02085f08(void);
extern unsigned int func_0205cf44(void);
extern unsigned int func_0205cf3c(void);
extern unsigned int func_0205cf34(void);
extern unsigned int func_020e9968(unsigned int, unsigned int, unsigned int);
extern void func_020e9b9c(void *);
extern void func_0205cc1c(int, int, int, int);

void func_0205ccc0(unsigned char *p0, int p1);

void func_0205ce98(UnkStruct_0205ce98 *p)
{
    int i;
    for (i = 0; i < 25; i++) {
        p->arr[i] = 0x144;
    }
}

void func_0205ce94(void *object) {}

void func_0205cda0(unsigned int *out)
{
    unsigned int total, s1, s2, s3, tmp, size;
    unsigned int arg, n0, n;
    unsigned char field;
    unsigned int i;

    arg = data_021c9af8;
    field = data_020ccf94[0x6c];
    n0 = func_020b5e04((unsigned int) func_020b65c4());
    if (field < n0) {
        n0 = field;
    }
    if (n0 != 0) {
        n = n0;
    } else {
        n = 1;
    }

    tmp = func_020b5df8((unsigned int) func_020b65c4());
    total = tmp + func_02085f08() - n;
    s1 = func_0205cf44();
    s2 = func_0205cf3c();
    s3 = func_0205cf34();

    for (i = 0; i < n0; i++) {
        out[i] = func_020e9968(arg, s1, 4);
    }

    size = 4;
    for (i = 4; i < total + 4; i++) {
        out[i] = func_020e9968(arg, s1, size);
    }

    for (i = 9; i < n0 + 9; i++) {
        out[i] = func_020e9968(arg, s2, 4);
    }

    for (i = 13; i < total + 13; i++) {
        out[i] = func_020e9968(arg, s2, size);
    }

    for (i = 18; i < total + 18; i++) {
        out[i] = func_020e9968(arg, s3, size);
    }
}

void func_0205cd60(my_struct *p)
{
    void *condition_value0;
    int i;
    for (i = 0; i < 25; i++) {
        p->arr0[i] = 0;
        p->arr1[i] = 0x144;
        p->arr2[i] = 0;
    }
    if ((condition_value0 = (void *) ((*(int *) &data_021c9af8)))) {
        func_020e9b9c(condition_value0);
    }
}

unsigned long func_0205cd58(UnkStruct_0205cd58 *p, int i)
{
    return p->a[i];
}

unsigned short func_0205cd4c(UnkStruct_0205cd4c *p, int i)
{
    return p->arr[i];
}

void func_0205cd40(UnkStruct_0205cd40 *p, int i, unsigned short v)
{
    p->arr[i] = v;
}

int func_0205cd08(unsigned short *array, int target)
{
    int i = 0;
    int max = 0x19;

    if (target < 0x137) {
        max = 9;
    } else {
        i = 9;
    }

    while (i < max) {
        unsigned short val = *(unsigned short *) ((char *) array + i * 2 + 100);
        if (val == target) {
            return i;
        }
        i++;
    }

    return 0x19;
}

unsigned short func_0205ccfc(UnkStruct_0205ccfc *p, int i)
{
    return p->arr[i];
}

void func_0205ccf0(UnkStruct_0205ccf0 *p, int i, unsigned short v)
{
    p->arr[i] = v;
}

void func_0205cce8(UnkStruct_0205cce8 *p)
{
    p->unk_00 = 25;
}

void func_0205cce4(void *object) {}

void func_0205ccc4(int param, int argument1)
{
    int r4 = param;
    func_0205ccc0((unsigned char *) param, (int) argument1);
    func_0205cc1c(r4, 0x144, 0, 0);
}

void func_0205ccc0(unsigned char *p0, int p1)
{
    p0[0] = p1;
}
