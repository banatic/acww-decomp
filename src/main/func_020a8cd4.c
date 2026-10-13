/* func_020a8cd4 @ 0x020a8cd4, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a895c(int a, int b, int c);
extern int func_020a8910(int a, int b, int c);

struct UnkStruct_020a8cd4 {
    unsigned char pad_00[4];
    int unk_04;
    unsigned char pad_08[36];
    int unk_2C;
    int unk_30;
    int unk_34;
    unsigned char unk_38;
};

void func_020a8cd4(struct UnkStruct_020a8cd4 *p)
{
    if (p->unk_2C != 0) {
        if (p->unk_34 == 0) {
            p->unk_38 = (unsigned char) func_020a895c(p->unk_2C, p->unk_30, p->unk_04);
        } else if (p->unk_34 == 1) {
            p->unk_38 = (unsigned char) func_020a8910(p->unk_2C, p->unk_30, p->unk_04);
        }
    }
}
