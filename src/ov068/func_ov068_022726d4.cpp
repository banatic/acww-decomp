/* func_ov068_022726d4 @ 0x022726d4, 0x98 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov068_0227775019func_ov068_022726d4Ev
 */

#include "cpp/main/Obj_020e2f6c.h"
#include "cpp/ov068/Obj_ov068_02277750.h"

struct Manager {
    int pad_00[2];
    int unk_08;
};

extern "C" {
extern char data_ov068_02277890[];
Manager *func_020682e0(int index);
int func_020984e8(void);
void *func_02099870(int obj);
int func_020950c0(void *obj);
void func_020a8164(Base_02066994 &recv, const char *name);
void func_02066954(Base_02066994 &recv, int arg, int mode);
void func_02068340(Manager *manager, Base_02066994 *recv);
int func_02082438(Obj_020e2f6c *out, unsigned short *id);
Obj_020e2f6c *func_02094fd4(Obj_020e2f6c *obj);
Obj_020e2f6c *func_02094fbc(Obj_020e2f6c *obj);
}

// stack storage for one Obj_020e2f6c (vtable pointer plus 0x1c bytes)
struct Storage_020e2f6c {
    int words[8];
};

int Obj_ov068_02277750::func_ov068_022726d4()
{
    Manager *manager = func_020682e0(0);
    Base_02066994::vfunc_02066994_08();
    func_020a8164(*this, data_ov068_02277890);
    int ready;
    int context = func_020984e8();
    if (context && func_020950c0(func_02099870(context)) == 1) {
        ready = 1;
    } else {
        ready = 0;
    }
    unk_1E = ready;
    func_02068340(manager, this);
    manager->unk_08 = 1;
    Storage_020e2f6c obj;
    func_02094fd4((Obj_020e2f6c *) &obj);
    unsigned short id[2];
    id[1] = 0xd014;
    func_02082438((Obj_020e2f6c *) &obj, &id[1]);
    Obj_020e2f6c *p = (Obj_020e2f6c *) &obj;
    func_02066954(*this, p->vfunc_0c(), 0);
    func_02094fbc((Obj_020e2f6c *) &obj);
    return 1;
}
