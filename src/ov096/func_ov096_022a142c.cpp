/* func_ov096_022a142c @ 0x022a142c, 0x1c bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov096_022a13f0(void *p);

class UnkStruct_022a142c {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

class UnkStruct_022a142c_2 {
  public:
    char pad_00[0x2500];
    UnkStruct_022a142c sub;
};

extern "C" void func_ov096_022a142c(UnkStruct_022a142c_2 *p)
{
    func_ov096_022a13f0(p);
    p->sub.f3();
}
