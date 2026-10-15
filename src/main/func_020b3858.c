/* func_020b3858 @ 0x020b3858, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct func_020b3858_s {
    unsigned char pad_00[0x234];
    unsigned char unk_234;
};

int func_020b3858(struct func_020b3858_s *p)
{
    unsigned int value = p->unk_234;

    if (value >= 3) {
        p->unk_234 = value % 3;
        return func_020b3858(p);
    }
    return value;
}
