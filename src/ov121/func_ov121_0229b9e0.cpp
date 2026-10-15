/* func_ov121_0229b9e0 @ 0x0229b9e0, 0x1c bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov121_0229b9d4(void);

class UnkStruct_0229b9e0 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};

struct UnkStruct_0229b9e0_2 {
    char pad_00[0x3a8];
    UnkStruct_0229b9e0 sub;
};

extern "C" void func_ov121_0229b9e0(UnkStruct_0229b9e0_2 *obj)
{
    func_ov121_0229b9d4();
    obj->sub.v3();
}
