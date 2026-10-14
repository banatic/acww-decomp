/* func_ov003_0221cbc0 @ 0x0221cbc0, 0x50 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov003_02238c5419func_ov003_0221cbc0Ev
 */

#include "cpp/ov003/Obj_ov003_02238c54.h"

extern "C" {
void func_02056ffc(Obj_020dd184 *p);
void func_0209e474(void *out);
void RtcSendPxiCommand(int command);
}

void Obj_ov003_02238c54::func_ov003_0221cbc0()
{
    func_02056ffc(&unk_2b4);
    *unk_2b4.unk_18 = unk_2b4.unk_08;
    unsigned int local[2];
    local[0] = 0;
    local[1] = 0;
    func_0209e474(local);
    if (((unsigned char *) local)[4] == 1) {
        RtcSendPxiCommand(0x61);
        vfunc_6c(1);
    }
}
