/* func_0206caa8 @ 0x0206caa8, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Vtbl Vtbl;
typedef struct UnkStruct_0206caa8 UnkStruct_0206caa8;
typedef struct Context Context;

struct Vtbl {
    void *slot0;
    void *slot1;
    void *slot2;
    void *(*func)(void *self);
};

struct UnkStruct_0206caa8 {
    Vtbl *vtbl;
    char pad0[0x1a58 - 4];
    void *unk_1A58;
    char pad_1A5C[4];
    int flag;
};

struct Context {
    char pad0[0x2c];
    UnkStruct_0206caa8 *obj;
};

extern UnkStruct_0206caa8 *func_02068058(void *p);
extern void func_020a9334(void *a, void *b);
extern void func_020a7994(void *a, void *b);

void func_0206caa8(Context *ctx)
{
    UnkStruct_0206caa8 *obj;
    void *v1;
    void *v2;

    obj = func_02068058(ctx->obj);
    v1 = obj->vtbl->func(obj);
    func_020a9334(ctx, v1);

    obj = func_02068058(ctx->obj);
    v2 = obj->vtbl->func(obj);
    func_020a7994(&ctx->obj->unk_1A58, v2);
    ctx->obj->flag = 1;
}
