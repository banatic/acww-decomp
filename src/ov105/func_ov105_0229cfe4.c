/* func_ov105_0229cfe4 @ 0x0229cfe4, 0x10 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229cfe4 {
    unsigned char pad_00[0x2ba];
    unsigned char byte;
};

extern int func_ov105_0229d4c4(struct UnkStruct_0229cfe4 *self, unsigned char byte);

int func_ov105_0229cfe4(struct UnkStruct_0229cfe4 *self)
{
    return func_ov105_0229d4c4(self, self->byte);
}
