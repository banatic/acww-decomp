/* func_ov088_02278c38 @ 0x02278c38, 0x5c bytes, Thumb, module ov088
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov088_02279d98;
extern int func_020984e8(int, void *);
extern int func_02099020(int, int);
extern int func_0202ea80(int, int);
extern int func_020644cc(int);
extern int func_0203fa58(int);

typedef struct {
    unsigned int unk_00;
    unsigned char unk_04;
} UnkStruct_02278c38;

void func_ov088_02278c38(int unused, UnkStruct_02278c38 *ctx)
{
    int r;
    int r2;

    ctx->unk_00 = (unsigned int) &data_ov088_02279d98;
    ctx->unk_04 = 1;
    r = func_02099020(func_020984e8(1, ctx), 0x10);
    if (r == 1) {
        r2 = func_0202ea80(0xe, 0);
        if (r2 == 0) {
            ctx->unk_04 = (unsigned char) (func_020644cc(2) + 0x13);
        } else if (func_0203fa58(r2) == 1) {
            ctx->unk_04 = (unsigned char) (func_020644cc(3) + 0xd);
        } else {
            ctx->unk_04 = (unsigned char) (func_020644cc(3) + 0x10);
        }
    }
}
