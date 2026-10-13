/* func_ov135_0229c738 @ 0x0229c738, 0x1c bytes, Thumb, module ov135
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov002_0220a374(void *p, int n);

class UnkStruct_0229c738 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void run();
};

class UnkStruct_0229c738_2 {
  public:
    char pad_00[0x98];
    UnkStruct_0229c738 sub;
};

extern "C" void func_ov135_0229c738(UnkStruct_0229c738_2 *self)
{
    func_ov002_0220a374(&self->sub, 0);
    self->sub.run();
}
