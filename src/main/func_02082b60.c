/* func_02082b60 @ 0x02082b60, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02082b60 {
    int unk_00;
    unsigned short unk_04;
};

int func_02082b60(int unused, const struct UnkStruct_02082b60 *p)
{
    if (p->unk_00 != 0 && ((p->unk_04 & 0xf000) >> 12) == 0xe) {
        return 1;
    }
    return 0;
}
