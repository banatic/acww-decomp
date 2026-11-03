/* villager_mood_3: 11 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201ccc0 @ 0x0201ccc0, 0x10 bytes, Thumb
 * func_0201cc6c @ 0x0201cc6c, 0x54 bytes, Thumb
 * func_0201cc48 @ 0x0201cc48, 0x24 bytes, Thumb
 * func_0201cbec @ 0x0201cbec, 0x5c bytes, Thumb
 * func_0201cbcc @ 0x0201cbcc, 0x20 bytes, Thumb
 * func_0201cbc4 @ 0x0201cbc4, 0x8 bytes, Thumb
 * func_0201cbbc @ 0x0201cbbc, 0x8 bytes, Thumb
 * func_0201cbac @ 0x0201cbac, 0x10 bytes, Thumb
 * func_0201cb68 @ 0x0201cb68, 0x44 bytes, Thumb
 * func_0201cb54 @ 0x0201cb54, 0x12 bytes, Thumb
 * func_0201cb40 @ 0x0201cb40, 0x12 bytes, Thumb
 */

#include "types.h"

struct Global {
    char pad_00[0x64];
    int unk_64;
};

struct UnkStruct_0201cc6c {
    char pad_00[0x54];
    unsigned char unk_54;
    char pad_55;
    unsigned short unk_56;
};

typedef struct {
    unsigned char pad_00[0x58];
    unsigned char unk_58;
} UnkStruct_0201cc48;

typedef struct {
    unsigned char pad_00[0x64];
    int unk_64;
} GlobStruct_0201cc48;

struct UnkStruct_0201cbec {
    u8 pad_00[0x8e];
    s16 unk_8E;
    u8 pad_90[0x478 - 0x90];
    u32 unk_478;
    u32 unk_47C;
    u32 unk_480;
};

typedef struct {
    char pad_00[0x5c];
    unsigned int unk_5C;
    unsigned int unk_60;
    unsigned int unk_64;
} UnkStruct_0201cbcc;

extern struct Global *data_020ccf94;
extern int func_02073dd4(struct Global *, int);
extern int func_020044c0(void *p1, void *p4, int c, int d);
extern int func_020912d4(void *p3, u32 *arr, short *s, int d);
extern void func_020044d0(void *a, unsigned int *b);
extern int func_020164a0(int, int);
extern int data_020c8ed4[];
extern int data_020c8ee8[];

int func_0201cbac(const unsigned char *ptr);

void func_0201ccc0(void *arg0)
{
    unsigned char *pbVar1;
    unsigned short *psVar2;

    pbVar1 = (unsigned char *) ((unsigned int) arg0 + 0x54);
    *pbVar1 = 5;
    psVar2 = (unsigned short *) ((unsigned int) arg0 + 0x56);
    *psVar2 = 0;
}

void func_0201cc6c(struct UnkStruct_0201cc6c *unk, unsigned int idx, unsigned int count)
{
    struct Global *p = data_020ccf94;
    unsigned short val;

    if (func_02073dd4(p, p->unk_64) != 0 || idx >= 5) {
        return;
    }

    val = (unsigned short) (count * 1200);

    if (idx == unk->unk_54) {
        unk->unk_56 += val;
    } else {
        unk->unk_54 = idx;
        unk->unk_56 = val;
    }
}

void func_0201cc48(UnkStruct_0201cc48 *arg)
{
    if (func_02073dd4((struct Global *) ((*(GlobStruct_0201cc48 * *) &data_020ccf94)), (*(GlobStruct_0201cc48 * *) &data_020ccf94)->unk_64) == 0) {
        arg->unk_58 = 1;
    }
}

int func_0201cbec(void *p1, struct UnkStruct_0201cbec *p2, void *p3, void *p4)
{

    u32 local[3];
    short s;

    int result = func_0201cbac((const unsigned char *) p1);
    if (result == 0) {
        return result;
    }

    local[0] = p2->unk_478;
    local[1] = p2->unk_47C;
    local[2] = p2->unk_480;
    s = p2->unk_8E;

    func_020044c0(p1, p4, 0x7f, 0);
    return func_020912d4(p3, local, &s, 0);
}

void func_0201cbcc(void *arg, UnkStruct_0201cbcc *p)
{
    unsigned int arr[3];
    unsigned int *base;

    base = (unsigned int *) ((char *) p + 0x5c);
    arr[0] = p->unk_5C;
    arr[1] = base[1];
    arr[2] = base[2];
    func_020044d0(arg, arr);
}

void func_0201cbc4(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (90))) + (0)) = 1;
}

void func_0201cbbc(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (90))) + (0)) = 0;
}

int func_0201cbac(const unsigned char *ptr)
{
    return ptr[0x5A] != 0;
}

int func_0201cb68(int unused, int param)
{
    int x = func_020164a0(param + 0x334, 0);
    int *p1 = data_020c8ed4;
    int *p2 = data_020c8ee8;
    int i;
    for (i = 0; i < 5; i++) {
        if (x == *p1 || x == *p2) {
            return 1;
        }
        p1++;
        p2++;
    }
    return 0;
}

void func_0201cb54(int a, int b)
{
    func_0201cbec((void *) a, (struct UnkStruct_0201cbec *) b, (void *) 0x5a, (void *) 0x7b);
}

int func_0201cb40(int a, int b)
{
    return func_0201cbec((void *) a, (struct UnkStruct_0201cbec *) b, (void *) 0x5b, (void *) 0x7b);
}
