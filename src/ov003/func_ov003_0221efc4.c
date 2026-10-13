/* func_ov003_0221efc4 @ 0x0221efc4, 0x28 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct Src {
    int a, b, c;
};
struct Dst {
    char flag;
    int a, b, c, count, value;
};

int func_ov003_0221efc4(struct Dst *dst, int idx, struct Src *src, int val)
{
    if (idx < dst->count) {
        dst->a = src->a;
        dst->b = src->b;
        dst->c = src->c;
        dst->count = idx;
        dst->value = val;
        dst->flag = 1;
        return 1;
    }
    return 0;
}
