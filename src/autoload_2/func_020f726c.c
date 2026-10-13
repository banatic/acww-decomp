/* func_020f726c @ 0x020f726c, 0x4c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern char data_021fd1bc[];
extern int func_020f1d3c(void *address, int arg);
extern void NNS_SndArcPlayerStartSeq(void *address, unsigned short val);

struct UnkStruct_020f726c {
    unsigned char pad_00[4];
    unsigned char data[9];
    unsigned char d;
    unsigned char e;
    unsigned char unk_0F;
};

void func_020f726c(struct UnkStruct_020f726c *s)
{
    s->d = 0;
    s->e = (unsigned char) func_020f1d3c(data_021fd1bc, 3);
    s->unk_0F = 0;
    NNS_SndArcPlayerStartSeq(s->data, (unsigned short) (s->e + 0xad));
}
