/* func_ov111_0229efec @ 0x0229efec, 0x96 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

struct Context {
    char pad_00[0x9e];
    unsigned char flag_9e;
    char pad_9F[13];
    char ac_member;
};

extern int func_ov111_0229f4dc(struct Context *ctx);
extern int func_ov111_0229efd8(struct Context *ctx, int v);
extern int func_ov111_0229f504(struct Context *ctx);

extern void func_ov095_0229cef4(void *p, int v);
extern void func_ov095_0229ce84(void *p, int v);
extern void func_ov095_0229bee4(void *p);
extern void func_ov095_0229bed8(void *p, int v);

void func_ov111_0229efec(struct Context *ctx)
{
    func_ov095_0229cef4(&ctx->ac_member, 0);
    if (func_ov111_0229f4dc(ctx)) {
        func_ov095_0229ce84(&ctx->ac_member, 0xb);
    } else {
        func_ov095_0229cef4(&ctx->ac_member, 0xb);
    }
    if (func_ov111_0229efd8(ctx, 8)) {
        func_ov095_0229ce84(&ctx->ac_member, 0xc);
    } else {
        func_ov095_0229cef4(&ctx->ac_member, 0xc);
    }
    if (func_ov111_0229f4dc(ctx)) {
        func_ov095_0229bee4(&ctx->ac_member);
        func_ov095_0229ce84(&ctx->ac_member, 6);
    } else {
        if (ctx->flag_9e == 0) {
            func_ov095_0229bee4(&ctx->ac_member);
        } else {
            func_ov095_0229bed8(&ctx->ac_member, func_ov111_0229f504(ctx));
        }
    }
}
