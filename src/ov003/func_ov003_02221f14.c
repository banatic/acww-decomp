/* func_ov003_02221f14 @ 0x02221f14, 0x3c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02221f14;

extern void VEC_Add(int *p1, int *p2, int *p3);
extern void func_ov003_02222860(struct UnkStruct_02221f14 *s);

struct UnkStruct_02221f14 {
    char pad_00[0x18];
    int unk_18;
    int unk_1C;
    char pad_20[0x10];
    int unk_30;
    int unk_34;
    int unk_38;
};

void func_ov003_02221f14(struct UnkStruct_02221f14 *s)
{
    s->unk_34 -= 0x400;
    VEC_Add(&s->unk_18, &s->unk_30, &s->unk_18);
    if (s->unk_1C >= 0) {
        return;
    }
    s->unk_1C = 0;
    s->unk_30 = 0;
    s->unk_34 = 0;
    s->unk_38 = 0;
    func_ov003_02222860(s);
}
