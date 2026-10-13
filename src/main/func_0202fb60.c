/* func_0202fb60 @ 0x0202fb60, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0202fb60 {
    char pad_00[4];
    int unk_04;
    int unk_08;
    int unk_0C;
    char pad_10[24];
    int unk_28;
    int unk_2C;
    int unk_30;
};

extern int FX_MulFunc(int a, int b) __attribute__((arm));

int func_0202fb60(struct UnkStruct_0202fb60 *p)
{
    int v1, v2, v3;
    v1 = FX_MulFunc(p->unk_30, p->unk_0C);
    v2 = FX_MulFunc(p->unk_28, p->unk_04);
    v3 = FX_MulFunc(p->unk_2C, p->unk_08);
    return -(v1 + (v2 + v3));
}
