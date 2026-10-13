/* func_ov127_02299a50 @ 0x02299a50, 0x44 bytes, Thumb, module ov127
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02299a50 {
    unsigned char pad_00[0x2824];
    short unk_2824;
    short unk_2826;
};

int func_ov127_02299a50(struct UnkStruct_02299a50 *p, int a, int b, int *out, int *out2)
{
    int x;
    int y;

    x = (a + p->unk_2824) & 0x1ff;
    y = b + p->unk_2826;

    if (y < 0 || y >= 0x100) {
        return 0;
    }

    *out = x >> 3;
    *out2 = y >> 3;
    return 1;
}
