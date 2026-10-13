/* func_020362a0 @ 0x020362a0, 0x6e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020362a0 {
    char pad_00[0xc];
    int unk_0C;
};
struct UnkStruct_020362a0_2 {
    char pad_00[0x84];
    int unk_84;
};
extern void func_02036558(struct UnkStruct_020362a0 *b, int a, int c, int d);
extern void func_020041dc(void);
extern void func_020041cc(void);

void func_020362a0(struct UnkStruct_020362a0_2 *a, struct UnkStruct_020362a0 *b)
{
    if (b->unk_0C == 7) {
        func_02036558(b, 0x28, 5, 1);
        b->unk_0C = 8;
        a->unk_84 = 0;
        func_020041dc();
    } else if (b->unk_0C == 8) {
        return;
    } else if (b->unk_0C == 9) {
        if (a->unk_84 > 0) {
            a->unk_84--;
        }
        if (a->unk_84 <= 0) {
            func_02036558(b, 0x7f, 5, 1);
            b->unk_0C = 0;
            func_020041cc();
        }
    }
}
