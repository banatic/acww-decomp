/* func_ov109_0229c658 @ 0x0229c658, 0x20 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229c658 {
  public:
    virtual int v1();
    virtual int v2();
    virtual int v3();
    virtual int v4();
};

struct UnkStruct_0229c658_2 {
    char pad_00[0x2274];
    UnkStruct_0229c658 sub;
};

extern "C" void func_ov002_0220a0ec(UnkStruct_0229c658 *p);

extern "C" int func_ov109_0229c658(UnkStruct_0229c658_2 *self)
{
    func_ov002_0220a0ec(&self->sub);
    return self->sub.v4();
}
