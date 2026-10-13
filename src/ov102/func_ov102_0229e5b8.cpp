/* func_ov102_0229e5b8 @ 0x0229e5b8, 0x12c bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

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

extern "C" void func_ov102_0229e5b8(UnkStruct_0229e5b8 *obj)
{
    static void (UnkStruct_0229e5b8::*tbl[16])() = {
        &UnkStruct_0229e5b8::m0,  &UnkStruct_0229e5b8::m1,  &UnkStruct_0229e5b8::m2,  &UnkStruct_0229e5b8::m3,
        &UnkStruct_0229e5b8::m4,  &UnkStruct_0229e5b8::m5,  &UnkStruct_0229e5b8::m6,  &UnkStruct_0229e5b8::m7,
        &UnkStruct_0229e5b8::m8,  &UnkStruct_0229e5b8::m9,  &UnkStruct_0229e5b8::m10, &UnkStruct_0229e5b8::m11,
        &UnkStruct_0229e5b8::m12, &UnkStruct_0229e5b8::m13, &UnkStruct_0229e5b8::m14, &UnkStruct_0229e5b8::m15};
    (obj->*tbl[obj->idx])();
}
