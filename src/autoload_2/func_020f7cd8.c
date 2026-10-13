/* func_020f7cd8 @ 0x020f7cd8, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void NNS_SndPlayerSetVolume(void *p, int n);

struct UnkStruct_020f7cd8 {
    int pad_00;
    int unk_04;
    int unk_08;
    unsigned char flag;
};

void func_020f7cd8(struct UnkStruct_020f7cd8 *self, unsigned char ch)
{
    self->flag = ch;
    NNS_SndPlayerSetVolume(&self->unk_04, 0x7f);
    NNS_SndPlayerSetVolume(&self->unk_08, 0x7f);
}
