/* func_ov068_02272e50 @ 0x02272e50, 0x98 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov068_0227775019func_ov068_02272e50Ev
 */

#include "cpp/ov068/Obj_ov068_02277750.h"

extern "C" {
int func_020984e8(void);
int func_020b22b8(void);
int func_020b22dc(void);
int func_020b5e10(void);
void func_020b5e90(void);
void func_0209971c(int, unsigned short *);
}

int Obj_ov068_02277750::func_ov068_02272e50()
{
    int result = func_020984e8();

    unk_2cc.x = unk_5C.x;
    unk_2cc.y = unk_5C.y;
    unk_2cc.z = unk_5C.z;

    if (func_020b22b8() != 0) {
        unk_2de = 1;
        func_020b5e10();
        func_020b5e90();
        func_ov068_02272a7c(1);
    } else if (func_020b22dc() != 0) {
        unk_2de = 1;
        if (result != 0) {
            unsigned short local = 0xfff1;
            func_0209971c(result, &local);
        }
        func_020b5e10();
        func_020b5e90();
        func_ov068_02272a7c(10);
    } else {
        func_ov068_02272a7c(0);
    }

    return 1;
}
