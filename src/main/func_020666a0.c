/* func_020666a0 @ 0x020666a0, 0xe bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020666a0 {
    char pad_00[0x1E];
    unsigned char unk_1E;
};

int func_020666a0(struct UnkStruct_020666a0 *s, int value)
{
    if (s->unk_1E == value) {
        return 1;
    } else {
        return 0;
    }
}
