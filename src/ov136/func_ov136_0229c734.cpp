/* func_ov136_0229c734 @ 0x0229c734, 0x1c bytes, Thumb, module ov136
 * mwccarm 1.2/base -O4,s
 */

struct SubObject {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};

extern "C" void func_ov002_0220a374(SubObject *obj, int val);

struct UnkStruct_0229c734 {
    char pad_00[0x94];
    SubObject sub;
};

extern "C" void func_ov136_0229c734(UnkStruct_0229c734 *self)
{
    func_ov002_0220a374(&self->sub, 0);
    self->sub.v3();
}
