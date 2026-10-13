/* func_ov046_022607f0 @ 0x022607f0, 0x7c bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b1558(void);

struct UnkStruct_022607f0 {
    char pad_00[0xc4];
    unsigned char unk_C4;
    unsigned char unk_C5;
    unsigned char unk_C6;
    char pad_C7[0x15];
    int unk_DC;
};

void func_ov046_022607f0(struct UnkStruct_022607f0 *a, int b)
{
    a->unk_C5 = 0x10 - func_020b1558();
    a->unk_C4 = 0;
    if (b == 0) {
        if (func_020b1558() < 0x10) {
            a->unk_DC = 0x18;
        } else {
            a->unk_DC = 7;
        }
    } else if (b == 1) {
        a->unk_DC = 0x35;
    } else if (b == 2) {
        a->unk_C5 = 0x10 - func_020b1558();
        a->unk_C4 = 0;
        a->unk_DC = 0x1f;
        a->unk_C6 = 0;
    } else {
        a->unk_DC = 2;
    }
}
