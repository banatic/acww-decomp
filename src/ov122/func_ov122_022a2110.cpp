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

// The state handlers func_ov122_022a1d60 ... func_ov122_022a1998, as member-function pointer
// constants in the ROM's data.
extern const PMF data_ov122_022a26f0;
extern const PMF data_ov122_022a26f8;
extern const PMF data_ov122_022a2630;
extern const PMF data_ov122_022a26e8;
extern const PMF data_ov122_022a26e0;
extern const PMF data_ov122_022a26d8;
extern const PMF data_ov122_022a26d0;
extern const PMF data_ov122_022a26c8;
extern const PMF data_ov122_022a26c0;
extern const PMF data_ov122_022a26b8;
extern const PMF data_ov122_022a2610;
extern const PMF data_ov122_022a26a8;
extern const PMF data_ov122_022a26a0;
extern const PMF data_ov122_022a2698;
extern const PMF data_ov122_022a2690;

int Obj_ov122_022a2738::func_ov122_022a2110()
{
    if (!(g_flag & 1)) {
        g_table[0] = data_ov122_022a26f0;
        g_table[1] = data_ov122_022a26f8;
        g_table[2] = data_ov122_022a2630;
        g_table[3] = data_ov122_022a26e8;
        g_table[4] = data_ov122_022a26e0;
        g_table[5] = data_ov122_022a26d8;
        g_table[6] = data_ov122_022a26d0;
        g_table[7] = data_ov122_022a26c8;
        g_table[8] = data_ov122_022a26c0;
        g_table[9] = data_ov122_022a26b8;
        g_table[10] = data_ov122_022a2610;
        g_table[11] = data_ov122_022a26a8;
        g_table[12] = data_ov122_022a26a0;
        g_table[13] = data_ov122_022a2698;
        g_table[14] = data_ov122_022a2690;
        g_flag |= 1;
    }
    func_ov122_022a1854(this);

    (this->*g_table[state])();

    func_ov122_022a1850(this);
    return 1;
}
