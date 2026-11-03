/* sequence4_4: 7 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_022728a8 @ 0x022728a8, 0x1c bytes, Thumb, emits _ZN18Obj_ov068_0227775019func_ov068_022728a8Ev
 * func_ov068_02272874 @ 0x02272874, 0x34 bytes, Thumb, emits _ZN18Obj_ov068_0227775019func_ov068_02272874Ev
 * func_ov068_0227282c @ 0x0227282c, 0x48 bytes, Thumb, emits _ZN18Obj_ov068_0227775019func_ov068_0227282cEv
 * func_ov068_022727d0 @ 0x022727d0, 0x5c bytes, Thumb, emits _ZN18Obj_ov068_0227775019func_ov068_022727d0Ev
 * func_ov068_0227276c @ 0x0227276c, 0x64 bytes, Thumb, emits _ZN18Obj_ov068_0227775019func_ov068_0227276cEv
 * func_ov068_022726d4 @ 0x022726d4, 0x98 bytes, Thumb, emits _ZN18Obj_ov068_0227775019func_ov068_022726d4Ev
 * func_ov068_022726c8 @ 0x022726c8, 0xc bytes, Thumb, emits _ZN18Obj_ov068_0227775019func_ov068_022726c8Ev
 */

#include "cpp/ov068/Obj_ov068_02277750.h"
#include "cpp/main/Obj_020e2f6c.h"

extern "C" int func_020961a8(int);
extern "C" void func_02055060(Obj_020dd05c *, int, int, int, int, int);
extern "C" void func_ov009_02262ed4(void *, int);
extern "C" int func_02056f94(void *);
extern "C" void func_ov068_02272c64(void *);
extern "C" void func_02055124(void *);

extern "C" {
extern int func_ov068_0227207c(void);
extern void func_ov009_02262ef0(Obj_0213f090 *, int);
}

extern "C" int func_02095ec4(void);
extern "C" void *func_ov068_02272cd4(void *);
extern "C" int func_02095a8c(void *, int);

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

void Obj_ov068_02277750::func_ov068_022728a8()
{
    if (func_020961a8(4) != 0) {
        func_ov068_02272a7c(2);
    }
}

int Obj_ov068_02277750::func_ov068_02272874()
{
    func_02055060(&unk_13c, vfunc_64(), 1, 0x1000, 0, 0);
    return 1;
}

void Obj_ov068_02277750::func_ov068_0227282c()
{
    void *p = (void *) this;
    func_ov009_02262ed4((void *) ((char *) p + 0x238), 0x888);
    if (func_02056f94((void *) ((char *) p + 0x1d8)) != 0) {
        ((Obj_ov068_02277750 *) p)->func_ov068_02272a7c(3);
    }
    func_ov068_02272c64(p);
    func_02055124((void *) ((char *) p + 0x13c));
}

int Obj_ov068_02277750::func_ov068_022727d0()
{
    unk_2dd = 0;
    if (func_ov068_0227207c() == 0) {
        goto ret0;
    }
    {
        int v = vfunc_68();
        func_02055060(&unk_13c, v, 1, 0x1000, 0, 0);
    }
    func_ov009_02262ef0(&unk_238, 0x88a);
    return 1;
ret0:
    return 0;
}

void Obj_ov068_02277750::func_ov068_0227276c()
{
    unsigned char *self = (unsigned char *) this;
    if (func_02056f94(self + 0x1d8)) {
        unsigned char b = self[0x2dd];
        switch (b) {
            case 0x12:
                func_02095ec4();
                func_02095a8c(func_ov068_02272cd4(self), 4);
                break;
            case 0x1c:
                ((Obj_ov068_02277750 *) self)->func_ov068_02272a7c(4);
                // fall through
        }
        if (self[0x2dd] < 200) {
            self[0x2dd]++;
        }
    } else {
        func_02055124(self + 0x13c);
    }
}

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

void Obj_ov068_02277750::func_ov068_022726c8()
{
    func_ov068_02272a7c(5);
}
