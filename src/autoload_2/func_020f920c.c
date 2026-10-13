/* func_020f920c @ 0x020f920c, 0xc4 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern int data_021fd1f8;
extern void NNS_SndPlayerReadVariable(void *player, int var, short *out);

typedef struct {
    char pad_00[0x16];
    char unk_16;
    char unk_17;
    char unk_18;
    char pad_19[0x13];
    short unk_2C;
    unsigned char unk_2E;
} UnkStruct_020f920c;

void func_020f920c(UnkStruct_020f920c *out)
{
    unsigned int valid;
    short vars[4];
    int *p = &data_021fd1f8;

    valid = (*p != 0);
    if (valid == 0) {
        return;
    }

    NNS_SndPlayerReadVariable(p, 1, &vars[0]);
    NNS_SndPlayerReadVariable(p, 0, &vars[1]);
    NNS_SndPlayerReadVariable(p, 2, &vars[2]);
    NNS_SndPlayerReadVariable(p, 3, &vars[3]);

    out->unk_16 = vars[1];
    out->unk_17 = vars[2];
    out->unk_18 = vars[3];

    if (out->unk_2C > vars[0]) {
        out->unk_2E = (out->unk_2E == 0) ? 1 : 0;
    }
    out->unk_2C = vars[0];
}
