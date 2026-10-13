/* func_ov068_0226c520 @ 0x0226c520, 0x6c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0226c520 {
  public:
    virtual int f0() = 0;
    virtual int f1() = 0;
    virtual int f2() = 0;
    virtual int f3() = 0;
    virtual int f4() = 0;
    virtual int f5() = 0;
    virtual int f6() = 0;
    virtual int f7() = 0;
    virtual int f8() = 0;
    virtual int f9() = 0;
    virtual int f10() = 0;
    virtual int f11() = 0;
    virtual int f12() = 0;
    virtual int f13() = 0;
    virtual int f14() = 0;
    virtual int f15() = 0;
    virtual int f16() = 0;
    virtual int f17() = 0;
    virtual int f18() = 0;
    virtual int f19() = 0;
    virtual int f20() = 0;
    virtual int f21() = 0;
    virtual int f22() = 0;
    virtual int f23() = 0;
    virtual int f24() = 0;
    virtual int f25() = 0;
    virtual int f26() = 0;
    virtual int f27() = 0;
    virtual int f28() = 0;
    virtual int f29() = 0;
    virtual int f30() = 0;
    virtual int f31() = 0;
    virtual int f32() = 0;
    virtual int f33() = 0;
    virtual int f34() = 0;
    virtual int f35() = 0;
    virtual int f36() = 0;
    virtual int f37() = 0;
    virtual int f38() = 0;
    virtual int f39() = 0;
    virtual int f40() = 0;
    virtual int f41() = 0;
    virtual int f42() = 0;
    virtual int f43() = 0;
    virtual int f44() = 0;
    virtual int f45() = 0;
    virtual int f46(UnkStruct_0226c520 *arg) = 0;
};

extern "C" int func_020644cc(int);
extern "C" UnkStruct_0226c520 *func_ov068_0226c58c(void *, UnkStruct_0226c520 *);
extern "C" void func_0201ce5c(UnkStruct_0226c520 *, UnkStruct_0226c520 *);
extern "C" void func_0201ce44(UnkStruct_0226c520 *, int);
extern "C" void func_ov068_0226ccd8(void *);
extern "C" void func_ov068_0226cce8(void *, UnkStruct_0226c520 *, int);

extern "C" int func_ov068_0226c520(void *arg1, UnkStruct_0226c520 *arg2)
{
    UnkStruct_0226c520 *obj;
    if (func_020644cc(5) == 0 && arg2->f45() != 0 && (obj = func_ov068_0226c58c(arg1, arg2)) != 0 && obj->f46(arg2) != 0) {
        func_0201ce5c(arg2, obj);
        func_0201ce44(arg2, 0);
        func_ov068_0226ccd8(arg1);
        func_ov068_0226cce8((char *) arg2 + 0x8b8, arg2, 9);
        return 1;
    }
    return 0;
}
