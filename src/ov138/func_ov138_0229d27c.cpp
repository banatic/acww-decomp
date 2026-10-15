/* func_ov138_0229d27c @ 0x0229d27c, 0x94 bytes, Thumb, module ov138
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov138_0229d4e019func_ov138_0229d27cEv
 */

#include "cpp/ov138/Obj_ov138_0229d4e0.h"

typedef void (Obj_ov138_0229d4e0::*PMF)();

#define STATE_func_ov138_0229d0b4 (PMF) & Obj_ov138_0229d4e0::func_ov138_0229d0b4
#define STATE_func_ov138_0229d04c (PMF) & Obj_ov138_0229d4e0::func_ov138_0229d04c

extern "C" void func_ov138_0229cf98(Obj_ov138_0229d4e0 *);
extern "C" void func_ov138_0229cf88(Obj_ov138_0229d4e0 *);

static PMF g_src0 = &Obj_ov138_0229d4e0::func_ov138_0229d0dc;
static PMF g_src1 = STATE_func_ov138_0229d0b4;
static PMF g_src2 = &Obj_ov138_0229d4e0::func_ov138_0229d07c;
static PMF g_src3 = STATE_func_ov138_0229d04c;

int Obj_ov138_0229d4e0::func_ov138_0229d27c()
{
    static unsigned int s_flag = 0;
    static PMF s_table[4];

    unsigned int flg = s_flag;
    if ((flg & 1) == 0) {
        s_table[0] = g_src0;
        s_table[1] = g_src1;
        s_table[2] = g_src2;
        s_table[3] = g_src3;
        s_flag = flg | 1;
    }

    func_ov138_0229cf98(this);

    (this->*(s_table[state]))();

    func_ov138_0229cf88(this);
    return 1;
}

#undef STATE_func_ov138_0229d0b4
#undef STATE_func_ov138_0229d04c
