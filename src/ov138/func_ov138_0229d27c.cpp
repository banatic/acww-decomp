/* func_ov138_0229d27c @ 0x0229d27c, 0x94 bytes, Thumb, module ov138
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov138_0229d4e019func_ov138_0229d27cEv
 */

#include "cpp/ov138/Obj_ov138_0229d4e0.h"

typedef void (Obj_ov138_0229d4e0::*PMF)();

extern "C" void func_ov138_0229cf98(Obj_ov138_0229d4e0 *);
extern "C" void func_ov138_0229cf88(Obj_ov138_0229d4e0 *);

// The state handlers, as member-function pointer constants in the ROM's data:
// func_ov138_0229d0dc, func_ov138_0229d0b4, func_ov138_0229d07c, func_ov138_0229d04c.
extern PMF data_ov138_0229d448;
extern PMF data_ov138_0229d440;
extern PMF data_ov138_0229d450;
extern PMF data_ov138_0229d4d0;

int Obj_ov138_0229d4e0::func_ov138_0229d27c()
{
    static unsigned int s_flag = 0;
    static PMF s_table[4];

    unsigned int flg = s_flag;
    if ((flg & 1) == 0) {
        s_table[0] = data_ov138_0229d448;
        s_table[1] = data_ov138_0229d440;
        s_table[2] = data_ov138_0229d450;
        s_table[3] = data_ov138_0229d4d0;
        s_flag = flg | 1;
    }

    func_ov138_0229cf98(this);

    (this->*(s_table[state]))();

    func_ov138_0229cf88(this);
    return 1;
}
