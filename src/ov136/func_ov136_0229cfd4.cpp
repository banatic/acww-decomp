/* func_ov136_0229cfd4 @ 0x0229cfd4, 0x18 bytes, Thumb, module ov136
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov136_0229cfb0(void *obj);

class UnkStruct_0229cfd4 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

class UnkStruct_0229cfd4_2 {
  public:
    unsigned char pad_00[0x94];
    UnkStruct_0229cfd4 inner;
};

extern "C" void func_ov136_0229cfd4(UnkStruct_0229cfd4_2 *obj)
{
    func_ov136_0229cfb0(obj);
    obj->inner.f3();
}
