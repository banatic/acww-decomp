/* func_02050974 @ 0x02050974, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0211f230(void);
extern int CARD_GetResultCode(void);

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
    r = func_0211f230();
    if (r != 0) {
        goto L1;
    }
    return 3;
L1:
    if (CARD_GetResultCode() != 0) {
        goto L2;
    }
    return 0;
L2:
    return 1;
}
