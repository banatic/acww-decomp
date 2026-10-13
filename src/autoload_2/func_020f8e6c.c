/* func_020f8e6c @ 0x020f8e6c, 0x40 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void NNS_SndPlayerReadVariable(char *ptr, int val, short *out);

struct UnkStruct_020f8e6c {
    char pad_00[8];
    char unk_08[6];
    short unk_0E;
};

int func_020f8e6c(struct UnkStruct_020f8e6c *p)
{
    short a;
    int ret;
    NNS_SndPlayerReadVariable(p->unk_08, 0, &a);
    ret = (a != p->unk_0E) ? a : -1;
    p->unk_0E = a;
    return ret;
}
