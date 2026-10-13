/* func_ov114_0229d500 @ 0x0229d500, 0x2c bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

extern int _s32_div_f(int, int);

struct UnkStruct_0229d500 {
    char pad_00[0x1270];
    int unk_1270;
    char pad_1274[8];
    int unk_127C;
    char pad_1280[24];
    int unk_1298;
};

void func_ov114_0229d500(struct UnkStruct_0229d500 *p)
{
    p->unk_1270 = _s32_div_f(p->unk_127C * 0x8c, p->unk_1298);
}
