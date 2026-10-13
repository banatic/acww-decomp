/* func_020574a0 @ 0x020574a0, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct StructName {
    char pad_00[4];
    signed char unk_04;
};

int func_020574a0(struct StructName *s)
{
    if (s->unk_04 == -1) {
        return 0;
    }
    return 1;
}
