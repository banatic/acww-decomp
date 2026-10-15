/* func_0205650c @ 0x0205650c, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02056548(int, void *, int);
extern char data_020dd148;

typedef struct {
    char pad_00[0x18];
    void *unk_18;
    int unk_1C;
} UnkStruct_0205650c;

int func_0205650c(UnkStruct_0205650c *ctx, int arg, int argument2)
{
    if (ctx->unk_18 != 0 || ctx->unk_1C != 0) {
        return 0;
    }
    ctx->unk_18 = func_02056548(arg, &data_020dd148, (int) argument2);
    ctx->unk_1C = arg;
    if (ctx->unk_18 != 0) {
        return 1;
    } else {
        return 0;
    }
}
