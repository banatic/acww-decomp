/* func_ov009_02263fbc @ 0x02263fbc, 0xd4 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov009_022658dc19func_ov009_02263fbcEv
 */

#include "cpp/ov009/Obj_ov009_022658dc.h"

extern "C" {
int DWC_Alloc(int, int);
int func_0203e31c(void);
int func_ov009_02264c90(int);
void func_0203edd0(int);
int func_0203e0a8(int, int);
int func_020b6590(void);
int func_020b74f0(int, int, int);
int func_020961a8(int);
}

void Obj_ov009_022658dc::func_ov009_02263fbc()
{
    int flag;
    int ret;
    int res;
    int tmp;
    int from6590;

    if (DWC_Alloc(0x13, 4) != 0) {
        return;
    }
    if (func_0203e31c() != 0) {
        return;
    }

    ret = func_ov009_02264c90((int) this);
    flag = 0;

    if (ret == 1 || ret == 3) {
        if ((unk_235 & 4) != 0) {
            if (vfunc_8c() == 0) {
                func_0203edd0((int) this);
                unk_280 = 1;
            } else {
                func_0203edd0((int) this);
                unk_280 = 0;
            }
            func_0203e0a8((int) this, 0);
            flag = 1;
        }
    }

    if ((unk_235 & 2) == 0) {
        return;
    }
    if (flag != 0) {
        return;
    }

    from6590 = func_020b6590();
    res = func_020b74f0(from6590, 0, 0);
    tmp = func_020961a8(4);
    if (tmp == 0) {
        return;
    }
    if (tmp != res) {
        return;
    }

    if (vfunc_8c() == 0) {
        func_0203edd0((int) this);
        unk_280 = 1;
    } else {
        func_0203edd0((int) this);
        unk_280 = 0;
    }
    func_0203e0a8((int) this, 0);
}
