/* storage_scene_9: 2 functions, module ov102
 * mwccarm 1.2/base -O4,s
 * func_ov102_0229e6e4 @ 0x0229e6e4, 0xe8 bytes, Thumb, emits _ZN18Obj_ov102_0229ea6019func_ov102_0229e6e4Ev
 * func_ov102_0229e5b8 @ 0x0229e5b8, 0x12c bytes, Thumb
 */

#include "cpp/ov102/Obj_ov102_0229ea60.h"

typedef void (Obj_ov102_0229ea60::*PMF)();

struct UnkStruct_0229e5b8 {
    char pad[0x8d];
    unsigned char idx;
    void m0() {}
    void m1() {}
    void m2() {}
    void m3() {}
    void m4() {}
    void m5() {}
    void m6() {}
    void m7() {}
    void m8() {}
    void m9() {}
    void m10() {}
    void m11() {}
    void m12() {}
    void m13() {}
    void m14() {}
    void m15() {}
};

int Obj_ov102_0229ea60::func_ov102_0229e6e4()
{
    static PMF table[10] = {&Obj_ov102_0229ea60::func_ov102_0229e4d8, &Obj_ov102_0229ea60::func_ov102_0229e458,
                            &Obj_ov102_0229ea60::func_ov102_0229e410, &Obj_ov102_0229ea60::func_ov102_0229e380,
                            &Obj_ov102_0229ea60::func_ov102_0229e308, &Obj_ov102_0229ea60::func_ov102_0229e29c,
                            &Obj_ov102_0229ea60::func_ov102_0229e24c, &Obj_ov102_0229ea60::func_ov102_0229e224,
                            &Obj_ov102_0229ea60::func_ov102_0229e1cc, &Obj_ov102_0229ea60::func_ov102_0229e1c4};
    func_ov102_0229e0b0();
    (this->*table[state])();
    func_ov102_0229e084();
    return 1;
}

extern "C" void func_ov102_0229e5b8(UnkStruct_0229e5b8 *obj)
{
    static void (UnkStruct_0229e5b8::*tbl[16])() = {
        &UnkStruct_0229e5b8::m0,  &UnkStruct_0229e5b8::m1,  &UnkStruct_0229e5b8::m2,  &UnkStruct_0229e5b8::m3,
        &UnkStruct_0229e5b8::m4,  &UnkStruct_0229e5b8::m5,  &UnkStruct_0229e5b8::m6,  &UnkStruct_0229e5b8::m7,
        &UnkStruct_0229e5b8::m8,  &UnkStruct_0229e5b8::m9,  &UnkStruct_0229e5b8::m10, &UnkStruct_0229e5b8::m11,
        &UnkStruct_0229e5b8::m12, &UnkStruct_0229e5b8::m13, &UnkStruct_0229e5b8::m14, &UnkStruct_0229e5b8::m15};
    (obj->*tbl[obj->idx])();
}
