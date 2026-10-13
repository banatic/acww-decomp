/* func_0206cc80 @ 0x0206cc80, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" int func_020a7cdc(int, int, int);
extern "C" int func_020676d0(void *);
extern "C" void func_020a93e8(void *, int);
extern "C" void func_020a9334(void *, int);

class UnkStruct_0206cc80 {
  public:
    virtual void f0() {}
    virtual void f1() {}
    virtual void f2() {}
    virtual int method()
    {
        return 0;
    }
};

struct UnkStruct_0206cc80_2 {
    char pad[0x1e4c];
    UnkStruct_0206cc80 sub;
};

struct MySelf {
    int pad_00;
    int a;
    char pad[0x2c - 8];
    UnkStruct_0206cc80_2 *unk_2C;
};

extern "C" void func_0206cc80(MySelf *self)
{
    int a = self->a;
    int b = func_020a7cdc(a, 1, 7);
    if (b == 0) {
        return;
    }
    if (func_020676d0(self->unk_2C) == 0) {
        return;
    }

    func_020a93e8(self, b - a);
    {
        int ret = self->unk_2C->sub.method();
        func_020a9334(self, ret);
    }
}
