/* func_ov112_0229fe84 @ 0x0229fe84, 0x60 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov002_02207fc0(char *self);
extern "C" void func_ov002_0220a374(char *p, int arg1);
extern "C" int func_ov002_0220a768(char *p, int x);
extern "C" int func_ov002_0220a72c(char *p, int x);
extern "C" void func_ov002_0220a0b4(char *p, int a, int b);
extern "C" unsigned char *func_ov002_02208098(char *self, unsigned char value);

class Vtbl {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

extern "C" void func_ov112_0229fe84(char *self)
{
    func_ov002_02207fc0(self);
    self[0xc2] = 1;
    func_ov002_0220a374(self + 0x4448, 1);
    ((Vtbl *) (self + 0x4448))->f3();
    int v1 = func_ov002_0220a768(self + 0x427c, 4);
    int v2 = func_ov002_0220a72c(self + 0x427c, 4);
    func_ov002_0220a0b4(self + 0x4448, v1, v2);
    func_ov002_02208098(self, 19);
}
