/* func_ov111_0229efd8 @ 0x0229efd8, 0x12 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0xa4 {
    char pad_00[0xa4];
    unsigned short flags;
};
int func_ov111_0229efd8(struct UnkStruct_0xa4 *self, unsigned int mask)
{
    return (self->flags & mask) != 0;
}
