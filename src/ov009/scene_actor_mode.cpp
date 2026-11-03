/* scene_actor_mode: 3 functions, module ov009
 * mwccarm 1.2/base -O4,s
 * func_ov009_02263b78 @ 0x02263b78, 0x30 bytes, Thumb, emits _ZN18Obj_ov009_022658dc19func_ov009_02263b78Ev
 * func_ov009_02263b34 @ 0x02263b34, 0x44 bytes, Thumb
 * func_ov009_02263ab0 @ 0x02263ab0, 0x84 bytes, Thumb, emits _ZN18Obj_ov009_022658dc19func_ov009_02263ab0Ev
 */

#include "cpp/ov009/Obj_ov009_022658dc.h"

extern "C" void func_02055124(Obj_020dd05c *);
extern "C" int func_02056f94(Obj_020dd184 *);
extern "C" void func_02055060(void *, int, int, int, int, int);

class UnkStruct_02263b34 {
  public:
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
    virtual void v24();
    virtual void v25();
    virtual int v26();
    char pad_04[0x12e];
    short unk_132;
    char pad_134[8];
    char unk_13C;
};

extern "C" int func_0204bba8(void *);
extern "C" void func_ov009_02262ef0(Obj_0213f090 *, int);

void Obj_ov009_022658dc::func_ov009_02263b78()
{
    func_02055124(&unk_13c);
    if (func_02056f94(static_cast<Obj_020dd184 *>(&unk_13c)) != 0) {
        vfunc_6c(4);
    }
}

extern "C" int func_ov009_02263b34(UnkStruct_02263b34 *obj)
{
    obj->unk_132 = 26;
    int ret = obj->v26();
    if (ret != 0) {
        func_02055060(&obj->unk_13C, ret, 1, 0x1000, 0, 0);
        return 1;
    } else {
        return 0;
    }
}

void Obj_ov009_022658dc::func_ov009_02263ab0()
{
    unsigned short tmp = unk_132;
    if (tmp != 0) {
        tmp--;
        unk_132 = tmp;
        if (unk_132 == 0) {
            if (func_0204bba8(&unk_136)) {
                func_ov009_02262ef0(&unk_238, 0x807);
            } else {
                func_ov009_02262ef0(&unk_238, 0x809);
            }
        }
    }
    if (unk_132 == 0) {
        func_02055124(&unk_13c);
        if (func_02056f94(static_cast<Obj_020dd184 *>(&unk_13c))) {
            vfunc_6c(0);
        }
    }
}
