/* chat_scene: 10 functions, module ov111
 * mwccarm 1.2/base -O4,s
 * func_ov111_0229f090 @ 0x0229f090, 0x14 bytes, Thumb
 * func_ov111_0229f084 @ 0x0229f084, 0xc bytes, Thumb
 * func_ov111_0229efec @ 0x0229efec, 0x96 bytes, Thumb
 * func_ov111_0229efd8 @ 0x0229efd8, 0x12 bytes, Thumb
 * func_ov111_0229efc8 @ 0x0229efc8, 0xe bytes, Thumb
 * func_ov111_0229efb8 @ 0x0229efb8, 0xe bytes, Thumb
 * func_ov111_0229efb4 @ 0x0229efb4, 0x4 bytes, Thumb
 * func_ov111_0229efb0 @ 0x0229efb0, 0x4 bytes, Thumb
 * func_ov111_0229ef90 @ 0x0229ef90, 0x20 bytes, Thumb
 * func_ov111_0229ef78 @ 0x0229ef78, 0x18 bytes, Thumb
 */

struct Context {
    char pad_00[0x9e];
    unsigned char flag_9e;
    char pad_9F[13];
    char ac_member;
};

struct UnkStruct_0xa4 {
    char pad_00[0xa4];
    unsigned short flags;
};

struct UnkStruct_0229efc8 {
    unsigned char pad_00[0xa4];
    unsigned short unk_A4;
};

struct UnkStruct_0229efb8 {
    char pad_00[0xa4];
    unsigned short unk_A4;
};

extern void func_ov095_0229c22c(void *ptr, int arg1, int arg2, int arg3);
extern void func_ov095_0229bf7c(void *ptr, int arg);
extern int func_ov111_0229f4dc(struct Context *ctx);
extern int func_ov111_0229f504(struct Context *ctx);
extern void func_ov095_0229cef4(void *p, int v);
extern void func_ov095_0229ce84(void *p, int v);
extern void func_ov095_0229bee4(void *p);
extern void func_ov095_0229bed8(void *receiver, int value);
extern void *func_020a887c(void *);
extern void func_020edb3c(void *);
extern unsigned int data_ov111_022a0ff0;

int func_ov111_0229efd8(struct UnkStruct_0xa4 *self, unsigned int mask);

void func_ov111_0229f090(void *self, int arg1)
{
    func_ov095_0229c22c((char *) self + 0xac, arg1, 6, 1);
}

void func_ov111_0229f084(void *ptr)
{
    func_ov095_0229bf7c((char *) ptr + 0xac, 6);
}

void func_ov111_0229efec(struct Context *ctx)
{
    func_ov095_0229cef4(&ctx->ac_member, 0);
    if (func_ov111_0229f4dc(ctx)) {
        func_ov095_0229ce84(&ctx->ac_member, 0xb);
    } else {
        func_ov095_0229cef4(&ctx->ac_member, 0xb);
    }
    if (func_ov111_0229efd8((struct UnkStruct_0xa4 *) ctx, 8)) {
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

int func_ov111_0229efd8(struct UnkStruct_0xa4 *self, unsigned int mask)
{
    return (self->flags & mask) != 0;
}

void func_ov111_0229efc8(struct UnkStruct_0229efc8 *p, unsigned short v)
{
    p->unk_A4 |= v;
}

void func_ov111_0229efb8(struct UnkStruct_0229efb8 *self, unsigned short mask)
{
    self->unk_A4 &= ~mask;
}

int func_ov111_0229efb4(void)
{
    return 16;
}

int func_ov111_0229efb0(int p0)
{
    return ((int) (p0) + (14));
}

void *func_ov111_0229ef90(void *obj)
{
    void *p = obj;
    *(unsigned int *) p = (unsigned int) &data_ov111_022a0ff0;
    func_020a887c(obj);
    func_020edb3c(p);
    return p;
}

void *func_ov111_0229ef78(void *self)
{
    *(char **) self = ((char *) &data_ov111_022a0ff0);
    func_020a887c(self);
    return self;
}
