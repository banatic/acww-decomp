/* func_0201e334 @ 0x0201e334, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_020c80f8;
extern int data_020d9290[2];

typedef struct Triple {
    int a, b, c;
} Triple;

typedef struct Pair {
    int x;
    int y;
} Pair;

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

void func_02019d0c(void *p, int a, int b, int c, int d, int e, int f, int g, int h, unsigned short i, int j);

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
    *(Pair *) obj->unk_F0 = *(Pair *) data_020d9290;
}
