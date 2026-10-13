/* func_ov066_02267530 @ 0x02267530, 0xdc bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned char unk_08;
    unsigned char unk_09;
    unsigned char unk_0A;
    unsigned char unk_0B;
    unsigned char unk_0C;
    unsigned char unk_0D;
    unsigned int unk_10;
    unsigned char pad_14[1];
    unsigned char unk_15;
    unsigned char unk_16;
    unsigned char pad_17[25];
    unsigned int unk_30;
    unsigned int unk_34;
    unsigned int unk_38;
    unsigned int unk_3C;
} Ov66Struct;

extern Ov66Struct *data_ov066_0226bdec;

void func_ov066_02267530(unsigned char arg0)
{
    data_ov066_0226bdec->unk_00 = 7;
    data_ov066_0226bdec->unk_04 = 1;
    data_ov066_0226bdec->unk_08 = 0xfe;
    data_ov066_0226bdec->unk_09 = 1;
    data_ov066_0226bdec->unk_0A = 0;
    data_ov066_0226bdec->unk_0B = 0;
    data_ov066_0226bdec->unk_0C = 0;
    data_ov066_0226bdec->unk_0D = arg0;
    data_ov066_0226bdec->unk_10 = 0;
    data_ov066_0226bdec->unk_15 = 0;
    data_ov066_0226bdec->unk_16 = 0;
    data_ov066_0226bdec->unk_30 = 0;
    data_ov066_0226bdec->unk_34 = 0;
    data_ov066_0226bdec->unk_38 = 0;
    data_ov066_0226bdec->unk_3C &= ~0x800;
    data_ov066_0226bdec->unk_3C &= ~0x400;
    data_ov066_0226bdec->unk_3C &= ~0x1000;
    data_ov066_0226bdec->unk_3C &= ~0x800;
}
