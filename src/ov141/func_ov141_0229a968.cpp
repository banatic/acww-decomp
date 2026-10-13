/* func_ov141_0229a968 @ 0x0229a968, 0x1c bytes, Thumb, module ov141
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov141_0229a934(void *p);
class UnkStruct_0229a968 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};
struct UnkStruct_0229a968_2 {
    char pad_00[0xa38];
    UnkStruct_0229a968 sub;
};
extern "C" void func_ov141_0229a968(UnkStruct_0229a968_2 *self)
{
    func_ov141_0229a934(self);
    self->sub.v3();
}
