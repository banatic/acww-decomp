/* func_ov066_0226bc4c @ 0x0226bc4c, 0x16c bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,s
 */

typedef struct Src {
    int unk_00;
    unsigned char unk_04;
    unsigned char unk_05;
    unsigned char unk_06;
    unsigned char unk_07;
} Src;

typedef struct UnkStruct_0226bc4c {
    char pad_00[8];
    unsigned char unk_08;
    unsigned char unk_09;
    unsigned char unk_0A;
    unsigned char unk_0B;
    unsigned char unk_0C;
    char pad_0D[0x14 - 0xd];
    unsigned char unk_14;
    char pad_15[0x17 - 0x15];
    unsigned char unk_17;
    unsigned short unk_18;
    unsigned short unk_1A;
    unsigned short unk_1C;
    unsigned short unk_1E;
    unsigned short unk_20;
    unsigned short unk_22;
    unsigned short unk_24;
    char pad_26[0x28 - 0x26];
    int unk_28;
    char pad_2C[0x3c - 0x28 - 4];
    unsigned int unk_3C;
} UnkStruct_0226bc4c;

extern UnkStruct_0226bc4c *data_ov066_0226bdec;

void func_ov066_0226bc4c(Src *p)
{
    unsigned short a = p->unk_06;
    unsigned char b = p->unk_04;
    unsigned short mulval = (unsigned short) (a * b + 4);

    data_ov066_0226bdec->unk_28 = p->unk_00;
    data_ov066_0226bdec->unk_3C &= ~8;
    data_ov066_0226bdec->unk_3C &= ~1;
    data_ov066_0226bdec->unk_3C |= 0x20;
    data_ov066_0226bdec->unk_3C |= 0x40;
    data_ov066_0226bdec->unk_3C |= 0x80;
    data_ov066_0226bdec->unk_3C &= ~0x200;
    data_ov066_0226bdec->unk_3C &= ~0x100;
    data_ov066_0226bdec->unk_3C |= 4;
    data_ov066_0226bdec->unk_3C |= 2;

    data_ov066_0226bdec->unk_17 = p->unk_07;
    data_ov066_0226bdec->unk_08 = 0xfe;
    data_ov066_0226bdec->unk_09 = 1;
    data_ov066_0226bdec->unk_0A = p->unk_04 - 1;
    data_ov066_0226bdec->unk_0B = p->unk_04;
    data_ov066_0226bdec->unk_0C = p->unk_05;
    data_ov066_0226bdec->unk_18 = a;
    data_ov066_0226bdec->unk_1A = mulval;
    data_ov066_0226bdec->unk_1C = mulval;
    data_ov066_0226bdec->unk_1E = a;
    data_ov066_0226bdec->unk_22 = 0x1e;
    data_ov066_0226bdec->unk_20 = 0x5a;
    data_ov066_0226bdec->unk_24 = 0xc8;
    data_ov066_0226bdec->unk_14 = 4;
}
