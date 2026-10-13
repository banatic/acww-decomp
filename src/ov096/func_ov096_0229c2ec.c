/* func_ov096_0229c2ec @ 0x0229c2ec, 0xe bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x94];
    unsigned int flags;
} UnkStruct_0229c2ec;

void func_ov096_0229c2ec(UnkStruct_0229c2ec *self, unsigned int bits)
{
    self->flags |= bits;
}
