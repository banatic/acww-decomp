/* func_ov126_0229f7c8 @ 0x0229f7c8, 0x12 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229f7c8 {
    char pad_00[0xa4];
    unsigned short flags;
};

int func_ov126_0229f7c8(struct UnkStruct_0229f7c8 *s, unsigned int mask)
{
    return (s->flags & mask) != 0;
}
