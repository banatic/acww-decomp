/* func_0203c0ac @ 0x0203c0ac, 0x134 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0203c0ac;
typedef int (UnkStruct_0203c0ac::*PMF)(void);

struct UnkStruct_0203c0ac_2 {
    PMF fn;
    int a;
    int b;
};

struct UnkStruct_0203c0ac {
    u8 pad_00[0xfc];
    short unk_FC;
    short unk_FE;
    int unk_100;
    int unk_104;
    int unk_108;
    int unk_10C;
    int unk_110;
    int unk_114;
    int unk_118;
    short unk_11C;
    short unk_11E;
    int unk_120;
    int unk_124;
    int unk_128;
    int unk_12C;
    int unk_130;
    int unk_134;
    int unk_138;
    int unk_13C;
    int unk_140;
    int unk_144;
    u8 pad_148[0x168 - 0x148];
    int unk_168;
    int unk_16C;
    int unk_170;
    u8 pad_174[0x1f4 - 0x174];
    u8 unk_1F4;
    u8 pad_1F5[3];
    int unk_1F8;
    int unk_1FC;
    int unk_200;
};

extern UnkStruct_0203c0ac_2 data_021c6820[];

extern "C" void func_0203c030(UnkStruct_0203c0ac *);
extern "C" void func_0203c068(UnkStruct_0203c0ac *);

extern "C" int func_0203c0ac(UnkStruct_0203c0ac *p, int idx)
{
    if (idx < 0x15) {
        if (idx != p->unk_1F8) {
            p->unk_1FC = p->unk_1F8;
            if (idx != p->unk_200) {
                p->unk_11C = p->unk_FC;
                p->unk_11E = p->unk_FE;
                p->unk_120 = p->unk_100;
                p->unk_124 = p->unk_104;
                p->unk_128 = p->unk_108;
                p->unk_12C = p->unk_10C;
                p->unk_130 = p->unk_110;
                p->unk_134 = p->unk_114;
                p->unk_138 = p->unk_118;
                p->unk_13C = p->unk_168;
                p->unk_140 = p->unk_16C;
                p->unk_144 = p->unk_170;
            }
        }
        p->unk_1F4 = 0;
        if ((p->*data_021c6820[idx].fn)()) {
            func_0203c030(p);
            p->unk_1F8 = idx;
            func_0203c068(p);
            return 1;
        }
    }
    return 0;
}
