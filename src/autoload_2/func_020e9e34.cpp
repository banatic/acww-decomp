/* func_020e9e34 @ 0x020e9e34, 0x3c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020e9e34 {
    virtual void m0() = 0;
    virtual void m1() = 0;
    virtual void m2() = 0;
    virtual void m3() = 0;
    virtual void m4() = 0;
    virtual void m5() = 0;
    virtual void m6() = 0;
    virtual void m7() = 0;
    virtual void m8() = 0;
    virtual void m9() = 0;
    virtual void m10() = 0;
    virtual void m11() = 0;
    virtual void m12() = 0;
    virtual int m13() = 0;
};

extern "C" void func_020ea0a4(UnkStruct_020e9e34 *);
extern "C" void func_020ea084(UnkStruct_020e9e34 *);

extern "C" int func_020e9e34(UnkStruct_020e9e34 *a)
{
    func_020ea0a4(a);
    int result = a->m13();
    func_020ea084(a);
    return result;
}
