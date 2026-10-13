/* func_ov009_02262ff8 @ 0x02262ff8, 0x42 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern "C" int func_ov009_02264c90(void *);

class UnkStruct_02262ff8 {
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
    virtual int f27(int) = 0;
};

extern "C" int func_ov009_02262ff8(UnkStruct_02262ff8 *obj)
{
    int r = func_ov009_02264c90(obj);
    switch (r) {
        case 2:
            return obj->f27(2);
        case 3:
            return obj->f27(6);
        case 1:
            return obj->f27(3);
        default:
            return 0;
    }
}
