/* func_020f0d98 @ 0x020f0d98, 0x44 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

struct UnkStruct_020f0d98 {
    short unk_00;
    short unk_02;
    int unk_04;
    int unk_08;
};

extern int FX_Div(int a, int b);

void func_020f0d98(struct UnkStruct_020f0d98 *s, short a, short b)
{
    int shifted;
    int diff;
    s->unk_00 = a;
    s->unk_02 = b;
    shifted = ((int) s->unk_00) << 12;
    diff = shifted - s->unk_04;
    if (b == 0) {
        s->unk_04 = shifted;
        return;
    }
    s->unk_08 = FX_Div(diff, b << 12);
}
