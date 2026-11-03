/* letter_reader_2: 3 functions, module ov091
 * mwccarm 1.2/base -O4,s
 * func_ov091_02299410 @ 0x02299410, 0x4c bytes, Thumb
 * func_ov091_0229936c @ 0x0229936c, 0xa4 bytes, Thumb, emits _ZN18Obj_ov091_0229953019func_ov091_0229936cEv
 * func_ov091_022992f8 @ 0x022992f8, 0x74 bytes, Thumb, emits _ZN18Obj_ov091_0229953019func_ov091_022992f8Ev
 */

#include "cpp/ov091/Obj_ov091_02299530.h"

extern "C" int func_ov002_02207f60(void *);
extern "C" void func_0208f210(void *, int, int);
extern "C" int func_0206fe54(void);
extern "C" void func_ov002_02209eb8(void *);

class UnkStruct_02299410 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

class UnkStruct_02299410_2 {
  public:
    virtual void g0();
    virtual void g1();
    virtual int g2();
};

extern "C" void func_ov091_02299054(void);
extern "C" void func_ov091_02299050(Obj_ov091_02299530 *p);

extern "C" int func_ov091_02299410(void *self)
{
    ((UnkStruct_02299410 *) ((char *) self + 0x434))->f3();
    int tmp = func_ov002_02207f60(self);
    func_0208f210((char *) self + 0x3bc, 0, tmp);
    ((UnkStruct_02299410_2 *) ((char *) self + 0x3bc))->g2();
    if (func_0206fe54()) {
        func_ov002_02209eb8((char *) self + 0x434);
    }
    return 1;
}

int Obj_ov091_02299530::func_ov091_0229936c()
{
    static void (Obj_ov091_02299530::*table[6])() = {
        &Obj_ov091_02299530::func_ov091_02299244, &Obj_ov091_02299530::func_ov091_022991e8,
        &Obj_ov091_02299530::func_ov091_022991b0, &Obj_ov091_02299530::func_ov091_0229914c,
        &Obj_ov091_02299530::func_ov091_022990f4, &Obj_ov091_02299530::func_ov091_022990b0};
    unsigned char idx = state;
    (this->*table[idx])();
    return 1;
}

int Obj_ov091_02299530::func_ov091_022992f8()
{
    func_ov091_02299054();
    static void (Obj_ov091_02299530::*pmfTable[2])() = {&Obj_ov091_02299530::func_ov091_02299004,
                                                        &Obj_ov091_02299530::func_ov091_02298fb4};
    (this->*pmfTable[subState])();
    func_ov091_02299050(this);
    return 1;
}
