/* func_020a861c @ 0x020a861c, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short func_020a87a8(const void *arg0, int arg1);

struct UnkStruct_020a861c {
    unsigned char pad_00[0xc];
    void *unk_0C;
};

void func_020a861c(struct UnkStruct_020a861c *self, unsigned short *out)
{
    *out = func_020a87a8(self->unk_0C, 0);
}
