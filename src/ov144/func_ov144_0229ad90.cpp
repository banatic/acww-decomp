/* func_ov144_0229ad90 @ 0x0229ad90, 0x40 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov144_0229ad90(char *self);

extern "C" void func_ov144_0229a040(char *);
extern "C" void func_ov002_0220af74(char *);
extern "C" void func_020b9ccc(char *);

class SubClass {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

void func_ov144_0229ad90(char *self)
{
    func_ov144_0229a040(self);
    func_ov002_0220af74(self + 0x170);
    func_020b9ccc(self + 0x708);
    func_020b9ccc(self + 0x72c);
    ((SubClass *) (self + 0x128))->f3();
}
