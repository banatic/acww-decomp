/* func_ov144_0229a378 @ 0x0229a378, 0x2c bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229a378 UnkStruct_0229a378;

struct UnkStruct_0229a378 {
    unsigned char pad_00[0x9c];
    int unk_9C;
    unsigned char pad_A0[0x4];
    int unk_A4;
    int unk_A8;
};

extern int _s32_div_f(int a, int b);
extern void func_ov144_0229a3dc(UnkStruct_0229a378 *s);

void func_ov144_0229a378(UnkStruct_0229a378 *s)
{
    if (s->unk_A4 > 0) {
        s->unk_A8 = _s32_div_f(0x78 * s->unk_9C, s->unk_A4);
        func_ov144_0229a3dc(s);
    }
}
