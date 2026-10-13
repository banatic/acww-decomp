/* func_ov003_0221b74c @ 0x0221b74c, 0x10 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0221b74c {
    char pad_00[0x44];
    unsigned char flag;
};

void func_ov003_0221b74c(struct UnkStruct_0221b74c *self, int a, int b, int flags)
{
    int bit;
    bit = flags & 4;
    if (bit != 0) {
        self->flag = 1;
    }
}
