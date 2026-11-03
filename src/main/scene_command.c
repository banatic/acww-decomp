/* scene_command: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02014bc0 @ 0x02014bc0, 0x2e bytes, Thumb
 * func_02014ba0 @ 0x02014ba0, 0x1e bytes, Thumb
 * func_02014b30 @ 0x02014b30, 0x70 bytes, Thumb
 * func_02014b14 @ 0x02014b14, 0x1c bytes, Thumb
 * func_02014ae8 @ 0x02014ae8, 0x2c bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0xa5];
    unsigned char flag;
} UnkStruct_02014ba0;

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

typedef struct {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0x68];
    unsigned char unk_AC;
} UnkStruct_02014ae8;

extern int func_0201596c(unsigned char *p, int n);
extern void func_02068440(void *);
extern void func_0206ea5c(void *, void *);
extern void func_0206ea10(unsigned short);
extern int func_0206e970(unsigned short);
extern unsigned char data_021cfbbc;
extern int data_020df2a0;
extern void func_02068434(int arg);

int func_02014bc0(unsigned char *p, long long *src)
{
    if (func_0201596c(p, 0xa) != 0) {
        *(long long *) (p + 0x8c) = *src;
        p[0xa5] = 0;
        return 1;
    }
    return 0;
}

int func_02014ba0(UnkStruct_02014ba0 *ptr)
{
    if (func_0201596c((unsigned char *) ptr, 10)) {
        ptr->flag = 1;
        return 1;
    }
    return 0;
}

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

int func_02014b14(unsigned char *arg0)
{
    if (data_020df2a0 != -1) {
        arg0[0xac] = 2;
    }
    return 0;
}

int func_02014ae8(UnkStruct_02014ae8 *arg)
{
    if (data_020df2a0 != -1) {
        return 0;
    }
    if (arg->unk_40) {
        func_02068434(arg->unk_40);
    }
    arg->unk_AC = 3;
    return 1;
}
