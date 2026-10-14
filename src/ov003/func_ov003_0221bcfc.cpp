/* func_ov003_0221bcfc @ 0x0221bcfc, 0x38 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov003_0223863019func_ov003_0221bcfcEv
 */

#include "cpp/ov003/Obj_ov003_02238630.h"

struct UnkStruct_0221bcfc {
    int unk_00;
    int unk_04;
};

extern "C" {
void func_020ae3b8(void *);
int func_020ae5f4(void);
void func_0206fbd8(int, int);
extern unsigned char data_021f3b30[];
}

void Obj_ov003_02238630::func_ov003_0221bcfc()
{
    if (((UnkStruct_0221bcfc *) unk_40)->unk_04 == 5) {
        func_020ae3b8((void *) data_021f3b30);
        func_0206fbd8(0xe, func_020ae5f4());
        func_ov003_0221bfa8(5);
    }
}
