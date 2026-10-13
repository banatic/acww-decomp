/* func_020f1d3c @ 0x020f1d3c, 0x48 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x54];
    volatile unsigned int unk_54;
    unsigned int unk_58;
    unsigned int unk_5C;
} UnkStruct_020f1d3c;

unsigned int func_020f1d3c(UnkStruct_020f1d3c *self, unsigned int arg)
{
    self->unk_54 = self->unk_5C + self->unk_58 * self->unk_54;
    if (arg == 0) {
        return (self->unk_54 >> 16) << 16 >> 16;
    } else {
        return (((self->unk_54 >> 16) * arg) >> 16) << 16 >> 16;
    }
}
