/* func_ov142_0229ae8c @ 0x0229ae8c, 0x38 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229ae8c {
    unsigned char pad_00[0xbb];
    unsigned char index;
};

void *func_ov142_0229ae8c(struct UnkStruct_0229ae8c *self)
{
    if (self->index >= 14) {
        return (char *) self + 0x8dc;
    } else {
        self->index++;
        return (char *) self + 0x360 + 108 * (self->index - 1);
    }
}
