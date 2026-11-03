/* cafe_room_3: 2 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_022750d0 @ 0x022750d0, 0x70 bytes, Thumb
 * func_ov068_0227507c @ 0x0227507c, 0x54 bytes, Thumb, emits _ZN18Obj_ov068_02277f3c19func_ov068_0227507cEv
 */

#include "cpp/ov068/Obj_ov068_02277f3c.h"

class UnkStruct_022750d0 {
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
    virtual void v24(int arg);
    char pad_04[0x28c];
    int unk_290;
    int unk_294;
    char unk_298;
    char pad_299[3];
    int unk_29C;
    char pad_2A0[180];
    int unk_354;
    char pad_358[160];
    int unk_3F8;
};

extern UnkStruct_022750d0 *data_ov068_022788b0;
extern "C" void func_ov004_0222c590(UnkStruct_022750d0 *p, int arg);
extern "C" int func_ov004_0222c5c8(UnkStruct_022750d0 *p, int *arg);
extern "C" int func_ov004_0222c62c(void *a, void *b, void *c, void *d);
extern int data_ov068_02277fa4;
extern int data_ov068_02277fb0;
extern "C" int func_020e895c(int *addr, int val, int mode);
extern "C" void NNS_G3dMdlSetMdlAlpha(void *ptr, unsigned int idx, unsigned char byte);

typedef struct InnerStruct {
    unsigned char pad_00[0x18];
    unsigned char count;
} InnerStruct;

typedef struct OuterStruct {
    unsigned char pad_00[0x148];
    InnerStruct *inner;
    unsigned char pad_14C[0x144];
    int unk_290;
    int unk_294;
} OuterStruct;

extern "C" int func_ov068_022750d0(UnkStruct_022750d0 *p)
{
    data_ov068_022788b0 = p;
    func_ov004_0222c590(p, 1);
    func_ov004_0222c5c8(p, &data_ov068_02277fa4);
    p->unk_294 = 1;
    p->unk_290 = p->unk_294;
    func_ov004_0222c62c(&data_ov068_02277fb0, &p->unk_29C, &p->unk_354, &p->unk_3F8);
    p->v24(1);
    p->unk_298 = 1;
    return 1;
}

int Obj_ov068_02277f3c::func_ov068_0227507c()
{
    OuterStruct *self = (OuterStruct *) this;
    unsigned int i;
    unsigned int n;

    ((Obj_ov068_02277f3c *) self)->func_ov068_02274f18();
    if (self->unk_290 != self->unk_294) {
        func_020e895c(&self->unk_290, self->unk_294, 2);
    }

    n = self->inner->count;
    for (i = 0; i < n; i++) {
        NNS_G3dMdlSetMdlAlpha(self->inner, i, (unsigned char) self->unk_290);
    }

    return 1;
}
