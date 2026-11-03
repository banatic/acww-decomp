/* pockets_view_6: 3 functions, module ov099
 * mwccarm 1.2/base -O4,s
 * func_ov099_0229ddec @ 0x0229ddec, 0x90 bytes, Thumb
 * func_ov099_0229dd4c @ 0x0229dd4c, 0xa0 bytes, Thumb, emits _ZN18Obj_ov099_0229e04019func_ov099_0229dd4cEv
 * func_ov099_0229dbc8 @ 0x0229dbc8, 0x184 bytes, Thumb, emits _ZN18Obj_ov099_0229e04019func_ov099_0229dbc8Ev
 */

#include "cpp/ov099/Obj_ov099_0229e040.h"

class UnkStruct_0229ddec {
  public:
    virtual void f0();
    virtual void f1();
    virtual int f2();
};

extern "C" void func_ov002_0220919c(void *);
extern "C" int func_ov099_0229c2ac(void *, int);
extern "C" int func_0206fe54(void);
extern "C" void func_ov002_02209eb8(void *);
extern "C" void func_ov099_0229c994(void *);
extern "C" void func_ov094_0229a850(void *, int, int);
extern "C" void func_ov094_0229b738(void *, int, int);
extern "C" void func_ov094_02299d84(void *receiver, int value);

typedef void (Obj_ov099_0229e040::*PMF)();

extern "C" int func_ov099_0229ddec(void *p)
{
    func_ov002_0220919c((char *) p + 0x22d8);
    if (func_ov099_0229c2ac(p, 1) == 0) {
        return 1;
    }

    UnkStruct_0229ddec *obj = (UnkStruct_0229ddec *) ((char *) p + 0x218c);
    obj->f2();
    if (func_0206fe54() != 0) {
        func_ov002_02209eb8((char *) p + 0x2274);
    }

    func_ov099_0229c994(p);

    if (func_ov099_0229c2ac(p, 2) != 0) {
        func_ov094_0229a850((char *) p + 0xcc, 0, *(int *) ((char *) p + 0x27ec));
        func_ov094_0229b738((char *) p + 0xb2c, 0, *(int *) ((char *) p + 0x27ec));
        func_ov094_02299d84((char *) p + 0xb54, *(int *) ((char *) p + 0x27ec));
    }

    return 1;
}

int Obj_ov099_0229e040::func_ov099_0229dd4c()
{
    static PMF table[5] = {&Obj_ov099_0229e040::func_ov099_0229db94, &Obj_ov099_0229e040::func_ov099_0229db24,
                           &Obj_ov099_0229e040::func_ov099_0229dae8, &Obj_ov099_0229e040::func_ov099_0229da84,
                           &Obj_ov099_0229e040::func_ov099_0229da34};
    func_ov099_0229d910();
    (this->*table[state])();
    func_ov099_0229d8d8();
    return 1;
}

int Obj_ov099_0229e040::func_ov099_0229dbc8()
{
    func_ov099_0229d948();

    static struct {
        PMF a[16];
        PMF b[5];
    } tbl = {{&Obj_ov099_0229e040::func_ov099_0229d814, &Obj_ov099_0229e040::func_ov099_0229d7a4,
              &Obj_ov099_0229e040::func_ov099_0229d718, &Obj_ov099_0229e040::func_ov099_0229d698,
              &Obj_ov099_0229e040::func_ov099_0229d5c0, &Obj_ov099_0229e040::func_ov099_0229d518,
              &Obj_ov099_0229e040::func_ov099_0229d49c, &Obj_ov099_0229e040::func_ov099_0229d44c,
              &Obj_ov099_0229e040::func_ov099_0229d400, &Obj_ov099_0229e040::func_ov099_0229d3e0,
              &Obj_ov099_0229e040::func_ov099_0229d3b8, &Obj_ov099_0229e040::func_ov099_0229d388,
              &Obj_ov099_0229e040::func_ov099_0229d358, &Obj_ov099_0229e040::func_ov099_0229d304,
              &Obj_ov099_0229e040::func_ov099_0229d2bc, &Obj_ov099_0229e040::func_ov099_0229d278},
             {&Obj_ov099_0229e040::func_ov099_0229d240, &Obj_ov099_0229e040::func_ov099_0229d204,
              &Obj_ov099_0229e040::func_ov099_0229d1c0, &Obj_ov099_0229e040::func_ov099_0229d1a0,
              &Obj_ov099_0229e040::func_ov099_0229d168}};

    (this->*tbl.a[subState])();

    func_ov099_0229d940();
    return 1;
}
