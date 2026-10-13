/* func_ov110_0229e370 @ 0x0229e370, 0x1c bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229e370 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

class UnkStruct_0229e370_2 {
  public:
    unsigned char pad_00[0x22e0];
    UnkStruct_0229e370 inner;
};

extern "C" void func_ov110_0229e330(UnkStruct_0229e370_2 *obj);

extern "C" void func_ov110_0229e370(UnkStruct_0229e370_2 *obj)
{
    func_ov110_0229e330(obj);
    obj->inner.f3();
}
