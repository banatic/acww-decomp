/* func_ov095_022999b0 @ 0x022999b0, 0x10 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022999b0 {
    unsigned char pad_00[20];
    unsigned short unk_14;
};

int func_ov095_022999b0(struct UnkStruct_022999b0 *p, unsigned int mask)
{
    if ((p->unk_14 & mask) != 0) {
        return 1;
    }
    return 0;
}
