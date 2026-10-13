/* func_ov094_022999b0 @ 0x022999b0, 0x10 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022999b0 {
    unsigned char pad_00[8];
    unsigned short value;
};

int func_ov094_022999b0(struct UnkStruct_022999b0 *s, int mask)
{
    if ((s->value & mask) != 0) {
        return 1;
    }
    return 0;
}
