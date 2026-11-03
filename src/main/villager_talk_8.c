/* villager_talk_8: 9 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201e510 @ 0x0201e510, 0x8 bytes, Thumb
 * func_0201e508 @ 0x0201e508, 0x8 bytes, Thumb
 * func_0201e4d4 @ 0x0201e4d4, 0x34 bytes, Thumb
 * func_0201e4a0 @ 0x0201e4a0, 0x34 bytes, Thumb
 * func_0201e46c @ 0x0201e46c, 0x34 bytes, Thumb
 * func_0201e3d0 @ 0x0201e3d0, 0x9c bytes, Thumb
 * func_0201e3b0 @ 0x0201e3b0, 0x20 bytes, Thumb
 * func_0201e334 @ 0x0201e334, 0x7c bytes, Thumb
 * func_0201e2d8 @ 0x0201e2d8, 0x5c bytes, Thumb
 */

typedef struct InputStruct {
    unsigned char pad_00[0x104];
    unsigned int field_at_104;
    unsigned char pad_108[0x1A];
    unsigned char byte_at_122;
} InputStruct;

typedef struct OutputStruct {
    void *ptr_at_0;
    unsigned char byte_at_4;
} OutputStruct;

typedef struct {
    unsigned int unk_00;
    unsigned char unk_04;
} ResultStruct;

typedef struct {
    unsigned int a;
    unsigned int b;
} Pair;

typedef struct {
    unsigned int a;
    unsigned char b;
} Data020c8d18;

typedef struct {
    int x;
    int y;
} Pair_0201e3b0;

typedef struct Triple {
    int a, b, c;
} Triple;

typedef struct Pair_0201e334 {
    int x;
    int y;
} Pair_0201e334;

typedef struct UnkStruct_0201e334_2 {
    int unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_0201e334_2;

typedef struct UnkStruct_0201e334 {
    unsigned char pad_00[0x5c];
    UnkStruct_0201e334_2 inner;
} UnkStruct_0201e334;

typedef struct UnkStruct_0201e334_3 {
    unsigned char pad_00[0xf0];
    int unk_F0[2];
    unsigned char pad_F8[8];
    UnkStruct_0201e334 *unk_100;
} UnkStruct_0201e334_3;

struct Pair {
    unsigned int a;
    unsigned int b;
};

struct UnkStruct_0201e2d8 {
    unsigned char pad_00[0xf0];
    unsigned int unk_F0;
    unsigned int unk_F4;
    unsigned char pad_F8[8];
    int unk_100;
};

extern void func_0202a5e8(void *, void *);
extern void func_02020360(void *);
extern int func_02022454(InputStruct *);
extern int func_02021118(void *p);
extern int func_02022034(void *p);
extern void func_0202dac0(void *p);
extern int func_0202213c(void *);
extern unsigned int func_0208150c(unsigned int);
extern unsigned int func_020036e8(unsigned int);
extern int func_0202da38(void *, void *, void *, int, int, int, int, int, int);
extern void func_0202d8f8(void *, void *, void *, unsigned int, int);
extern Pair data_020d92b0;
extern Data020c8d18 data_020c8d18;
extern Pair_0201e3b0 data_020d8f98;
extern int func_02015590(int a, int b);
extern void func_0202dbf0(int a, Pair_0201e3b0 p);
extern unsigned short data_020c80f8;
extern int data_020d9290[2];
int func_02019d0c(void *p, int a, int b, int c, int d, int e, int f, int g, int h, unsigned short i, int j);
extern int func_02019e00(int);
extern int func_02019de8(int);
extern int func_02019c6c(int, int, unsigned short);
extern unsigned int data_020d8f58[2];

void func_0201e510(void *argument0, void *argument1)
{
    func_0202a5e8((void *) argument0, (void *) argument1);
}

void func_0201e508(void *argument0)
{
    func_02020360((void *) argument0);
}

void func_0201e4d4(InputStruct *param0, OutputStruct *param1)
{
    func_02021118((void *) param0);
    func_02022454(param0);
    param1->ptr_at_0 = &param0->field_at_104;
    param1->byte_at_4 = param0->byte_at_122;
    func_0202dac0((void *) param0);
}

void func_0201e4a0(void *p, ResultStruct *r)
{
    func_02021118(p);
    func_02022034(p);
    r->unk_00 = (unsigned int) p + 0x104;
    r->unk_04 = ((unsigned char *) p)[0x122];
    func_0202dac0(p);
}

void func_0201e46c(void *param0, void *param1)
{
    unsigned char *r5;
    unsigned char *r4;
    unsigned char *r0;

    r5 = param0;
    r4 = param1;
    func_02021118(r5);
    func_0202213c(r5);
    r0 = r5 + 0x104;
    *(unsigned int *) r4 = (unsigned int) r0;
    r0 = r5 + 0x122;
    r4[4] = *r0;
    func_0202dac0(r5);
}

void func_0201e3d0(unsigned char *self, unsigned char *out)
{
    unsigned int y;

    y = func_020036e8(func_0208150c(*(unsigned int *) (*(unsigned int *) (self + 0x100) + 0x830)));
    func_0202da38(self, self + 0x104, self + 0x122, 30, y, data_020c8d18.a, 1, 0, data_020c8d18.b);
    *(unsigned int *) out = (unsigned int) (self + 0x104);
    *(unsigned char *) (out + 4) = *(unsigned char *) (self + 0x122);
    func_0202d8f8(self, self + 0x12c, self + 0x128, *(unsigned int *) (*(unsigned int *) (self + 0x100) + 0x830), 0);
    *(Pair *) (self + 0xf8) = data_020d92b0;
}

void func_0201e3b0(int a)
{
    func_02015590(a, 0);
    func_0202dbf0(a, data_020d8f98);
}

void func_0201e334(UnkStruct_0201e334_3 *obj)
{
    Triple tmp;
    UnkStruct_0201e334 *p = obj->unk_100;
    UnkStruct_0201e334_2 *ip = &p->inner;
    tmp.a = ip->unk_00;
    tmp.b = ip->unk_04;
    tmp.c = ip->unk_08;
    tmp.a += 0x1e00;
    tmp.c -= 0x2800;
    {
        int *tp = (int *) &tmp;
        func_02019d0c((char *) obj->unk_100 + 0x564, 2, 2, tp[0], tmp.c, 0, 0, 0, 0, data_020c80f8, 0);
    }
    *(Pair_0201e334 *) obj->unk_F0 = *(Pair_0201e334 *) data_020d9290;
}

void func_0201e2d8(struct UnkStruct_0201e2d8 *p)
{
    if (func_02019e00(p->unk_100 + 0x564) != 2) {
        return;
    }
    if (func_02019de8(p->unk_100 + 0x564) == 0) {
        return;
    }
    func_02019c6c(p->unk_100 + 0x564, 2, data_020c80f8);
    *(struct Pair *) &p->unk_F0 = *(struct Pair *) &data_020d8f58;
}
