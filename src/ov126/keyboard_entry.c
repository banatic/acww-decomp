/* keyboard_entry: 3 functions, module ov126
 * mwccarm 1.2/base -O4,s
 * func_ov126_0229f7c8 @ 0x0229f7c8, 0x12 bytes, Thumb
 * func_ov126_0229f7b8 @ 0x0229f7b8, 0xe bytes, Thumb
 * func_ov126_0229f7a8 @ 0x0229f7a8, 0xe bytes, Thumb
 */

struct UnkStruct_0229f7c8 {
    char pad_00[0xa4];
    unsigned short flags;
};

struct UnkStruct_0229f7b8 {
    char pad_00[0xa4];
    unsigned short unk_A4;
};

struct UnkStruct_0229f7a8 {
    unsigned char pad_00[0xa4];
    unsigned short unk_A4;
};

int func_ov126_0229f7c8(struct UnkStruct_0229f7c8 *s, unsigned int mask)
{
    return (s->flags & mask) != 0;
}

void func_ov126_0229f7b8(struct UnkStruct_0229f7b8 *p, unsigned short v)
{
    p->unk_A4 |= v;
}

void func_ov126_0229f7a8(struct UnkStruct_0229f7a8 *self, unsigned short mask)
{
    self->unk_A4 &= ~mask;
}
