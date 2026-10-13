/* func_ov068_02269b88 @ 0x02269b88, 0x100 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov068_022771c019func_ov068_02269b88Ei
 */

#include "cpp/ov068/Obj_ov068_022771c0.h"

extern "C" {
int func_0201ce50(int);
void func_0202e194(int);
void MI_CpuCopy8(const void *, void *, int);
int func_0202d6e4(char *, int);
extern unsigned char data_ov068_02276794[];
}

void Obj_ov068_022771c0::func_ov068_02269b88(int param)
{
    static int (Obj_ov068_022771c0::*const members[7])(int) = {
        &Obj_ov068_022771c0::func_ov068_0226ab58, &Obj_ov068_022771c0::func_ov068_0226aad4,
        &Obj_ov068_022771c0::func_ov068_0226a91c, &Obj_ov068_022771c0::func_ov068_0226a618,
        &Obj_ov068_022771c0::func_ov068_0226a49c, &Obj_ov068_022771c0::func_ov068_0226a3e0,
        &Obj_ov068_022771c0::func_ov068_0226a260};
    int res1 = func_0201ce50(param);
    func_0202e194(param);
    func_0202e194(res1);
    char local_array[7];
    MI_CpuCopy8(data_ov068_02276794, local_array, 7);
    int flag;
    flag = 0;
    int i;
    for (i = 0; i < 7; i++) {
        int idx = func_0202d6e4(local_array, 7);
        if ((unsigned) idx >= 7) {
            continue;
        }
        if ((this->*members[idx])(param) != 0) {
            break;
        }
        local_array[idx] = (char) flag;
    }
    if (i == 7) {
        state_1c = 3;
    }
}
