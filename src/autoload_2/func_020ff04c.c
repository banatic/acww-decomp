/* func_020ff04c @ 0x020ff04c, 0x4c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

struct UnkStruct_020ff04c {
    char pad_00[4];
    short s;
};

struct UnkStruct_020ff04c_2 {
    char pad_00[20];
    struct UnkStruct_020ff04c *b;
};

struct UnkStruct_020ff04c_3 {
    char pad_00[52];
    unsigned short unk_34;
};

void func_020ff04c(struct UnkStruct_020ff04c_3 *out, struct UnkStruct_020ff04c_2 *a, int v)
{
    short s;
    int delta;
    int factor;
    int prod;
    int ratio;

    s = a->b->s;
    delta = s - 0x1000;
    factor = v - 255;
    prod = delta * factor;
    ratio = prod / 255;
    out->unk_34 = (unsigned short) (s + ratio);
}
