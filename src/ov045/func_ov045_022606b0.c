/* func_ov045_022606b0 @ 0x022606b0, 0x74 bytes, Thumb, module ov045
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204f818(int *a, int *b, int *c);

typedef struct {
    int a;
    int b;
    int c;
} InterData;

extern InterData *func_02095794(int n);

typedef struct {
    char pad_00[0x5C];
    int unk_5C;
    char pad_60[0x4];
    int unk_64;
    char pad_68[0x5F0];
    int unk_658;
} UnkStruct_022606b0;

int func_ov045_022606b0(UnkStruct_022606b0 *p)
{
    int result = 0;
    int v0, v1;
    struct {
        int a, b, c;
    } local;
    InterData *data;

    data = func_02095794(4);
    local.a = data->a;
    local.b = data->b;
    local.c = data->c;
    v0 = 0;
    v1 = 0;
    func_0204f818(&v0, &v1, &local.a);

    if (p->unk_658 != 0) {
        goto exit;
    }
    if (local.a <= (p->unk_5C - 0x1000)) {
        goto exit;
    }
    if (local.a >= (p->unk_5C + 0x1000)) {
        goto exit;
    }
    if (local.c <= (p->unk_64 + 0x2000)) {
        goto exit;
    }
    if (local.c >= (p->unk_64 + 0x4000)) {
        goto exit;
    }
    result = 1;
exit:
    return result;
}
