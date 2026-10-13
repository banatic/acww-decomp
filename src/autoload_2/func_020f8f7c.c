/* func_020f8f7c @ 0x020f8f7c, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

struct Func020f8f7cStruct {
    unsigned char pad_00[8];
    unsigned char unk_08[6];
    short unk_0E;
    int unk_10;
};

extern void NNS_SndArcPlayerStartSeq(void *ptr, int value);

void func_020f8f7c(struct Func020f8f7cStruct *self)
{
    NNS_SndArcPlayerStartSeq(self->unk_08, 0xf6);
    self->unk_0E = -1;
    self->unk_10 = 0;
}
