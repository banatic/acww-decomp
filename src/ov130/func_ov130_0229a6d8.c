/* func_ov130_0229a6d8 @ 0x0229a6d8, 0xb6 bytes, Thumb, module ov130
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned short unk_00;
    unsigned char unk_02;
    unsigned char unk_03;
    unsigned char unk_04;
    unsigned char unk_05;
    unsigned char unk_06;
    unsigned char unk_07;
    unsigned char unk_08;
    unsigned char unk_09;
    unsigned char unk_0A;
    unsigned char unk_0B;
    unsigned int unk_0C;
    unsigned int unk_10;
    unsigned int unk_14;
    unsigned int unk_18;
} UnkStruct_0229a6d8;

extern void func_ov130_022999e4(UnkStruct_0229a6d8 *self);
extern int func_020984e8(void);
extern void func_02099870(void);
extern int func_020950c0(void);
extern void func_0200458c(int);

void func_ov130_0229a6d8(UnkStruct_0229a6d8 *self, unsigned char idx, unsigned char arg2, unsigned char arg3)
{
    self->unk_00 = 0;
    self->unk_07 = idx;

    switch (self->unk_07) {
        case 0:
            self->unk_08 = 2;
            self->unk_09 = 0;
            break;
        case 1:
            self->unk_08 = 2;
            self->unk_09 = 5;
            break;
        case 2:
            self->unk_08 = 2;
            self->unk_09 = 1;
            break;
        case 3:
            self->unk_08 = 3;
            self->unk_09 = 2;
            break;
        case 4:
            self->unk_08 = 5;
            self->unk_09 = 3;
            break;
        case 5:
            self->unk_08 = 3;
            self->unk_09 = 4;
            break;
        case 6:
            self->unk_08 = 4;
            self->unk_09 = 6;
            break;
        default:
            break;
    }

    self->unk_0A = arg2;
    self->unk_0B = arg3;

    func_ov130_022999e4(self);

    self->unk_05 = 10;
    self->unk_04 = 13;
    self->unk_03 = 0;
    self->unk_02 = 0;
    self->unk_0C = 0;
    self->unk_10 = 0;
    self->unk_14 = 0;
    self->unk_18 = 0;

    if (func_020984e8() != 0 && (func_02099870(), func_020950c0() == 0)) {
        func_0200458c(0);
    } else {
        func_0200458c(1);
    }
}