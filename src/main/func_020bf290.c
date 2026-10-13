/* func_020bf290 @ 0x020bf290, 0xe bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Input {
    char pad_00[0x34];
    unsigned int unk_34;
    unsigned int unk_38;
};

struct Output {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
};

int func_020bf290(struct Input *in, struct Output *out)
{
    out->unk_00 = in->unk_34;
    out->unk_04 = in->unk_38;
    out->unk_08 = 0;
    return 0;
}
