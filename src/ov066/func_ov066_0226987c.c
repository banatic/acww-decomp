/* func_ov066_0226987c @ 0x0226987c, 0x70 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,s
 */

struct Dest {
    unsigned short unk_00;
    unsigned short unk_02;
    unsigned char unk_04;
    unsigned char unk_05;
    unsigned char unk_06;
};

struct GStruct {
    unsigned char pad_00[8];
    struct Dest *dest;
    unsigned char pad_0C[0x95 - 12];
    unsigned char unk_95;
};

extern struct GStruct *data_ov066_0226bdf4;
extern unsigned int data_ov066_0226bdf8;

void func_ov066_0226987c(unsigned int arg0, unsigned char arg1)
{
    struct Dest *d = data_ov066_0226bdf4->dest;
    if (arg0 != 0xe34d) {
        d->unk_00 = (unsigned short) arg0;
    }
    data_ov066_0226bdf8 = data_ov066_0226bdf8 * 0x5eedf715 + 0x1b0cb173;
    d->unk_02 = (unsigned short) data_ov066_0226bdf8;
    d->unk_04 = data_ov066_0226bdf4->unk_95;
    d->unk_05 = arg1;
    d->unk_06 = 5;
}
