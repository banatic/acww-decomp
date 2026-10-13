/* func_02050974 @ 0x02050974, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0211f230(int a, int b);
extern int CARD_GetResultCode(int a);

struct UnkStruct_02050974 {
    int unk_00;
    int unk_04;
};

int func_02050974(struct UnkStruct_02050974 *s)
{
    int r;
    if (s->unk_04 == -3) {
        return 4;
    }
    r = func_0211f230(-3, s->unk_04);
    if (r != 0) {
        goto L1;
    }
    return 3;
L1:
    if (CARD_GetResultCode(r) != 0) {
        goto L2;
    }
    return 0;
L2:
    return 1;
}
