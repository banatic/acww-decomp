/* func_020ff3a4 @ 0x020ff3a4, 0x90 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

typedef struct {
    short a;
    short b;
    short c;
    unsigned char lo;
    unsigned char hi;
} Table;

typedef struct {
    int pad_00;
    Table *tab;
} UnkStruct_020ff3a4;

typedef struct {
    char pad_00[0x34];
    short value;
} Output;

void func_020ff3a4(Output *out, const UnkStruct_020ff3a4 *outer, int x)
{
    const Table *t = outer->tab;
    unsigned char lo = t->lo;
    unsigned char hi = t->hi;

    if (x < lo) {
        out->value = t->a + x * (t->b - t->a) / lo;
        return;
    }
    if (x < hi) {
        out->value = t->b;
        return;
    }
    out->value = t->c + (x - 255) * (t->c - t->b) / (255 - hi);
}
