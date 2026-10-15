/* func_0206c6ac @ 0x0206c6ac, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class Obj1 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual int method();
};

struct Sys {
    char pad_00[0x1a58];
    int unk_1A58;
    int pad_1A5C;
    int flag;
    char pad_1A64[0x3a0];
    Obj1 obj1;
};

struct Parent {
    char pad_00[0x2c];
    Sys *sys;
};

extern "C" int func_0206777c(Sys *sys);
extern "C" void func_020a9334(Parent *self, int r);
extern "C" void func_020a7994(int *field1, int r);

extern "C" void func_0206c6ac(Parent *self)
{
    func_0206777c(self->sys);
    int r1 = self->sys->obj1.method();
    func_020a9334(self, r1);
    int r2 = self->sys->obj1.method();
    func_020a7994(&self->sys->unk_1A58, r2);
    self->sys->flag = 1;
}
