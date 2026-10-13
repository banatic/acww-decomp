/* func_020bc5f8 @ 0x020bc5f8, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020bca80(void *a, int b, int c, int d);
extern void func_020bc9c4(void *a, int b);

struct Context {
    char pad_00[0x2f30];
    int unk_2F30;
};

void func_020bc5f8(struct Context *ctx)
{
    int val = ctx->unk_2F30;
    if (val < 0) {
        func_020bca80(ctx, 0, 0xe1, 0);
    } else if (val == 0) {
        func_020bc9c4(ctx, 0x13);
    }
}
