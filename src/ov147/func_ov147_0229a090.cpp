/* func_ov147_0229a090 @ 0x0229a090, 0x50 bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov147_0229aa2819func_ov147_0229a090Ev
 */

#include "cpp/ov147/Obj_ov147_0229aa28.h"

typedef void (Obj_ov147_0229aa28::*Pmf)();

struct FlagEntry {
    int flag;
    char pad[12];
};

struct PMFEntry {
    char pad[8];
    Pmf pmf;
};

extern FlagEntry data_ov147_0229ad54[];
extern PMFEntry data_ov147_0229ad4c[];

extern "C" void func_ov147_02299168(Obj_ov147_0229aa28 *);

int Obj_ov147_0229aa28::func_ov147_0229a090()
{
    if (data_ov147_0229ad54[unk_50].flag != 0) {
        (this->*data_ov147_0229ad4c[unk_50].pmf)();
    }
    func_ov147_02299168(this);
    unk_B0.func_ov147_0229a634();
    return 1;
}
