/* func_ov096_0229ee80 @ 0x0229ee80, 0x1a bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229ee80 {
    char pad_00[0xac];
    unsigned short unk_AC;
    char pad_AE[2];
    unsigned char unk_B0;
};

extern int func_ov096_0229ef30(struct UnkStruct_0229ee80 *s, int x, unsigned short a, unsigned char b);

int func_ov096_0229ee80(struct UnkStruct_0229ee80 *s, int x)
{
    return func_ov096_0229ef30(s, x, s->unk_AC, s->unk_B0);
}
