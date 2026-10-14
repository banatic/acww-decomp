/* func_ov103_0229c868 @ 0x0229c868, 0x3c bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov103_0229e2e019func_ov103_0229c868Ev
 */

#include "cpp/ov103/Obj_ov103_0229e2e0.h"

extern "C" int func_ov103_0229c820(int);
extern "C" int func_ov103_0229c810(int);
extern "C" void func_ov002_0220a0b4(AnimState *state, int a, int b);

void Obj_ov103_0229e2e0::func_ov103_0229c868()
{
    int param = (int) this;
    int v1 = func_ov103_0229c820(param);
    int v2 = func_ov103_0229c810(param);
    func_ov002_0220a0b4(&unk_2274, v1, v2);
    func_ov002_0220a374(&unk_2274, 1);
    ((Obj_ov103_0229e2e0 *) param)->func_ov103_0229c680();
}
