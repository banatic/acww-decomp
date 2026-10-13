/* func_ov147_0229a2a8 @ 0x0229a2a8, 0x28 bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229a2a8 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
};

extern void func_ov147_0229a2f4(struct UnkStruct_0229a2a8 *s);
extern void func_ov147_0229a280(struct UnkStruct_0229a2a8 *s);

void func_ov147_0229a2a8(struct UnkStruct_0229a2a8 *s)
{
    if (s->unk_08 != s->unk_0C) {
        func_ov147_0229a2f4(s);
    } else {
        s->unk_18--;
        if (s->unk_18 > 0) {
            // do nothing
        } else {
            func_ov147_0229a280(s);
        }
    }
}
