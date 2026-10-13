/* func_ov002_0220b06c @ 0x0220b06c, 0x5c bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0220b06c {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
    virtual void f4(int a, int b);
};

extern "C" void func_0208aa60(void *self, int a, int b);
extern "C" void func_02070c08(void *p);
extern "C" void func_0207094c(void *p, void *a);
extern "C" void func_0208aa48(void *self, void *p);
extern "C" void func_0208aa88(void *self);
extern "C" void func_0208a9c8(void *self);
extern "C" void func_02070be8(void *p);

extern "C" void func_ov002_0220b06c(UnkStruct_0220b06c *self, void *a, int b, int c)
{
    char tmp[0x6c];

    self->f4(b, c);
    func_0208aa60(self, 0, 0);
    func_02070c08(tmp);
    func_0207094c(tmp, a);
    func_0208aa48(self, tmp);
    func_0208aa88(self);
    func_0208a9c8(self);
    self->f3();
    self->f3();
    func_02070be8(tmp);
}
