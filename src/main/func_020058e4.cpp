/* func_020058e4 @ 0x020058e4, 0xbe8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Obj_020d82b4.h"

typedef void (Obj_020d82b4::*PMF)();

struct UnkStruct_020058e4;

extern "C" int func_0203f8d0(Vec_0203f080 *, Vec_0203f080 *);
extern "C" void func_020103e4(Obj_020d82b4 *);
extern "C" void func_02010134(Obj_020d82b4 *);
extern "C" int func_02073908(UnkStruct_020058e4 *, int);
extern "C" void func_0200dc98(Obj_020d82b4 *);
extern "C" int func_0200dc8c(Obj_020d82b4 *);
extern "C" int func_0200f290(Obj_020d82b4 *, int);
extern "C" void func_020069f0(Obj_020d82b4 *);
extern "C" void func_02006554(Obj_020d82b4 *);
extern "C" void func_0205ea60(Member_0205ef90 *member);
extern "C" void func_02010f48(Obj_020d82b4 *);
extern "C" int func_02011520(int);
extern "C" void func_02006530(Obj_020d82b4 *, int, int);
extern "C" void func_020064f0(Obj_020d82b4 *, int);
extern "C" void func_020082ac(Obj_020d82b4 *);
extern "C" void func_02010424(Obj_020d82b4 *);
extern "C" void func_02010160(Obj_020d82b4 *);
extern "C" void func_ov003_0220cd84(Obj_020d82b4 *);
extern "C" void func_ov003_0220cd08(Obj_020d82b4 *);
extern "C" void func_ov003_0220cc24(Obj_020d82b4 *);
extern "C" void func_ov003_0220ca24(Obj_020d82b4 *);
extern "C" void func_0200fef0(Obj_020d82b4 *);
extern "C" int func_0200fea0(Obj_020d82b4 *);
extern "C" void func_ov003_0220cbb4(Obj_020d82b4 *);
extern "C" void func_0200f098(Obj_020d82b4 *);
extern "C" void func_020044d0(Obj_0213f058 *member, int *pos);
extern "C" void func_02004444(Obj_020d8414 *member, int *pos);

extern UnkStruct_020058e4 *data_020ccf94;
extern unsigned char data_020e54a8;

extern int data_021c0004;
extern PMF data_020d7314, data_020d731c, data_020d7324, data_020d7334, data_020d733c, data_020d7344, data_020d734c,
    data_020d7354, data_020d735c, data_020d7364, data_020d736c, data_020d7374, data_020d737c, data_020d7384, data_020d738c,
    data_020d7394, data_020d739c, data_020d73a4, data_020d73ac, data_020d73b4, data_020d73bc, data_020d73c4, data_020d73d4,
    data_020d73dc, data_020d73e4, data_020d73ec, data_020d73f4, data_020d73fc, data_020d7404, data_020d741c, data_020d7424,
    data_020d742c, data_020d7434, data_020d743c, data_020d7444, data_020d744c, data_020d7454, data_020d745c, data_020d7464,
    data_020d746c, data_020d7474, data_020d7484, data_020d7494, data_020d749c, data_020d74a4, data_020d74ac, data_020d74c4,
    data_020d74cc, data_020d74d4, data_020d74dc, data_020d74e4, data_020d74ec, data_020d74f4, data_020d74fc, data_020d7504,
    data_020d750c, data_020d7514, data_020d751c, data_020d7524, data_020d752c, data_020d7534, data_020d753c, data_020d7544,
    data_020d7554, data_020d755c, data_020d7564, data_020d756c, data_020d7574, data_020d757c, data_020d7584, data_020d758c,
    data_020d7594, data_020d759c, data_020d75a4, data_020d75ac, data_020d75b4, data_020d75bc, data_020d75c4, data_020d75d4,
    data_020d75dc, data_020d75e4, data_020d75ec, data_020d75f4, data_020d75fc, data_020d7604, data_020d760c, data_020d7614,
    data_020d761c, data_020d7624, data_020d762c, data_020d7634, data_020d763c, data_020d7644, data_020d764c, data_020d7654,
    data_020d765c, data_020d7664, data_020d766c, data_020d7674, data_020d767c, data_020d7684, data_020d768c, data_020d7694,
    data_020d769c, data_020d76a4, data_020d76ac, data_020d76b4, data_020d76bc, data_020d76c4, data_020d76d4, data_020d76dc,
    data_020d76e4, data_020d76ec, data_020d76f4, data_020d76fc, data_020d7704, data_020d7714, data_020d771c, data_020d7724,
    data_020d7734, data_020d7744, data_020d796c, data_020d7974, data_020d797c, data_020d7a4c, data_020d7a54, data_020d7a5c,
    data_020d7a64, data_020d7a6c, data_020d7a7c, data_020d7a84, data_020d7aa4, data_020d7ab4, data_020d7ac4, data_020d7acc,
    data_020d7b4c, data_020d7be4, data_020d7bec, data_020d7bf4, data_020d7c2c, data_020d7e4c, data_020d7e54, data_020d8054,
    data_020d824c, data_020d825c, data_020d8274, data_020d828c;
extern PMF data_021c04b0[147];

extern "C" void func_020058e4(Obj_020d82b4 *self)
{
    UnkStruct_020058e4 *g;
    Vec_0203f080 tmp;
    int k;
    int fl;

    fl = self->unk_B0;
    if ((fl & 4) ? 1 : 0) {
        if ((fl & 2) ? 1 : 0) {
            Vec_0203f080 *p = &self->unk_5C;
            tmp = *p;
            self->unk_6F4 = p->x;
            self->unk_6F8 = p->y;
            self->unk_6FC = p->z;
            {
                Vec_0203f080 *q = (Vec_0203f080 *) &self->unk_6F4;
                self->unk_6E0 = q->x;
                self->unk_6E4 = q->y;
                self->unk_6E8 = q->z;
                {
                    Vec_0203f080 *r = (Vec_0203f080 *) &self->unk_6E0;
                    self->unk_6D4 = r->x;
                    self->unk_6D8 = r->y;
                    self->unk_6DC = r->z;
                    {
                        Vec_0203f080 *s = (Vec_0203f080 *) &self->unk_6D4;
                        self->unk_6C8 = s->x;
                        self->unk_6CC = s->y;
                        self->unk_6D0 = s->z;
                    }
                }
            }
            func_0203f8d0(&tmp, &tmp);
            self->unk_65C = tmp.x;
            self->unk_62C = self->unk_65C;
            self->unk_6BC = self->unk_62C;
            self->unk_68C = self->unk_6BC;
            self->unk_660 = tmp.y;
            self->unk_630 = self->unk_660;
            self->unk_6C0 = self->unk_630;
            self->unk_690 = self->unk_6C0;
            self->unk_664 = tmp.z;
            self->unk_634 = self->unk_664;
            self->unk_6C4 = self->unk_634;
            self->unk_694 = self->unk_6C4;
        }
    }
    func_020103e4(self);
    func_02010134(self);
    g = data_020ccf94;
    if (func_02073908(g, self->unk_800)) {
        func_0200dc98(self);
        if (func_0200dc8c(self) == 0) {
            self->unk_8EA = 0;
        }
    } else if (func_0200f290(self, 0x10) == 0) {
        func_020069f0(self);
    }
    func_02006554(self);
    func_0205ea60(&self->unk_5A0);
    self->unk_8C4 = 0;
    self->unk_8C8 = 0;
    self->unk_8CC = 0;
    {
        if (!(data_021c0004 & 1)) {
            data_021c04b0[0] = data_020d7bf4;
            data_021c04b0[1] = data_020d7be4;
            data_021c04b0[2] = data_020d7494;
            data_021c04b0[3] = data_020d7704;
            data_021c04b0[4] = data_020d76fc;
            data_021c04b0[5] = data_020d76f4;
            data_021c04b0[6] = data_020d76ec;
            data_021c04b0[7] = data_020d76e4;
            data_021c04b0[8] = data_020d76dc;
            data_021c04b0[9] = data_020d76d4;
            data_021c04b0[10] = data_020d765c;
            data_021c04b0[11] = data_020d76c4;
            data_021c04b0[12] = data_020d76bc;
            data_021c04b0[13] = data_020d76b4;
            data_021c04b0[14] = data_020d7684;
            data_021c04b0[15] = data_020d769c;
            data_021c04b0[16] = data_020d76a4;
            data_021c04b0[17] = data_020d7a4c;
            data_021c04b0[18] = data_020d8054;
            data_021c04b0[19] = data_020d7ac4;
            data_021c04b0[20] = data_020d7a7c;
            data_021c04b0[21] = data_020d7aa4;
            data_021c04b0[22] = data_020d7acc;
            data_021c04b0[23] = data_020d7bec;
            data_021c04b0[24] = data_020d7c2c;
            data_021c04b0[25] = data_020d8274;
            data_021c04b0[26] = data_020d824c;
            data_021c04b0[27] = data_020d7644;
            data_021c04b0[28] = data_020d763c;
            data_021c04b0[29] = data_020d7634;
            data_021c04b0[30] = data_020d762c;
            data_021c04b0[31] = data_020d7624;
            data_021c04b0[32] = data_020d761c;
            data_021c04b0[33] = data_020d7614;
            data_021c04b0[34] = data_020d760c;
            data_021c04b0[35] = data_020d7604;
            data_021c04b0[36] = data_020d75fc;
            data_021c04b0[37] = data_020d75f4;
            data_021c04b0[38] = data_020d75ec;
            data_021c04b0[39] = data_020d797c;
            data_021c04b0[40] = data_020d796c;
            data_021c04b0[41] = data_020d75d4;
            data_021c04b0[42] = data_020d731c;
            data_021c04b0[43] = data_020d75c4;
            data_021c04b0[44] = data_020d75bc;
            data_021c04b0[45] = data_020d75b4;
            data_021c04b0[46] = data_020d75ac;
            data_021c04b0[47] = data_020d75a4;
            data_021c04b0[48] = data_020d759c;
            data_021c04b0[49] = data_020d7594;
            data_021c04b0[50] = data_020d758c;
            data_021c04b0[51] = data_020d7584;
            data_021c04b0[52] = data_020d757c;
            data_021c04b0[53] = data_020d7574;
            data_021c04b0[54] = data_020d756c;
            data_021c04b0[55] = data_020d7564;
            data_021c04b0[56] = data_020d755c;
            data_021c04b0[57] = data_020d7554;
            data_021c04b0[58] = data_020d736c;
            data_021c04b0[59] = data_020d7544;
            data_021c04b0[60] = data_020d753c;
            data_021c04b0[61] = data_020d7534;
            data_021c04b0[62] = data_020d752c;
            data_021c04b0[63] = data_020d7524;
            data_021c04b0[64] = data_020d751c;
            data_021c04b0[65] = data_020d7514;
            data_021c04b0[66] = data_020d750c;
            data_021c04b0[67] = data_020d7504;
            data_021c04b0[68] = data_020d74fc;
            data_021c04b0[69] = data_020d74f4;
            data_021c04b0[70] = data_020d74ec;
            data_021c04b0[71] = data_020d74e4;
            data_021c04b0[72] = data_020d74dc;
            data_021c04b0[73] = data_020d74d4;
            data_021c04b0[74] = data_020d74cc;
            data_021c04b0[75] = data_020d7744;
            data_021c04b0[76] = data_020d7484;
            data_021c04b0[77] = data_020d771c;
            data_021c04b0[78] = data_020d7714;
            data_021c04b0[79] = data_020d74a4;
            data_021c04b0[80] = data_020d74ac;
            data_021c04b0[81] = data_020d7654;
            data_021c04b0[82] = data_020d7664;
            data_021c04b0[83] = data_020d767c;
            data_021c04b0[84] = data_020d768c;
            data_021c04b0[85] = data_020d76ac;
            data_021c04b0[86] = data_020d7a54;
            data_021c04b0[87] = data_020d7ab4;
            data_021c04b0[88] = data_020d7b4c;
            data_021c04b0[89] = data_020d7e4c;
            data_021c04b0[90] = data_020d825c;
            data_021c04b0[91] = data_020d7444;
            data_021c04b0[92] = data_020d743c;
            data_021c04b0[93] = data_020d7434;
            data_021c04b0[94] = data_020d742c;
            data_021c04b0[95] = data_020d7424;
            data_021c04b0[96] = data_020d741c;
            data_021c04b0[97] = data_020d75e4;
            data_021c04b0[98] = data_020d7324;
            data_021c04b0[99] = data_020d7404;
            data_021c04b0[100] = data_020d73fc;
            data_021c04b0[101] = data_020d73f4;
            data_021c04b0[102] = data_020d73ec;
            data_021c04b0[103] = data_020d73e4;
            data_021c04b0[104] = data_020d73dc;
            data_021c04b0[105] = data_020d73d4;
            data_021c04b0[106] = data_020d7374;
            data_021c04b0[107] = data_020d73c4;
            data_021c04b0[108] = data_020d73bc;
            data_021c04b0[109] = data_020d73b4;
            data_021c04b0[110] = data_020d7394;
            data_021c04b0[111] = data_020d73ac;
            data_021c04b0[112] = data_020d744c;
            data_021c04b0[113] = data_020d745c;
            data_021c04b0[114] = data_020d7464;
            data_021c04b0[115] = data_020d74c4;
            data_021c04b0[116] = data_020d7724;
            data_021c04b0[117] = data_020d764c;
            data_021c04b0[118] = data_020d766c;
            data_021c04b0[119] = data_020d7694;
            data_021c04b0[120] = data_020d7a5c;
            data_021c04b0[121] = data_020d7a84;
            data_021c04b0[122] = data_020d828c;
            data_021c04b0[123] = data_020d7344;
            data_021c04b0[124] = data_020d733c;
            data_021c04b0[125] = data_020d7334;
            data_021c04b0[126] = data_020d7974;
            data_021c04b0[127] = data_020d734c;
            data_021c04b0[128] = data_020d7354;
            data_021c04b0[129] = data_020d7364;
            data_021c04b0[130] = data_020d737c;
            data_021c04b0[131] = data_020d738c;
            data_021c04b0[132] = data_020d739c;
            data_021c04b0[133] = data_020d7454;
            data_021c04b0[134] = data_020d746c;
            data_021c04b0[135] = data_020d749c;
            data_021c04b0[136] = data_020d7674;
            data_021c04b0[137] = data_020d7a64;
            data_021c04b0[138] = data_020d7e54;
            data_021c04b0[139] = data_020d7314;
            data_021c04b0[140] = data_020d75dc;
            data_021c04b0[141] = data_020d735c;
            data_021c04b0[142] = data_020d7384;
            data_021c04b0[143] = data_020d73a4;
            data_021c04b0[144] = data_020d7474;
            data_021c04b0[145] = data_020d7734;
            data_021c04b0[146] = data_020d7a6c;
            data_021c0004 |= 1;
        }

        PMF f;

        f = data_021c04b0[self->unk_7F0];
        func_02010f48(self);
        (self->*f)();
    }
    func_02011520(self->unk_800);
    k = self->unk_7F0;
    func_02006530(self, k, 0);
    if (func_02073908(g, self->unk_800)) {
        func_020064f0(self, k);
    }
    func_020082ac(self);
    func_02010424(self);
    func_02010160(self);
    if (func_02073908(g, self->unk_800)) {
        if (data_020e54a8 ? 0 : 1) {
            func_ov003_0220cd84(self);
            func_ov003_0220cd08(self);
            func_ov003_0220cc24(self);
            func_ov003_0220ca24(self);
        }
        if (self->unk_8E8) {
            self->unk_8E8--;
        }
    }
    if (self->unk_8EC) {
        self->unk_8EC--;
    }
    func_0200fef0(self);
    self->unk_818 = func_0200fea0(self);
    if (func_02073908(g, self->unk_800)) {
        if (data_020e54a8 ? 0 : 1) {
            func_ov003_0220cbb4(self);
        }
    }
    func_0200f098(self);
    if (func_0200f290(self, 0xa)) {
        if (self->unk_8C4 == 0 && self->unk_8C8 == 0 && self->unk_8CC == 0) {
            self->unk_8C4 = self->unk_5C.x;
            self->unk_8C8 = self->unk_5C.y;
            self->unk_8CC = self->unk_5C.z;
        }
        if (func_0200f290(self, 0x19)) {
            func_020044d0(&self->unk_83C, &self->unk_8C4);
        } else {
            func_02004444(&self->unk_880, &self->unk_8C4);
        }
    }
    {
        int cur = *(volatile int *) &self->unk_7F4;
        if (cur != self->unk_7F0) {
            self->unk_7F4 = self->unk_7F0;
        }
    }
}
