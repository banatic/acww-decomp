/* func_ov106_0229e9a4 @ 0x0229e9a4, 0x1c bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov106_0229e960(void *self);

class UnkStruct_0229e9a4 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

extern "C" void func_ov106_0229e9a4(void *self)
{
    func_ov106_0229e960(self);
    ((UnkStruct_0229e9a4 *) ((char *) self + 0x22a0))->f3();
}
