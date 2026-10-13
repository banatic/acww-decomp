/* func_020a9ccc @ 0x020a9ccc, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Context {
    int array[6];
    int count;
};

void func_020a9ccc(struct Context *ctx)
{
    if (ctx->count) {
        ctx->count--;
        ctx->array[ctx->count] = 0;
    }
}
