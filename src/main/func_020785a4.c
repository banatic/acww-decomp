/* func_020785a4 @ 0x020785a4, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[2];
    unsigned char unk_02;
    unsigned char unk_03;
} UnkStruct_020785a4;

extern unsigned short func_02077898(const UnkStruct_020785a4 *in);

void func_020785a4(int *out0, unsigned char *out1, unsigned short *out2, int *out3, unsigned char *out4,
                   const UnkStruct_020785a4 *in)
{
    *out0 = (in->unk_02 >> 4) & 0xF;
    *out3 = in->unk_02 & 7;
    *out4 = (in->unk_02 >> 3) & 1;
    *out1 = in->unk_03;
    *out2 = func_02077898(in);
}
