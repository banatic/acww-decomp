/* func_020fa090 @ 0x020fa090, 0x6c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020fa090 {
    int pad_00;
    int x;
    int y;
    int z;
};

struct UnkStruct_020fa090_2 {
    char pad_00[0x18];
    struct UnkStruct_020fa090 **b;
    char pad_1C[0x4];
    int vec[3];
};

struct UnkStruct_020fa090_3 {
    int arr[3];
};

struct UnkStruct_020fa090_4;

extern void func_020fabdc(struct UnkStruct_020fa090_2 *a, char *p);

void func_020fa090(struct UnkStruct_020fa090_4 *f, struct UnkStruct_020fa090_2 *a, struct UnkStruct_020fa090_3 *e)
{
    int v2;

    a->vec[0] = e->arr[0] + (*a->b)->x;
    a->vec[1] = e->arr[1] + (*a->b)->y;
    v2 = e->arr[2] + (*a->b)->z;
    a->vec[2] = v2;
    func_020fabdc(a, (char *) f + 0x14);
}
