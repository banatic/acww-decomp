/* func_ov004_02242a28 @ 0x02242a28, 0x74 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_02242a28 {
    char unk_00[0x192];
    short ang;
    char unk_194[0x2c8 - 0x194];
    Vec3 pos;
} UnkStruct_02242a28;

extern int func_0200322c(Vec3 *a, Vec3 *b);
extern int func_020e8870(short *a, int b, int c);

int func_ov004_02242a28(UnkStruct_02242a28 *a, UnkStruct_02242a28 *b)
{
    short t[2];
    unsigned char f;

    t[0] = a->ang;
    t[1] = b->ang;
    f = (unsigned char) func_020e8870(&t[1], func_0200322c(&b->pos, &a->pos), 0xaaa);
    f &= func_020e8870(&t[0], func_0200322c(&a->pos, &b->pos), 0xaaa);
    a->ang = t[0];
    b->ang = t[1];
    return f != 0;
}
