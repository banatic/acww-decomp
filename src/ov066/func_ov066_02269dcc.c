/* func_ov066_02269dcc @ 0x02269dcc, 0x1a0 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

struct UnkStruct_02269dcc {
    char pad_00[0x1e];
    unsigned short unk_1E;
    char pad_20[0x28 - 0x20];
    unsigned char arr28[16][6];
    char pad_88[0x8c - 0x88];
    unsigned char unk_8C;
    unsigned char unk_8D;
    unsigned char unk_8E;
    unsigned char unk_8F;
    char pad_90[0xc0 - 0x90];
    unsigned int unk_C0;
};
extern struct UnkStruct_02269dcc *data_ov066_0226bdf4;
struct UnkStruct_02269dcc_2 {
    char pad_00[8];
    unsigned char unk_08;
};
extern struct UnkStruct_02269dcc_2 *data_ov066_0226bdec;
extern void MI_CpuFill8(void *buf, int mode, int len);
void func_ov066_02269dcc(void)
{
    unsigned char buf[6];
    int i;
    data_ov066_0226bdf4->unk_1E = 0xffff;
    data_ov066_0226bdf4->unk_8C = 1;
    data_ov066_0226bdf4->unk_C0 &= ~1u;
    data_ov066_0226bdf4->unk_C0 &= ~2u;
    data_ov066_0226bdf4->unk_C0 &= ~4u;
    data_ov066_0226bdf4->unk_C0 &= ~8u;
    data_ov066_0226bdf4->unk_C0 &= ~0x10u;
    data_ov066_0226bdf4->unk_C0 &= ~0x20u;
    data_ov066_0226bdf4->unk_C0 &= ~0x40u;
    data_ov066_0226bdf4->unk_C0 &= ~0x400u;
    if (((unsigned char) (data_ov066_0226bdec->unk_08 + 2)) <= 1) {
        data_ov066_0226bdf4->unk_C0 |= 0x80;
        data_ov066_0226bdf4->unk_8D = 0;
        data_ov066_0226bdf4->unk_8E = 0;
        data_ov066_0226bdf4->unk_8F = 0;
    } else {
        data_ov066_0226bdf4->unk_C0 &= ~0x80u;
        data_ov066_0226bdf4->unk_8D = data_ov066_0226bdec->unk_08;
        data_ov066_0226bdf4->unk_8E = 0;
        data_ov066_0226bdf4->unk_8F = data_ov066_0226bdec->unk_08;
    }
    MI_CpuFill8(buf, 0, 6);
    {
        typedef struct {
            unsigned char a, b;
        } Pair;
        unsigned char *p = (unsigned char *) data_ov066_0226bdf4;
        for (i = 0; i < 16; i++) {
            *(Pair *) &p[0x28] = *(Pair *) &buf[0];
            *(Pair *) &p[0x2a] = *(Pair *) &buf[2];
            *(Pair *) &p[0x2c] = *(Pair *) &buf[4];
            p += 6;
        }
    }
}
