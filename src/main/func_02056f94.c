/* func_02056f94 @ 0x02056f94, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02056f94 {
    char pad_00[4];
    int unk_04;
    int unk_08;
    char pad_0C[8];
    unsigned char unk_14;
};

int func_02056f94(struct UnkStruct_02056f94 *s)
{
    switch (s->unk_14) {
        case 1:
            if (s->unk_08 < (s->unk_04 - 0x1000)) {
                return 0;
            } else {
                return 1;
            }
        case 3:
            if (s->unk_08 != 0) {
                return 0;
            } else {
                return 1;
            }
        default:
            return 0;
    }
}
