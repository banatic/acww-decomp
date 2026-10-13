/* func_0201acbc @ 0x0201acbc, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char unk_00;
    unsigned char pad_01[3];
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    unsigned char unk_18;
    unsigned char pad_19[3];
    unsigned short unk_1C;
    unsigned short unk_1E;
    unsigned char pad_20[4];
    unsigned short unk_24;
    unsigned short unk_26;
    unsigned char pad_28[2];
    unsigned char unk_2A;
    unsigned char pad_2B[0x5c - 0x2b];
    unsigned int unk_5C;
    unsigned char unk_60;
    unsigned char pad_61[3];
    unsigned int unk_64;
} UnkStruct_0201acbc;

void func_0201acbc(UnkStruct_0201acbc *self, int val, unsigned short a, unsigned short b, signed short c, signed short d)
{
    if (self->unk_18 != 0) {
        return;
    }
    if (self->unk_14 == 4) {
        return;
    }
    if (val < self->unk_14) {
        return;
    }

    self->unk_00 = 5;
    self->unk_04 = 0;
    self->unk_08 = 0;
    self->unk_0C = 0;
    self->unk_10 = 0;
    self->unk_14 = val;
    self->unk_2A = 0;
    self->unk_5C = 0x8000;
    self->unk_60 = 1;
    self->unk_64 = 4;
    self->unk_1E = a;
    self->unk_26 = b;
    self->unk_1C = (unsigned short) c;
    self->unk_24 = (unsigned short) d;
}
