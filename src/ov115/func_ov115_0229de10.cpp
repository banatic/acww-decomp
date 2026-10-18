/* func_ov115_0229de10 @ 0x0229de10, 0x1a bytes, Thumb, module ov115
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229de10 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};

struct StructDef {
    char pad_00[0x94];
    UnkStruct_0229de10 sub;
};

extern "C" void func_ov002_0220a0ec(UnkStruct_0229de10 *p);

extern "C" void func_ov115_0229de10(StructDef *obj)
{
    func_ov002_0220a0ec(&obj->sub);
    obj->sub.v3();
}
