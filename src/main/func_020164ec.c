/* func_020164ec @ 0x020164ec, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02016764(int a, void *b, int c, int d, int e, int f, int g, int h);

struct UnkStruct_020164ec {
    unsigned char pad_00[0x190];
    unsigned int unk_190;
    unsigned char pad_194[0x4];
    unsigned int unk_198;
};

int func_020164ec(int a, struct UnkStruct_020164ec *b, int c, int d, int e)
{
    return func_02016764(a, b, c, d, 0, b->unk_198, (b->unk_190 << 4) >> 16, e);
}
