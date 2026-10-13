/* func_ov090_02299470 @ 0x02299470, 0x198 bytes, Thumb, module ov090
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov090_0229982019func_ov090_02299470Ev
 */

#include "types.h"
#include "cpp/ov090/Obj_ov090_02299820.h"

typedef Obj_ov090_02299820 S;
typedef void (S::*PMF)();

extern u8 data_ov090_02299960;
extern "C" volatile u16 data_021fbe40[2];

extern "C" void func_ov090_02299058(S *self);
extern "C" int func_020a1518(void);
extern "C" void func_0206efc0(void);
extern "C" void func_ov002_0220b9b8(void *a, void *b, int c, int d);
extern "C" int func_ov090_02299078(u8 v);
extern "C" int func_ov090_02299098(u8 v);
extern "C" void func_ov090_02298fac(S *self, int v);
extern "C" void RtcSendPxiCommand(int cmd);

int Obj_ov090_02299820::func_ov090_02299470()
{
    static PMF tbl[3] = {&S::func_ov090_02299348, &S::func_ov090_0229926c, &S::func_ov090_02299258};

    func_ov090_02299058(this);

    if (unk_97 == 2) {
        if (func_020a1518() != 0) {
            subState = 2;
            u8 v = 31;
            func_ov002_0220b9b8(&buf1164, &v, 1, 1);
            unk_97 = 3;
        } else {
            unk_97 = 0;
            func_0206efc0();
        }
    }

    if (data_ov090_02299960 != 0) {
        data_ov090_02299960--;
    }

    (this->*(tbl[subState]))();

    if (unk_94 != 0) {
        if (unk_92 != 0x10) {
            if (unk_92 >= 0xe) {
                unk_92 = 0x10;
            } else {
                unk_92 += 2;
            }
        }
    } else {
        if (unk_92 != 0) {
            if (unk_92 <= 4) {
                unk_91 = 0;
                unk_92 = 0;
            } else {
                unk_92 -= 4;
            }
        }
    }

    if (unk_95 != 0) {
        if (data_021fbe40[1] & 0x100) {
            int v = func_ov090_02299078(unk_93);
            func_ov090_02298fac(this, v);
            RtcSendPxiCommand(3);
        }
        if (data_021fbe40[1] & 0x200) {
            int w = func_ov090_02299098(unk_93);
            func_ov090_02298fac(this, w);
            RtcSendPxiCommand(3);
        }
    }

    return 1;
}
