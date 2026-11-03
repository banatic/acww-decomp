/* mes_bg_2: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020acae8 @ 0x020acae8, 0x60 bytes, Thumb
 * func_020acab8 @ 0x020acab8, 0x30 bytes, Thumb
 * func_020aca98 @ 0x020aca98, 0x20 bytes, Thumb
 */

class UnkStruct_020acae8_2 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
};

typedef struct {
    char pad_00[0x10];
    UnkStruct_020acae8_2 obj;
} ParamType;

typedef struct {
    int unk_00;
} UnkStruct_020acae8;

extern "C" int func_0208e958(UnkStruct_020acae8_2 *p);
extern "C" int func_0208aeec(ParamType *p);
extern "C" int func_0208aef0(ParamType *p);
extern "C" void func_02088df8(int, int, int, int, int, int, int, int, int, int, int, int);
extern UnkStruct_020acae8 *data_020d5b3c;
extern "C" int func_020aca7c(void *object);
extern "C" int func_020aca74(void *p);
extern "C" void func_0208ea70(void *p, int a, int b);

class UnkStruct_020acab8_2 {
  public:
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
};

struct UnkStruct_020acab8 {
    char pad_00[0x10];
    UnkStruct_020acab8_2 base;
};

class UnkStruct_020aca98 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
    virtual void method4(int, int);
};

struct UnkStruct_020aca98_2 {
    char pad_00[0x10];
    UnkStruct_020aca98 inner;
};

extern "C" void func_0208aef4(UnkStruct_020aca98_2 *o, int b, int c);

extern "C" void func_020acae8(ParamType *param)
{
    if (func_0208e958(&param->obj) == 0) {
        return;
    }
    param->obj.f2();
    int g = data_020d5b3c->unk_00;
    int a = func_0208aeec(param);
    int b = func_0208aef0(param);
    func_02088df8(0, g, b, a, -1, 0, 0x1000, 0x1000, 0, -1, 0, 0);
}

extern "C" void func_020acab8(UnkStruct_020acab8 *param)
{
    int a = func_020aca7c(param);
    int b = func_020aca74(param);
    func_0208ea70(&param->base, a, b);
    (&param->base)->m3();
}

extern "C" void func_020aca98(UnkStruct_020aca98_2 *o, int b, int c)
{
    func_0208aef4(o, b, c);
    UnkStruct_020aca98 *obj = &o->inner;
    obj->method4(b, c);
}
