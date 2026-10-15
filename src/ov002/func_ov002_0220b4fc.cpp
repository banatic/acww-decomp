/* func_ov002_0220b4fc @ 0x0220b4fc, 0x3e bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0220b4fc {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
    virtual void f4(int a, int b);
};

extern "C" int func_ov002_0220b550(void *self, void *p);
extern "C" void func_0208f210(void *self, int a, int b);
extern "C" void func_0208f250(void *self);
extern "C" void func_0208f0c4(void *self, int a);

extern "C" void func_ov002_0220b4fc(UnkStruct_0220b4fc *self, void *p, int a, int b)
{
    func_ov002_0220b550(self, p);
    self->f4(a, b);
    func_0208f210(self, 0, 0);
    func_0208f250(self);
    func_0208f0c4(self, 1);
    self->f3();
}
