/* mailbox_scene_10: 2 functions, module ov106
 * mwccarm 1.2/base -O4,s
 * func_ov106_0229ef8c @ 0x0229ef8c, 0x27c bytes, Thumb, emits _ZN18Obj_ov106_0229f6e019func_ov106_0229ef8cEv
 * func_ov106_0229ef30 @ 0x0229ef30, 0x5c bytes, Thumb, emits _ZN18Obj_ov106_0229f6e019func_ov106_0229ef30Ev
 */

#include "cpp/ov106/Obj_ov106_0229f6e0.h"

typedef void (Obj_ov106_0229f6e0::*PMF)();

extern "C" void func_0206f58c(void);
extern "C" int func_0206f56c(void);
extern "C" void func_ov106_0229cc50(unsigned char *);
extern "C" void func_ov106_0229c378(unsigned char *);
extern "C" int func_ov002_02207d24(unsigned char *, int);
extern "C" void func_ov106_0229e9a4(unsigned char *);
extern "C" void func_ov106_0229e99c(unsigned char *);

void Obj_ov106_0229f6e0::func_ov106_0229ef8c()
{
    static PMF table[39] = {&Obj_ov106_0229f6e0::func_ov106_0229e7e0, &Obj_ov106_0229f6e0::func_ov106_0229e734,
                            &Obj_ov106_0229f6e0::func_ov106_0229e6c4, &Obj_ov106_0229f6e0::func_ov106_0229e67c,
                            &Obj_ov106_0229f6e0::func_ov106_0229e544, &Obj_ov106_0229f6e0::func_ov106_0229e4fc,
                            &Obj_ov106_0229f6e0::func_ov106_0229e430, &Obj_ov106_0229f6e0::func_ov106_0229e2dc,
                            &Obj_ov106_0229f6e0::func_ov106_0229e1d8, &Obj_ov106_0229f6e0::func_ov106_0229e134,
                            &Obj_ov106_0229f6e0::func_ov106_0229e114, &Obj_ov106_0229f6e0::func_ov106_0229e078,
                            &Obj_ov106_0229f6e0::func_ov106_0229e014, &Obj_ov106_0229f6e0::func_ov106_0229dfcc,
                            &Obj_ov106_0229f6e0::func_ov106_0229df98, &Obj_ov106_0229f6e0::func_ov106_0229df70,
                            &Obj_ov106_0229f6e0::func_ov106_0229df40, &Obj_ov106_0229f6e0::func_ov106_0229df14,
                            &Obj_ov106_0229f6e0::func_ov106_0229dec0, &Obj_ov106_0229f6e0::func_ov106_0229de78,
                            &Obj_ov106_0229f6e0::func_ov106_0229de28, &Obj_ov106_0229f6e0::func_ov106_0229ddf0,
                            &Obj_ov106_0229f6e0::func_ov106_0229ddb4, &Obj_ov106_0229f6e0::func_ov106_0229dd64,
                            &Obj_ov106_0229f6e0::func_ov106_0229dd44, &Obj_ov106_0229f6e0::func_ov106_0229dd10,
                            &Obj_ov106_0229f6e0::func_ov106_0229dcb0, &Obj_ov106_0229f6e0::func_ov106_0229dc80,
                            &Obj_ov106_0229f6e0::func_ov106_0229dc04, &Obj_ov106_0229f6e0::func_ov106_0229dad4,
                            &Obj_ov106_0229f6e0::func_ov106_0229da80, &Obj_ov106_0229f6e0::func_ov106_0229d9fc,
                            &Obj_ov106_0229f6e0::func_ov106_0229d978, &Obj_ov106_0229f6e0::func_ov106_0229d948,
                            &Obj_ov106_0229f6e0::func_ov106_0229d8e0, &Obj_ov106_0229f6e0::func_ov106_0229d860,
                            &Obj_ov106_0229f6e0::func_ov106_0229d810, &Obj_ov106_0229f6e0::func_ov106_0229d7d4,
                            &Obj_ov106_0229f6e0::func_ov106_0229d7ac};
    (this->*table[subState])();
}

int Obj_ov106_0229f6e0::func_ov106_0229ef30()
{
    unsigned char *self = (unsigned char *) this;
    if (((void) (func_0206f58c()), func_0206f56c()) != 0) {
        if (self[0x8d] == 0 || self[0x8d] == 1 || self[0x8d] == 7) {
            func_ov106_0229cc50(self);
            func_ov106_0229c378(self);
            func_ov002_02207d24(self + 0x21b8, 0);
            return 1;
        }
    }
    func_ov106_0229e9a4(self);
    ((Obj_ov106_0229f6e0 *) self)->func_ov106_0229ef8c();
    func_ov106_0229e99c(self);
    return 1;
}
