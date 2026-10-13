/* func_020bec40 @ 0x020bec40, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020bec40 {
    unsigned short pad_00[4];
    unsigned short unk_08;
};

int func_020bec40(struct UnkStruct_020bec40 *p, int bit)
{
    return (p->unk_08 & (1 << bit)) ? 1 : 0;
}
