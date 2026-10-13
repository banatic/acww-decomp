/* func_02073970 @ 0x02073970, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02077b58(int key);

typedef struct {
    unsigned char pad_00[0x4c];
    unsigned int arrayA[3];
    unsigned int arrayB[3];
} Context;

void func_02073970(Context *ctx, int key)
{
    unsigned int idx;
    unsigned int newVal;

    idx = func_02077b58(key);
    ctx->arrayB[idx]--;
    newVal = ctx->arrayA[idx] + 1;
    if (newVal >= 3) {
        newVal = 0;
    }
    ctx->arrayA[idx] = newVal;
}
