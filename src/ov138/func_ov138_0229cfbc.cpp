/* func_ov138_0229cfbc @ 0x0229cfbc, 0x18 bytes, Thumb, module ov138
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov138_0229cf98(void *obj);

struct SubClass {
    virtual void f1();
    virtual void f2();
    virtual void f3();
    virtual int f4();
};

struct UnkStruct_0229cfbc {
    char pad_00[0x98];
    SubClass member;
};

extern "C" int func_ov138_0229cfbc(UnkStruct_0229cfbc *obj)
{
    func_ov138_0229cf98(obj);
    return obj->member.f4();
}
