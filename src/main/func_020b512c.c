/* func_020b512c @ 0x020b512c, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x24];
    signed char *base;
    unsigned char pad_28[0x3c - 0x28];
    int unk_3C;
    int count;
    unsigned char flag44;
    unsigned char flag45;
} UnkStruct_020b512c;

void func_020b512c(UnkStruct_020b512c *self)
{
    int f = self->unk_3C;
    signed char b0 = (signed char) (f & 0xff);
    signed char b1 = (signed char) ((f >> 8) & 0xff);
    int count = self->count;

    if ((unsigned int) (0xa00 - count) > 2) {
        self->count = count + 1;
        *(self->base + count + 0xafc) = b0;
        count = self->count;
        self->count = count + 1;
        *(self->base + count + 0xafc) = b1;
    } else {
        self->flag45 = 0;
    }
}
