/* talk_tags_24: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206b024 @ 0x0206b024, 0x28 bytes, Thumb
 * func_0206afa4 @ 0x0206afa4, 0x80 bytes, Thumb
 * func_0206aec4 @ 0x0206aec4, 0xe0 bytes, Thumb
 */

#include "cpp/main/Base_0206afa4.h"

extern "C" void func_020a8750(void *p);

class UnkStruct_0206b024 {
  public:
    virtual void f00();
    virtual void f01();
    virtual void f02();
    virtual void f03();
    virtual void f04();
    virtual void f05();
    virtual void f06();
    virtual void f07();
    virtual void f08();
    virtual void f09();
    virtual void f10();
    virtual void f11();
    virtual void f12();
    virtual void f13();
    virtual void target(int arg);
};

struct Container {
    char pad_00[0x14a8];
    UnkStruct_0206b024 *obj;
};

struct UnkStruct_0206b024_2 {
    char pad_00[0x24];
    Container *container;
    char pad_28[0x10];
    char sub;
    int arg;
};

typedef void (Base_0206afa4::*Pmf)();

extern int data_021cda8c;
extern Pmf data_020de854;
extern Pmf data_020de994;
extern Pmf data_020de9a4;
extern Pmf data_021cdabc[3];

struct UnkStruct_0206aec4;

typedef void (UnkStruct_0206aec4::*PMF)();

extern PMF data_020de87c;
extern PMF data_020de974;
extern PMF data_020de96c;
extern PMF data_020de964;
extern PMF data_020de894;
extern PMF data_020de954;
extern PMF data_020de8ac;
extern PMF data_020de944;
extern PMF data_020de8b4;
extern PMF data_020de934;

struct UnkStruct_0206aec4 {
    char pad_00[0x3c];
    int method;
};

extern int data_021cda6c;
extern PMF data_021cdc34[10];

extern "C" void func_0206b024(UnkStruct_0206b024_2 *self)
{
    int a = self->arg;
    UnkStruct_0206b024 *v = self->container->obj;
    func_020a8750(&self->sub);
    v->target(a);
}

extern "C" void func_0206afa4(Base_0206afa4 *self)
{
    if (!(data_021cda8c & 1)) {
        data_021cdabc[0] = data_020de9a4;
        data_021cdabc[1] = data_020de854;
        data_021cdabc[2] = data_020de994;
        data_021cda8c |= 1;
    }
    Pmf p = data_021cdabc[self->unk_3C];
    (self->*p)();
}

extern "C" void func_0206aec4(UnkStruct_0206aec4 *obj)
{
    if (!(data_021cda6c & 1)) {
        data_021cdc34[0] = data_020de87c;
        data_021cdc34[1] = data_020de974;
        data_021cdc34[2] = data_020de96c;
        data_021cdc34[3] = data_020de964;
        data_021cdc34[4] = data_020de894;
        data_021cdc34[5] = data_020de954;
        data_021cdc34[6] = data_020de8ac;
        data_021cdc34[7] = data_020de944;
        data_021cdc34[8] = data_020de8b4;
        data_021cdc34[9] = data_020de934;
        data_021cda6c |= 1;
    }

    PMF pmf = data_021cdc34[obj->method];
    (obj->*pmf)();
}
