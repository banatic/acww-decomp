/* func_020fa054 @ 0x020fa054, 0x3c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void ENV_AppendResourceSet(void *resource);

struct ResSet {
    int pad_00;
    unsigned short unk_04;
    unsigned short unk_06;
    char pad_08[5];
    signed char unk_0D;
    char pad_0E;
    unsigned char unk_0F;
    unsigned char unk_10;
};

void func_020fa054(struct ResSet *self, unsigned short val)
{
    ENV_AppendResourceSet(self);
    self->unk_04 = val;
    self->unk_06 = 0;
    self->unk_0D = -1;
    self->unk_0F = 0;
    self->unk_10 = 0;
}
