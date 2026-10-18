/* func_020069f0 @ 0x020069f0, 0x974 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Obj_020d82b4.h"

typedef void (Obj_020d82b4::*PMF)(int);

typedef struct UnkStruct_020069f0 UnkStruct_020069f0;
struct UnkStruct_020069f0 {
    short unk_00;
    short unk_02;
    int unk_04;
};

extern "C" int func_02096518(int *, int, int);
extern "C" int func_0200f290(Obj_020d82b4 *, int);
extern "C" void func_0200f268(Obj_020d82b4 *, int);
extern "C" UnkStruct_020069f0 *func_020966c4(int);
extern "C" int func_0200ea0c(Obj_020d82b4 *, int);
extern "C" int func_020778c8(short *);
extern "C" void MI_CpuCopy8(void *, void *, unsigned int);

extern int data_021bfff8;
extern PMF data_020d732c, data_020d73cc, data_020d740c, data_020d7414, data_020d748c, data_020d76cc, data_020d770c,
    data_020d774c, data_020d7754, data_020d775c, data_020d7764, data_020d776c, data_020d7774, data_020d777c, data_020d7784,
    data_020d778c, data_020d7794, data_020d779c, data_020d77a4, data_020d77ac, data_020d77b4, data_020d77bc, data_020d77c4,
    data_020d77cc, data_020d77d4, data_020d77dc, data_020d77e4, data_020d77ec, data_020d77f4, data_020d77fc, data_020d7804,
    data_020d780c, data_020d7814, data_020d781c, data_020d7824, data_020d782c, data_020d7834, data_020d783c, data_020d7844,
    data_020d7854, data_020d785c, data_020d7864, data_020d786c, data_020d7874, data_020d787c, data_020d7884, data_020d788c,
    data_020d7894, data_020d789c, data_020d78a4, data_020d78ac, data_020d78b4, data_020d78bc, data_020d78c4, data_020d78cc,
    data_020d78d4, data_020d78dc, data_020d78e4, data_020d78ec, data_020d78f4, data_020d78fc, data_020d7904, data_020d790c,
    data_020d7914, data_020d791c, data_020d7924, data_020d792c, data_020d7934, data_020d793c, data_020d7944, data_020d7954,
    data_020d795c, data_020d7964, data_020d7984, data_020d798c, data_020d7994, data_020d799c, data_020d79a4, data_020d79ac,
    data_020d79b4, data_020d79bc, data_020d79c4, data_020d79cc, data_020d79d4, data_020d79dc, data_020d79e4, data_020d79ec,
    data_020d79f4, data_020d79fc, data_020d7a04, data_020d7a0c, data_020d7a14, data_020d7a1c, data_020d7a24, data_020d7a2c,
    data_020d7a34, data_020d7a3c, data_020d7a44, data_020d7a74, data_020d7a8c, data_020d7a94, data_020d7a9c, data_020d7aac,
    data_020d7abc, data_020d7ad4, data_020d7adc, data_020d7ae4, data_020d7aec, data_020d7af4, data_020d7afc, data_020d7b04,
    data_020d7b0c, data_020d7b14, data_020d7b1c, data_020d7b24, data_020d7b2c, data_020d7b34, data_020d7b3c, data_020d7b44,
    data_020d7b54, data_020d7b5c, data_020d7b64, data_020d7b6c, data_020d7b74, data_020d7b7c, data_020d7b84, data_020d7b8c,
    data_020d7b94, data_020d7b9c, data_020d7ba4, data_020d7bac, data_020d7bb4, data_020d7bbc, data_020d7bc4, data_020d7bcc,
    data_020d7bd4, data_020d7bdc, data_020d7c0c, data_020d7c14, data_020d804c, data_020d8094, data_020d809c, data_020d80a4,
    data_020d80ac, data_020d8254, data_020d827c, data_020d8284;
extern PMF data_021c0948[147];

extern "C" void func_020069f0(Obj_020d82b4 *self)
{
    int v;
    int a;
    int b;
    UnkStruct_020069f0 *p;

    if (func_02096518(&v, -1, self->unk_800) == 0) {
        self->unk_8F8 = 147;
        return;
    }
    if (v >= 147) {
        self->unk_8F8 = 147;
        return;
    }
    if (func_0200f290(self, 0x12)) {
        if (v != 0x1a) {
            return;
        }
        if (self->unk_7F0 != 0x19) {
            return;
        }
        func_0200f268(self, 0x12);
    }
    self->unk_8F8 = v;
    p = func_020966c4(self->unk_800);
    if (p) {
        MI_CpuCopy8(&p->unk_04, self->unk_8F0, 8);
    }
    a = func_0200ea0c(self, self->unk_7F0);
    b = func_0200ea0c(self, v);
    if (a == 1 && b == 1) {
        return;
    }
    if (b == 1) {
        v = 2;
    }
    a = -1;
    p = func_020966c4(self->unk_800);
    if (p) {
        a = func_020778c8(&p->unk_02);
    }
    if (self->unk_C84 >= 0 && self->unk_C88 == v && a == self->unk_C84) {
        return;
    }
    {
        if (!(data_021bfff8 & 1)) {
            data_021c0948[0] = data_020d7bdc;
            data_021c0948[1] = data_020d770c;
            data_021c0948[2] = data_020d748c;
            data_021c0948[3] = data_020d7bc4;
            data_021c0948[4] = data_020d7bbc;
            data_021c0948[5] = data_020d7bb4;
            data_021c0948[6] = data_020d7bac;
            data_021c0948[7] = data_020d7ba4;
            data_021c0948[8] = data_020d7b9c;
            data_021c0948[9] = data_020d7b94;
            data_021c0948[10] = data_020d7b8c;
            data_021c0948[11] = data_020d7b84;
            data_021c0948[12] = data_020d7b7c;
            data_021c0948[13] = data_020d7b74;
            data_021c0948[14] = data_020d7b6c;
            data_021c0948[15] = data_020d7b64;
            data_021c0948[16] = data_020d7b5c;
            data_021c0948[17] = data_020d7b54;
            data_021c0948[18] = data_020d76cc;
            data_021c0948[19] = data_020d7b44;
            data_021c0948[20] = data_020d7b3c;
            data_021c0948[21] = data_020d7b34;
            data_021c0948[22] = data_020d7b2c;
            data_021c0948[23] = data_020d7b24;
            data_021c0948[24] = data_020d7b1c;
            data_021c0948[25] = data_020d7b14;
            data_021c0948[26] = data_020d7b0c;
            data_021c0948[27] = data_020d7b04;
            data_021c0948[28] = data_020d7afc;
            data_021c0948[29] = data_020d7af4;
            data_021c0948[30] = data_020d7aec;
            data_021c0948[31] = data_020d7ae4;
            data_021c0948[32] = data_020d7adc;
            data_021c0948[33] = data_020d7ad4;
            data_021c0948[34] = data_020d7414;
            data_021c0948[35] = data_020d732c;
            data_021c0948[36] = data_020d80a4;
            data_021c0948[37] = data_020d7a74;
            data_021c0948[38] = data_020d7a8c;
            data_021c0948[39] = data_020d7a94;
            data_021c0948[40] = data_020d7a9c;
            data_021c0948[41] = data_020d7aac;
            data_021c0948[42] = data_020d7abc;
            data_021c0948[43] = data_020d7bcc;
            data_021c0948[44] = data_020d7bd4;
            data_021c0948[45] = data_020d7c0c;
            data_021c0948[46] = data_020d7c14;
            data_021c0948[47] = data_020d827c;
            data_021c0948[48] = data_020d804c;
            data_021c0948[49] = data_020d8254;
            data_021c0948[50] = data_020d8284;
            data_021c0948[51] = data_020d7a44;
            data_021c0948[52] = data_020d7a3c;
            data_021c0948[53] = data_020d7a34;
            data_021c0948[54] = data_020d7a2c;
            data_021c0948[55] = data_020d7a24;
            data_021c0948[56] = data_020d7a1c;
            data_021c0948[57] = data_020d7a14;
            data_021c0948[58] = data_020d7a0c;
            data_021c0948[59] = data_020d7a04;
            data_021c0948[60] = data_020d79fc;
            data_021c0948[61] = data_020d79f4;
            data_021c0948[62] = data_020d79ec;
            data_021c0948[63] = data_020d79e4;
            data_021c0948[64] = data_020d79dc;
            data_021c0948[65] = data_020d79d4;
            data_021c0948[66] = data_020d79cc;
            data_021c0948[67] = data_020d79c4;
            data_021c0948[68] = data_020d79bc;
            data_021c0948[69] = data_020d79b4;
            data_021c0948[70] = data_020d79ac;
            data_021c0948[71] = data_020d79a4;
            data_021c0948[72] = data_020d799c;
            data_021c0948[73] = data_020d7994;
            data_021c0948[74] = data_020d798c;
            data_021c0948[75] = data_020d7984;
            data_021c0948[76] = data_020d80ac;
            data_021c0948[77] = data_020d809c;
            data_021c0948[78] = data_020d8094;
            data_021c0948[79] = data_020d7964;
            data_021c0948[80] = data_020d795c;
            data_021c0948[81] = data_020d7954;
            data_021c0948[82] = data_020d740c;
            data_021c0948[83] = data_020d7944;
            data_021c0948[84] = data_020d793c;
            data_021c0948[85] = data_020d7934;
            data_021c0948[86] = data_020d792c;
            data_021c0948[87] = data_020d7924;
            data_021c0948[88] = data_020d791c;
            data_021c0948[89] = data_020d7914;
            data_021c0948[90] = data_020d790c;
            data_021c0948[91] = data_020d7904;
            data_021c0948[92] = data_020d78fc;
            data_021c0948[93] = data_020d78f4;
            data_021c0948[94] = data_020d78ec;
            data_021c0948[95] = data_020d78e4;
            data_021c0948[96] = data_020d78dc;
            data_021c0948[97] = data_020d78d4;
            data_021c0948[98] = data_020d78cc;
            data_021c0948[99] = data_020d78c4;
            data_021c0948[100] = data_020d78bc;
            data_021c0948[101] = data_020d78b4;
            data_021c0948[102] = data_020d78ac;
            data_021c0948[103] = data_020d78a4;
            data_021c0948[104] = data_020d789c;
            data_021c0948[105] = data_020d7894;
            data_021c0948[106] = data_020d788c;
            data_021c0948[107] = data_020d7884;
            data_021c0948[108] = data_020d787c;
            data_021c0948[109] = data_020d7874;
            data_021c0948[110] = data_020d786c;
            data_021c0948[111] = data_020d7864;
            data_021c0948[112] = data_020d785c;
            data_021c0948[113] = data_020d7854;
            data_021c0948[114] = data_020d73cc;
            data_021c0948[115] = data_020d7844;
            data_021c0948[116] = data_020d783c;
            data_021c0948[117] = data_020d7834;
            data_021c0948[118] = data_020d782c;
            data_021c0948[119] = data_020d7824;
            data_021c0948[120] = data_020d781c;
            data_021c0948[121] = data_020d7814;
            data_021c0948[122] = data_020d780c;
            data_021c0948[123] = data_020d7804;
            data_021c0948[124] = data_020d77fc;
            data_021c0948[125] = data_020d77f4;
            data_021c0948[126] = data_020d77ec;
            data_021c0948[127] = data_020d77e4;
            data_021c0948[128] = data_020d77dc;
            data_021c0948[129] = data_020d77d4;
            data_021c0948[130] = data_020d77cc;
            data_021c0948[131] = data_020d77c4;
            data_021c0948[132] = data_020d77bc;
            data_021c0948[133] = data_020d77b4;
            data_021c0948[134] = data_020d77ac;
            data_021c0948[135] = data_020d77a4;
            data_021c0948[136] = data_020d779c;
            data_021c0948[137] = data_020d7794;
            data_021c0948[138] = data_020d778c;
            data_021c0948[139] = data_020d7784;
            data_021c0948[140] = data_020d777c;
            data_021c0948[141] = data_020d7774;
            data_021c0948[142] = data_020d776c;
            data_021c0948[143] = data_020d7764;
            data_021c0948[144] = data_020d775c;
            data_021c0948[145] = data_020d7754;
            data_021c0948[146] = data_020d774c;
            data_021bfff8 |= 1;
        }
        (self->*data_021c0948[v])(a);
    }
}
