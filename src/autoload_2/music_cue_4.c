/* music_cue_4: 2 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020fa054 @ 0x020fa054, 0x3c bytes, ARM
 * func_020fa034 @ 0x020fa034, 0x20 bytes, ARM
 */

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

extern void func_020eed48(void *resource);
extern int func_020eed18(void *arg, int value);
extern void NNS_SndHandleReleaseSeq(void *arg);

void func_020fa054(struct ResSet *self, unsigned short val)
{
    func_020eed48(self);
    self->unk_04 = val;
    self->unk_06 = 0;
    self->unk_0D = -1;
    self->unk_0F = 0;
    self->unk_10 = 0;
}

void func_020fa034(void *arg)
{
    func_020eed18(arg, 0);
    NNS_SndHandleReleaseSeq(arg);
}
