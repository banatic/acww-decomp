/* message_walker_5: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a9ccc @ 0x020a9ccc, 0x14 bytes, Thumb
 * func_020a9cc0 @ 0x020a9cc0, 0xa bytes, Thumb
 * func_020a9cac @ 0x020a9cac, 0x12 bytes, Thumb
 * func_020a9c9c @ 0x020a9c9c, 0xe bytes, Thumb
 * func_020a9c98 @ 0x020a9c98, 0x2 bytes, Thumb
 * func_020a9c84 @ 0x020a9c84, 0x12 bytes, Thumb
 */

struct Context {
    int array[6];
    int count;
};

typedef struct {
    unsigned char pad_00[0x18];
    int unk_18;
} UnkStruct_020a9cc0;

struct UnkStruct_020a9cac {
    unsigned int arr[6];
    unsigned int count;
};

typedef struct {
    int arr[6];
    int x;
} __func_020a9c84_struct;

void func_020a9ccc(struct Context *ctx)
{
    if (ctx->count) {
        ctx->count--;
        ctx->array[ctx->count] = 0;
    }
}

int *func_020a9cc0(UnkStruct_020a9cc0 *p)
{
    return (int *) p + (p->unk_18 - 1);
}

void func_020a9cac(struct UnkStruct_020a9cac *s, unsigned int *src)
{
    unsigned int idx;
    idx = s->count;
    if (idx >= 6) {
        return;
    }
    s->count = idx + 1;
    s->arr[idx] = *src;
}

int func_020a9c9c(void *param)
{
    if (*(int *) ((char *) param + 0x18) == 0) {
        return 1;
    }
    return 0;
}

void func_020a9c98(void *self) {}

void func_020a9c84(__func_020a9c84_struct *p)
{
    unsigned int i;
    p->x = 0;
    for (i = 0; i < 6; i++) {
        p->arr[i] = 0;
    }
}
