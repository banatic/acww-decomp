/* sound_object_kinds_3: 4 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020f7d14 @ 0x020f7d14, 0x38 bytes, ARM
 * func_020f7d04 @ 0x020f7d04, 0x10 bytes, ARM
 * func_020f7cd8 @ 0x020f7cd8, 0x2c bytes, ARM
 * func_020f7cb0 @ 0x020f7cb0, 0x28 bytes, ARM
 */

struct UnkStruct_020f7cd8 {
    int pad_00;
    int unk_04;
    int unk_08;
    unsigned char flag;
};

extern int func_020eed18(void *ptr, int val);
extern void NNS_SndHandleReleaseSeq(void *ptr);
extern void func_020f7c1c(int, int);
extern void NNS_SndPlayerSetVolume(void *p, int n);

void func_020f7d14(void *self)
{
    func_020eed18((char *) self + 4, 0);
    func_020eed18((char *) self + 8, 0);
    NNS_SndHandleReleaseSeq((char *) self + 4);
    NNS_SndHandleReleaseSeq((char *) self + 8);
}

void func_020f7d04(int a, int b, int c)
{
    func_020f7c1c(a, c);
}

void func_020f7cd8(struct UnkStruct_020f7cd8 *self, unsigned char ch)
{
    self->flag = ch;
    NNS_SndPlayerSetVolume(&self->unk_04, 0x7f);
    NNS_SndPlayerSetVolume(&self->unk_08, 0x7f);
}

void func_020f7cb0(void *p)
{
    NNS_SndPlayerSetVolume((char *) p + 4, 0);
    NNS_SndPlayerSetVolume((char *) p + 8, 0);
}
