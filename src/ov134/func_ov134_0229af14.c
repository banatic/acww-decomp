/* func_ov134_0229af14 @ 0x0229af14, 0x4c bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229af14 {
    unsigned char pad_00[0x84];
    int unk_84;
    unsigned char pad_88[0x92 - 0x84 - 4];
    unsigned short unk_92;
    unsigned short unk_94;
} UnkStruct_0229af14;

void func_ov134_0229af14(UnkStruct_0229af14 *param)
{
    int r4 = param->unk_84;
    while (r4 < 0) {
        r4 += 720;
    }
    while (r4 >= 720) {
        r4 -= 720;
    }
    param->unk_94 = (unsigned short) ((r4 << 16) / 720);
    param->unk_92 = (unsigned short) (0x444 * (r4 % 60));
}
