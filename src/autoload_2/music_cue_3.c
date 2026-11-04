/* music_cue_3: 3 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020f9f98 @ 0x020f9f98, 0x34 bytes, ARM
 * func_020f9f74 @ 0x020f9f74, 0x24 bytes, ARM
 * func_020f9f48 @ 0x020f9f48, 0x2c bytes, ARM
 */

struct UnkStruct_020f9f74 {
    char pad_00[0xb];
    signed char unk_0B;
};

extern int NNS_SndPlayerReadGlobalVariable(int, short *);
extern short data_021fd26c;

unsigned char func_020f9f98(void)
{
    short v;
    NNS_SndPlayerReadGlobalVariable(2, &v);
    data_021fd26c = v;
    return (unsigned char) v;
}

void func_020f9f74(struct UnkStruct_020f9f74 *p, int value)
{
    signed char tmp;
    p->unk_0B = value;
    p->unk_0B--;
    tmp = p->unk_0B;
    if (tmp < 0) {
        tmp = 15;
    }
    p->unk_0B = tmp;
}

int func_020f9f48(void *r0)
{
    int r2;
    unsigned char r1;

    r2 = -1;
    r1 = *(unsigned char *) ((char *) r0 + 8);
    if (r1 == 1) {
        r1 = *(unsigned char *) ((char *) r0 + 0xf);
        if (r1 == 0) {
            *(unsigned char *) ((char *) r0 + 0xf) = 1;
            r2 = 3;
        }
    }
    return r2;
}
