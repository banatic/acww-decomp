/* func_ov111_0229f0a4 @ 0x0229f0a4, 0x28 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229f0a4 {
  public:
    virtual void v0() {}
    virtual void v1() {}
    virtual void v2() {}
    virtual void v3() {}
};

struct UnkStruct_0229f0a4_2 {
    char pad_00[0x3d38];
    UnkStruct_0229f0a4 obj;
};

extern "C" void func_ov002_0220a0ec(UnkStruct_0229f0a4 *b);
extern "C" void func_ov002_02208098(UnkStruct_0229f0a4_2 *w, int n);

extern "C" void func_ov111_0229f0a4(UnkStruct_0229f0a4_2 *w)
{
    func_ov002_0220a0ec(&w->obj);
    w->obj.v3();
    func_ov002_02208098(w, 3);
}
