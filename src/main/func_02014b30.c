/* func_02014b30 @ 0x02014b30, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02068440(void *);
extern void func_0206ea5c(void *, void *);
extern void func_0206ea10(unsigned short);
extern void func_0206e970(unsigned short);
extern unsigned char data_021cfbbc;

struct FuncTable;
struct UnkStruct_02014b30 {
    struct FuncTable *vtbl;
};
struct FuncTable {
    int (*funcs[34])(struct UnkStruct_02014b30 *);
};

struct UnkStruct_02014b30_2 {
    unsigned char pad_00[0x40];
    void *unk_40;
    unsigned char pad_44[0x8];
    struct UnkStruct_02014b30 *unk_4C;
    unsigned char pad_50[0x3c];
    unsigned char sub8c[0x19];
    unsigned char flag_a5;
    unsigned char pad_A6[0x6];
    unsigned char flag_ac;
};

int func_02014b30(struct UnkStruct_02014b30_2 *ctx)
{
    void *base = &data_021cfbbc;
    int r4;

    if (ctx->unk_4C) {
        r4 = ctx->unk_4C->vtbl->funcs[33](ctx->unk_4C);
    } else {
        r4 = 0;
    }

    if (r4 != 0xffff) {
        if (ctx->unk_40) {
            func_02068440(ctx->unk_40);
        }
        if (ctx->flag_a5 == 0) {
            func_0206ea5c(ctx->sub8c, base);
            func_0206ea10((unsigned short) r4);
        } else {
            func_0206e970((unsigned short) r4);
        }
        ctx->flag_ac = 1;
        return 0;
    } else {
        ctx->flag_ac = 3;
        return 1;
    }
}
