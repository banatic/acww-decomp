/* func_02007364 @ 0x02007364, 0x980 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Obj_020d82b4.h"

typedef void (Obj_020d82b4::*PMF)(Msg_02007364 *, int);

struct UnkStruct_02007364 {
    char cpad[0x64];
    int unk_64;
};

extern "C" void func_02007d40(Obj_020d82b4 *, int);
extern "C" void func_02007d2c(Obj_020d82b4 *);
extern "C" void func_02007d00(Obj_020d82b4 *, int);
extern "C" int func_02008270(Obj_020d82b4 *, int, int);
extern "C" void func_02007ce4(Obj_020d82b4 *, int);
extern "C" void func_02010e48(Obj_020d82b4 *, int *);
extern "C" void func_020064cc(Obj_020d82b4 *, int);
extern "C" int func_02073dd4(UnkStruct_02007364 *, int);
extern "C" int func_02073908(UnkStruct_02007364 *, int);
extern "C" short func_02073d80(UnkStruct_02007364 *);
extern "C" int func_02008264(Obj_020d82b4 *, int);
extern "C" unsigned int *func_0200f27c(Obj_020d82b4 *, int);
extern "C" void func_0200f268(Obj_020d82b4 *, int);

extern UnkStruct_02007364 *data_020ccf94;
extern void *data_020c7e48[];

extern int data_021c0000;
extern PMF data_020d74bc, data_020d754c, data_020d75cc, data_020d772c, data_020d773c, data_020d784c, data_020d794c,
    data_020d7bfc, data_020d7c04, data_020d7c1c, data_020d7c24, data_020d7c34, data_020d7c3c, data_020d7c44, data_020d7c4c,
    data_020d7c54, data_020d7c5c, data_020d7c64, data_020d7c6c, data_020d7c74, data_020d7c7c, data_020d7c84, data_020d7c8c,
    data_020d7c94, data_020d7c9c, data_020d7ca4, data_020d7cac, data_020d7cb4, data_020d7cbc, data_020d7cc4, data_020d7ccc,
    data_020d7cd4, data_020d7cdc, data_020d7ce4, data_020d7cec, data_020d7cf4, data_020d7cfc, data_020d7d04, data_020d7d0c,
    data_020d7d14, data_020d7d1c, data_020d7d24, data_020d7d2c, data_020d7d34, data_020d7d3c, data_020d7d44, data_020d7d4c,
    data_020d7d54, data_020d7d5c, data_020d7d64, data_020d7d6c, data_020d7d74, data_020d7d7c, data_020d7d84, data_020d7d8c,
    data_020d7d94, data_020d7d9c, data_020d7da4, data_020d7dac, data_020d7db4, data_020d7dbc, data_020d7dc4, data_020d7dcc,
    data_020d7dd4, data_020d7ddc, data_020d7de4, data_020d7dec, data_020d7df4, data_020d7dfc, data_020d7e04, data_020d7e0c,
    data_020d7e14, data_020d7e1c, data_020d7e24, data_020d7e2c, data_020d7e34, data_020d7e3c, data_020d7e44, data_020d7e5c,
    data_020d7e64, data_020d7e6c, data_020d7e74, data_020d7e7c, data_020d7e84, data_020d7e8c, data_020d7e94, data_020d7e9c,
    data_020d7ea4, data_020d7eac, data_020d7eb4, data_020d7ebc, data_020d7ec4, data_020d7ecc, data_020d7ed4, data_020d7edc,
    data_020d7ee4, data_020d7eec, data_020d7ef4, data_020d7efc, data_020d7f04, data_020d7f0c, data_020d7f14, data_020d7f1c,
    data_020d7f24, data_020d7f2c, data_020d7f34, data_020d7f3c, data_020d7f44, data_020d7f4c, data_020d7f54, data_020d7f5c,
    data_020d7f64, data_020d7f6c, data_020d7f74, data_020d7f7c, data_020d7f84, data_020d7f8c, data_020d7f94, data_020d7f9c,
    data_020d7fa4, data_020d7fac, data_020d7fb4, data_020d7fbc, data_020d7fc4, data_020d7fcc, data_020d7fd4, data_020d7fdc,
    data_020d7fe4, data_020d7fec, data_020d7ff4, data_020d7ffc, data_020d8004, data_020d800c, data_020d8014, data_020d801c,
    data_020d8024, data_020d802c, data_020d8034, data_020d803c, data_020d8044, data_020d805c, data_020d8064, data_020d806c,
    data_020d8074, data_020d807c, data_020d8084, data_020d808c;
extern PMF data_021c0de0[147];

extern "C" void func_02007364(Obj_020d82b4 *self, Msg_02007364 *msg)
{
    if (!(data_021c0000 & 1)) {
        data_021c0de0[0] = data_020d808c;
        data_021c0de0[1] = data_020d8084;
        data_021c0de0[2] = data_020d807c;
        data_021c0de0[3] = data_020d8074;
        data_021c0de0[4] = data_020d806c;
        data_021c0de0[5] = data_020d8064;
        data_021c0de0[6] = data_020d805c;
        data_021c0de0[7] = data_020d794c;
        data_021c0de0[8] = data_020d75cc;
        data_021c0de0[9] = data_020d8044;
        data_021c0de0[10] = data_020d803c;
        data_021c0de0[11] = data_020d8034;
        data_021c0de0[12] = data_020d802c;
        data_021c0de0[13] = data_020d8024;
        data_021c0de0[14] = data_020d801c;
        data_021c0de0[15] = data_020d8014;
        data_021c0de0[16] = data_020d800c;
        data_021c0de0[17] = data_020d8004;
        data_021c0de0[18] = data_020d7ffc;
        data_021c0de0[19] = data_020d7ff4;
        data_021c0de0[20] = data_020d7fec;
        data_021c0de0[21] = data_020d7fe4;
        data_021c0de0[22] = data_020d7fdc;
        data_021c0de0[23] = data_020d7fd4;
        data_021c0de0[24] = data_020d7fcc;
        data_021c0de0[25] = data_020d7fc4;
        data_021c0de0[26] = data_020d7fbc;
        data_021c0de0[27] = data_020d7fb4;
        data_021c0de0[28] = data_020d7fac;
        data_021c0de0[29] = data_020d7fa4;
        data_021c0de0[30] = data_020d7f9c;
        data_021c0de0[31] = data_020d7f94;
        data_021c0de0[32] = data_020d7f8c;
        data_021c0de0[33] = data_020d7f84;
        data_021c0de0[34] = data_020d7f7c;
        data_021c0de0[35] = data_020d7f74;
        data_021c0de0[36] = data_020d7f6c;
        data_021c0de0[37] = data_020d7f64;
        data_021c0de0[38] = data_020d7f5c;
        data_021c0de0[39] = data_020d7f54;
        data_021c0de0[40] = data_020d7f4c;
        data_021c0de0[41] = data_020d7f44;
        data_021c0de0[42] = data_020d7f3c;
        data_021c0de0[43] = data_020d7f34;
        data_021c0de0[44] = data_020d7f2c;
        data_021c0de0[45] = data_020d7f24;
        data_021c0de0[46] = data_020d7f1c;
        data_021c0de0[47] = data_020d7f14;
        data_021c0de0[48] = data_020d7f0c;
        data_021c0de0[49] = data_020d7f04;
        data_021c0de0[50] = data_020d7efc;
        data_021c0de0[51] = data_020d7ef4;
        data_021c0de0[52] = data_020d7eec;
        data_021c0de0[53] = data_020d7ee4;
        data_021c0de0[54] = data_020d7edc;
        data_021c0de0[55] = data_020d7ed4;
        data_021c0de0[56] = data_020d7ecc;
        data_021c0de0[57] = data_020d7ec4;
        data_021c0de0[58] = data_020d7ebc;
        data_021c0de0[59] = data_020d7eb4;
        data_021c0de0[60] = data_020d7eac;
        data_021c0de0[61] = data_020d7ea4;
        data_021c0de0[62] = data_020d7e9c;
        data_021c0de0[63] = data_020d7e94;
        data_021c0de0[64] = data_020d7e8c;
        data_021c0de0[65] = data_020d7e84;
        data_021c0de0[66] = data_020d7e7c;
        data_021c0de0[67] = data_020d7e74;
        data_021c0de0[68] = data_020d7e6c;
        data_021c0de0[69] = data_020d7e64;
        data_021c0de0[70] = data_020d7e5c;
        data_021c0de0[71] = data_020d784c;
        data_021c0de0[72] = data_020d754c;
        data_021c0de0[73] = data_020d7e44;
        data_021c0de0[74] = data_020d7e3c;
        data_021c0de0[75] = data_020d7e34;
        data_021c0de0[76] = data_020d7e2c;
        data_021c0de0[77] = data_020d7e24;
        data_021c0de0[78] = data_020d7e1c;
        data_021c0de0[79] = data_020d7e14;
        data_021c0de0[80] = data_020d7e0c;
        data_021c0de0[81] = data_020d7e04;
        data_021c0de0[82] = data_020d7dfc;
        data_021c0de0[83] = data_020d7df4;
        data_021c0de0[84] = data_020d7dec;
        data_021c0de0[85] = data_020d7de4;
        data_021c0de0[86] = data_020d7ddc;
        data_021c0de0[87] = data_020d7dd4;
        data_021c0de0[88] = data_020d7dcc;
        data_021c0de0[89] = data_020d7dc4;
        data_021c0de0[90] = data_020d7dbc;
        data_021c0de0[91] = data_020d7db4;
        data_021c0de0[92] = data_020d7dac;
        data_021c0de0[93] = data_020d7da4;
        data_021c0de0[94] = data_020d7d9c;
        data_021c0de0[95] = data_020d7d94;
        data_021c0de0[96] = data_020d7d8c;
        data_021c0de0[97] = data_020d7d84;
        data_021c0de0[98] = data_020d7d7c;
        data_021c0de0[99] = data_020d7d74;
        data_021c0de0[100] = data_020d7d6c;
        data_021c0de0[101] = data_020d7d64;
        data_021c0de0[102] = data_020d7d5c;
        data_021c0de0[103] = data_020d7d54;
        data_021c0de0[104] = data_020d7d4c;
        data_021c0de0[105] = data_020d7d44;
        data_021c0de0[106] = data_020d7d3c;
        data_021c0de0[107] = data_020d7d34;
        data_021c0de0[108] = data_020d7d2c;
        data_021c0de0[109] = data_020d7d24;
        data_021c0de0[110] = data_020d7d1c;
        data_021c0de0[111] = data_020d7d14;
        data_021c0de0[112] = data_020d7d0c;
        data_021c0de0[113] = data_020d7d04;
        data_021c0de0[114] = data_020d7cfc;
        data_021c0de0[115] = data_020d7cf4;
        data_021c0de0[116] = data_020d7cec;
        data_021c0de0[117] = data_020d7ce4;
        data_021c0de0[118] = data_020d7cdc;
        data_021c0de0[119] = data_020d7cd4;
        data_021c0de0[120] = data_020d7ccc;
        data_021c0de0[121] = data_020d7cc4;
        data_021c0de0[122] = data_020d7cbc;
        data_021c0de0[123] = data_020d7cb4;
        data_021c0de0[124] = data_020d7cac;
        data_021c0de0[125] = data_020d7ca4;
        data_021c0de0[126] = data_020d7c9c;
        data_021c0de0[127] = data_020d7c94;
        data_021c0de0[128] = data_020d7c8c;
        data_021c0de0[129] = data_020d7c84;
        data_021c0de0[130] = data_020d7c7c;
        data_021c0de0[131] = data_020d7c74;
        data_021c0de0[132] = data_020d7c6c;
        data_021c0de0[133] = data_020d7c64;
        data_021c0de0[134] = data_020d7c5c;
        data_021c0de0[135] = data_020d7c54;
        data_021c0de0[136] = data_020d7c4c;
        data_021c0de0[137] = data_020d7c44;
        data_021c0de0[138] = data_020d7c3c;
        data_021c0de0[139] = data_020d7c34;
        data_021c0de0[140] = data_020d773c;
        data_021c0de0[141] = data_020d7c24;
        data_021c0de0[142] = data_020d7c1c;
        data_021c0de0[143] = data_020d772c;
        data_021c0de0[144] = data_020d74bc;
        data_021c0de0[145] = data_020d7c04;
        data_021c0de0[146] = data_020d7bfc;
        data_021c0000 |= 1;
    }

    UnkStruct_02007364 *g;
    int id;
    PMF f;
    int saved;
    short h;

    id = msg->unk_00;
    h = msg->unk_08;
    f = data_021c0de0[id];
    saved = self->unk_7F4;
    func_02007d40(self, id);
    func_02007d2c(self);
    self->unk_7F0 = id;
    func_02007d00(self, id);
    func_02008270(self, id, saved);
    func_02007ce4(self, id);
    func_02010e48(self, &id);
    func_020064cc(self, id);
    g = data_020ccf94;
    if (func_02073dd4(g, g->unk_64)) {
        if (func_02073908(g, self->unk_800) == 0) {
            if (h >= 0) {
                self->unk_C84 = h;
                self->unk_C88 = id;
            }
        } else {
            self->unk_C84 = func_02073d80(g);
        }
    }
    (self->*f)(msg, saved);
    self->unk_7FC = func_02008264(self, id);
    if (func_02073908(g, self->unk_800) == 0 && data_020c7e48[id] != 0) {
        func_0200f27c(self, 0x12);
    } else {
        func_0200f268(self, 0x12);
    }
}
