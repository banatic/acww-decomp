/* func_ov140_02299fb0 @ 0x02299fb0, 0x18 bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02299fb0 {
    unsigned char pad_00[0x8ac];
    unsigned short flags;
};

int func_ov140_02299fb0(struct UnkStruct_02299fb0 *self, int mask)
{
    if ((self->flags & mask) != 0) {
        return 1;
    }
    return 0;
}
