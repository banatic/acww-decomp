/* chat_scene_7: 3 functions, module ov111
 * mwccarm 1.2/base -O4,s
 * func_ov111_022a0cf8 @ 0x022a0cf8, 0xa4 bytes, Thumb, emits _ZN18Obj_ov111_022a100819func_ov111_022a0cf8Ev
 * func_ov111_022a0bcc @ 0x022a0bcc, 0x12c bytes, Thumb, emits _ZN18Obj_ov111_022a100819func_ov111_022a0bccEv
 * func_ov111_022a0ba0 @ 0x022a0ba0, 0x2a bytes, Thumb, emits _ZN18Obj_ov111_022a100819func_ov111_022a0ba0Ev
 */

#include "cpp/ov111/Obj_ov111_022a1008.h"

extern "C" int func_ov111_022a0a5c(int arg);
extern "C" void func_ov111_022a0b58(int arg);
extern "C" void func_ov111_022a0b20(int arg);

int Obj_ov111_022a1008::func_ov111_022a0cf8()
{
    static void (Obj_ov111_022a1008::*tbl[6])() = {
        &Obj_ov111_022a1008::func_ov111_022a0940, &Obj_ov111_022a1008::func_ov111_022a0910,
        &Obj_ov111_022a1008::func_ov111_022a08bc, &Obj_ov111_022a1008::func_ov111_022a088c,
        &Obj_ov111_022a1008::func_ov111_022a085c, &Obj_ov111_022a1008::func_ov111_022a082c};
    (this->*tbl[state])();
    return 1;
}

void Obj_ov111_022a1008::func_ov111_022a0bcc()
{
    static void (Obj_ov111_022a1008::*table[16])() = {
        &Obj_ov111_022a1008::func_ov111_022a075c, &Obj_ov111_022a1008::func_ov111_022a0708,
        &Obj_ov111_022a1008::func_ov111_022a06c8, &Obj_ov111_022a1008::func_ov111_022a05dc,
        &Obj_ov111_022a1008::func_ov111_022a05b0, &Obj_ov111_022a1008::func_ov111_022a0530,
        &Obj_ov111_022a1008::func_ov111_022a04cc, &Obj_ov111_022a1008::func_ov111_022a04ac,
        &Obj_ov111_022a1008::func_ov111_022a0460, &Obj_ov111_022a1008::func_ov111_022a02f8,
        &Obj_ov111_022a1008::func_ov111_022a027c, &Obj_ov111_022a1008::func_ov111_022a024c,
        &Obj_ov111_022a1008::func_ov111_022a021c, &Obj_ov111_022a1008::func_ov111_022a00f4,
        &Obj_ov111_022a1008::func_ov111_022a001c, &Obj_ov111_022a1008::func_ov111_0229fff4};
    (this->*table[subState])();
}

int Obj_ov111_022a1008::func_ov111_022a0ba0()
{
    int arg = (int) this;
    if (func_ov111_022a0a5c(arg) != 0) {
        return 1;
    }
    func_ov111_022a0b58(arg);
    ((Obj_ov111_022a1008 *) arg)->func_ov111_022a0bcc();
    func_ov111_022a0b20(arg);
    return 1;
}
