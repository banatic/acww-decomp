/* func_ov122_022a2110 @ 0x022a2110, 0x12c bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov122_022a273819func_ov122_022a2110Ev
 */

#include "cpp/ov122/Obj_ov122_022a2738.h"

extern "C" void func_ov122_022a1854(Obj_ov122_022a2738 *);
extern "C" void func_ov122_022a1850(Obj_ov122_022a2738 *);

typedef void (Obj_ov122_022a2738::*PMF)();

static int g_flag;
static PMF g_table[15];

static const PMF pmf0 = &Obj_ov122_022a2738::func_ov122_022a1d60;
static const PMF pmf1 = &Obj_ov122_022a2738::func_ov122_022a1d04;
static const PMF pmf2 = &Obj_ov122_022a2738::func_ov122_022a1cc8;
static const PMF pmf3 = &Obj_ov122_022a2738::func_ov122_022a1c68;
static const PMF pmf4 = &Obj_ov122_022a2738::func_ov122_022a1c24;
static const PMF pmf5 = &Obj_ov122_022a2738::func_ov122_022a1bd4;
static const PMF pmf6 = &Obj_ov122_022a2738::func_ov122_022a1ba4;
static const PMF pmf7 = &Obj_ov122_022a2738::func_ov122_022a1b60;
static const PMF pmf8 = &Obj_ov122_022a2738::func_ov122_022a1b50;
static const PMF pmf9 = &Obj_ov122_022a2738::func_ov122_022a1b24;
static const PMF pmf10 = &Obj_ov122_022a2738::func_ov122_022a1ac4;
static const PMF pmf11 = &Obj_ov122_022a2738::func_ov122_022a1a84;
static const PMF pmf12 = &Obj_ov122_022a2738::func_ov122_022a1a58;
static const PMF pmf13 = &Obj_ov122_022a2738::func_ov122_022a1a04;
static const PMF pmf14 = &Obj_ov122_022a2738::func_ov122_022a1998;

int Obj_ov122_022a2738::func_ov122_022a2110()
{
    if (!(g_flag & 1)) {
        g_table[0] = pmf0;
        g_table[1] = pmf1;
        g_table[2] = pmf2;
        g_table[3] = pmf3;
        g_table[4] = pmf4;
        g_table[5] = pmf5;
        g_table[6] = pmf6;
        g_table[7] = pmf7;
        g_table[8] = pmf8;
        g_table[9] = pmf9;
        g_table[10] = pmf10;
        g_table[11] = pmf11;
        g_table[12] = pmf12;
        g_table[13] = pmf13;
        g_table[14] = pmf14;
        g_flag |= 1;
    }
    func_ov122_022a1854(this);
    (this->*g_table[state])();
    func_ov122_022a1850(this);
    return 1;
}
