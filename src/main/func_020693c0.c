/* func_020693c0 @ 0x020693c0, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206b97c(void *self, unsigned int offset);

struct UnkStruct_020693c0 {
    unsigned char pad_00[0x24];
    unsigned int unk_24;
};

int func_020693c0(struct UnkStruct_020693c0 *self)
{
    return func_0206b97c(self, self->unk_24 + 0x18ac);
}
