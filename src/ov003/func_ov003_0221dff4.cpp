/* func_ov003_0221dff4 @ 0x0221dff4, 0x44 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct Result1 {
    int pad_00;            // offset 0
    unsigned short unk_04; // offset 4
};

class UnkStruct_0221dff4 {
  public:
    virtual void f0() = 0;
    virtual void f1() = 0;
    virtual void f2() = 0;
    virtual void f3() = 0;
    virtual void f4() = 0;
    virtual void f5() = 0;
    virtual void f6() = 0;
    virtual void f7() = 0;
    virtual void f8() = 0;
    virtual void f9() = 0;
    virtual void f10() = 0;
    virtual void f11() = 0;
    virtual void f12() = 0;
    virtual void f13() = 0;
    virtual void f14() = 0;
    virtual void f15() = 0;
    virtual void f16() = 0;
    virtual void f17() = 0;
    virtual void f18() = 0;
    virtual void f19() = 0;
    virtual void f20() = 0;
    virtual void f21() = 0;
    virtual void f22() = 0;
    virtual void f23() = 0;
    virtual void f24() = 0;
    virtual void f25() = 0;
    virtual Result1 *DoSomething() = 0; // vtable slot 0x68

    char pad_04[0x138]; // data members up to 0x138
    int someMember;     // offset 0x13c
};

extern "C" void func_02055060(void *, int, int, int, int, int);

extern "C" int func_ov003_0221dff4(UnkStruct_0221dff4 *obj)
{
    Result1 *p = obj->DoSomething();
    int arg1 = (int) obj->DoSomething();
    unsigned short val = (unsigned short) (p->unk_04 - 1);
    func_02055060(&obj->someMember, arg1, 1, 0x1000, val, 0);
    return 1;
}
