/* func_ov112_0229fe60 @ 0x0229fe60, 0xe bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229fe60 {
    unsigned char pad_00[0xac];
    unsigned int flags;
};

void func_ov112_0229fe60(struct UnkStruct_0229fe60 *self, unsigned int mask)
{
    self->flags |= mask;
}
