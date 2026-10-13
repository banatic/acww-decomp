/* func_020360d0 @ 0x020360d0, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct InnerStruct {
    char pad_00[0xc];
    void *unk_0C;
    char pad_10[4];
    unsigned char unk_14;
    char pad_15[0x1c0 - 0x15];
    int unk_1C0;
} InnerStruct;

typedef struct OuterStruct {
    InnerStruct *obj;
} OuterStruct;

typedef struct Arg1Struct {
    char pad_00[0xc];
    int unk_0C;
} Arg1Struct;

typedef struct Pair {
    int first;
    int second;
} Pair;

extern Pair data_020da284;
extern void func_02036558(void *a, void *b, int c, int d);
extern void func_02034e28(void *a, Pair b);

void func_020360d0(OuterStruct *a, Arg1Struct *b)
{
    if (a->obj->unk_1C0 > 0) {
        if (a->obj->unk_14 != 0 && a->obj->unk_0C != 0) {
            func_02036558(b, a->obj->unk_0C, 0, 1);
        }
        func_02034e28(a->obj, data_020da284);
        b->unk_0C = 0x12;
    } else {
        b->unk_0C = 0;
    }
}
