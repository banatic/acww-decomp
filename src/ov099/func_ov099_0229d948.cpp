/* func_ov099_0229d948 @ 0x0229d948, 0x1c bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

class SubClass {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void target();
};

class UnkStruct_0229d948 {
  public:
    char pad_00[0x2274];
    SubClass sub;
};

extern "C" void func_ov099_0229d910(UnkStruct_0229d948 *obj);

extern "C" void func_ov099_0229d948(UnkStruct_0229d948 *obj)
{
    func_ov099_0229d910(obj);
    obj->sub.target();
}
