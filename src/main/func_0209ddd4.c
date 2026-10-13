/* func_0209ddd4 @ 0x0209ddd4, 0x4e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef union {
    struct {
        unsigned char a;
        unsigned char b;
    } unk_00;
    unsigned short raw;
} Pair;

void func_0209ddd4(Pair p1, Pair p2, Pair *out)
{
    Pair local;

    local.raw = p1.raw;
    local.unk_00.a += p2.unk_00.a;
    local.unk_00.b += p2.unk_00.b;
    while (local.unk_00.a >= 0x3c) {
        local.unk_00.b++;
        local.unk_00.a -= 0x3c;
    }
    while (local.unk_00.b >= 0x18) {
        local.unk_00.b -= 0x18;
    }
    out->raw = local.raw;
}
