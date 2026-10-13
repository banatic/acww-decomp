/* func_ov118_0229a440 @ 0x0229a440, 0xe bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229a440 {
    unsigned char pad_00[0x9c];
    unsigned short unk_9C;
};

void func_ov118_0229a440(struct UnkStruct_0229a440 *self, unsigned int mask)
{
    self->unk_9C &= ~mask;
}
