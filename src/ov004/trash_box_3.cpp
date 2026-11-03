/* trash_box_3: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222f7a0 @ 0x0222f7a0, 0x30 bytes, Thumb
 * func_ov004_0222f6e8 @ 0x0222f6e8, 0xb8 bytes, Thumb
 */

#include "cpp/ov004/Obj_ov004_022553d8.h"

struct UnkStruct_0222f7a0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void vcall(int a);
};

extern "C" int func_02056f94(void *p);
extern "C" void func_02055124(void *p);

typedef int (Obj_ov004_022553d8::*Pmf)(void);

extern "C" void func_ov004_0222f7a0(UnkStruct_0222f7a0 *self)
{
    if (func_02056f94((char *) self + 0x188) != 0) {
        self->vcall(0);
    } else {
        func_02055124((char *) self + 0xec);
    }
}

extern "C" int func_ov004_0222f6e8(Obj_ov004_022553d8 *self, int i)
{
    {
        static Pmf tbl[] = {&Obj_ov004_022553d8::func_ov004_0222f63c, &Obj_ov004_022553d8::func_ov004_0222f5f0,
                            &Obj_ov004_022553d8::func_ov004_0222f5c8, &Obj_ov004_022553d8::func_ov004_0222f584,
                            &Obj_ov004_022553d8::func_ov004_0222f54c, &Obj_ov004_022553d8::func_ov004_0222f518};
        if (i < 6) {
            if ((self->*(tbl[i]))()) {
                self->unk_61c = i;
                return 1;
            }
        }
    }
    return 0;
}
