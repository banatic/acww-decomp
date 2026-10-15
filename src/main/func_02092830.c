/* func_02092830 @ 0x02092830, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct UnkStruct_02092830 {
    int a;
    int b;
    int c;
    unsigned short d;
} data_021d5658;

extern signed short FX_SinCosTable_[];

struct UnkStruct_02092830_2 {
    int pad_00;
    int x;
    int y;
    int z;
};

typedef struct UnkStruct_02092830_3 {
    char pad_00[0x18];
    struct UnkStruct_02092830_2 **ptr;
    char pad_1C[4];
    int mat[3];
    char pad_2C[0x10];
    short s0;
    short s1;
    short s2;
    char pad_42[0x36];
    void (*func)(struct UnkStruct_02092830_3 *a, int b);
} UnkStruct_02092830_3;

extern void func_02090db0(UnkStruct_02092830_3 *ctx);
extern void func_02092898(UnkStruct_02092830_3 *a, int b);

void func_02092830(UnkStruct_02092830_3 *ctx)
{
    unsigned short d;
    int idx2;

    d = data_021d5658.d;
    ctx->mat[0] = data_021d5658.a + (*ctx->ptr)->x;
    ctx->mat[1] = data_021d5658.b + (*ctx->ptr)->y;
    ctx->mat[2] = data_021d5658.c + (*ctx->ptr)->z;
    idx2 = (d >> 4) * 2;
    ctx->s0 = FX_SinCosTable_[idx2];
    ctx->s1 = 0;
    ctx->s2 = FX_SinCosTable_[idx2 + 1];
    func_02090db0(ctx);
    ctx->func = func_02092898;
}
