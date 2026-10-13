/* func_ov121_02299a5c @ 0x02299a5c, 0x12 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02299a5c {
    char pad_00[0xa2];
    unsigned short flags;
};

int func_ov121_02299a5c(struct UnkStruct_02299a5c *self, int mask)
{
    if (self->flags & mask) {
        return 1;
    }
    return 0;
}
