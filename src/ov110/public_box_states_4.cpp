/* public_box_states_4: 3 functions, module ov110
 * mwccarm 1.2/base -O4,s
 * func_ov110_0229ea10 @ 0x0229ea10, 0xa4 bytes, Thumb
 * func_ov110_0229e954 @ 0x0229e954, 0xbc bytes, Thumb, emits _ZN18Obj_ov110_0229ecb819func_ov110_0229e954Ev
 * func_ov110_0229e7cc @ 0x0229e7cc, 0x188 bytes, Thumb, emits _ZN18Obj_ov110_0229ecb819func_ov110_0229e7ccEv
 */

#include "cpp/ov110/Obj_ov110_0229ecb8.h"

struct Main;

extern "C" {
int func_ov110_0229c2c8(struct Main *self, int mode);
void func_ov110_0229ce0c(struct Main *self);
int func_0206fe54(void);
void func_ov002_02209eb8(void *ptr);
void func_ov094_0229a7cc(void *ptr, int a, unsigned int b);
void func_ov094_0229a850(void *ptr, int a, unsigned int b);
void func_ov094_0229b738(void *ptr, int a, unsigned int b);
void func_ov094_02299d84(void *receiver, int value);
}

struct Main {
    unsigned char pad_00[0x98];
    unsigned int unk_98;
    unsigned int unk_9C;
};

struct UnkStruct_0229ea10 {
    virtual int v0();
    virtual int v1();
    virtual int v2();
};

typedef void (Obj_ov110_0229ecb8::*PMF)();

extern "C" int func_ov110_0229ea10(struct Main *self)
{
    if (func_ov110_0229c2c8(self, 1) == 0) {
        return 1;
    }
    if (((void) (((UnkStruct_0229ea10 *) ((char *) self + 0x21f8))->v2()), func_0206fe54()) != 0) {
        func_ov002_02209eb8((void *) ((char *) self + 0x22e0));
    }
    func_ov110_0229ce0c(self);
    if (func_ov110_0229c2c8(self, 0x80) != 0) {
        func_ov094_0229a7cc((void *) ((char *) self + 0x138), 0, self->unk_9C);
    }
    if (func_ov110_0229c2c8(self, 2) != 0) {
        func_ov094_0229a850((void *) ((char *) self + 0x138), 0, self->unk_98);
        func_ov094_0229b738((void *) ((char *) self + 0xb98), 0, self->unk_98);
        func_ov094_02299d84((void *) ((char *) self + 0xbc0), self->unk_98);
    }
    return 1;
}

int Obj_ov110_0229ecb8::func_ov110_0229e954()
{
    typedef void (Obj_ov110_0229ecb8::*PMF)();
    static PMF tbl[7] = {&Obj_ov110_0229ecb8::func_ov110_0229e718, &Obj_ov110_0229ecb8::func_ov110_0229e68c,
                         &Obj_ov110_0229ecb8::func_ov110_0229e60c, &Obj_ov110_0229ecb8::func_ov110_0229e5d4,
                         &Obj_ov110_0229ecb8::func_ov110_0229e564, &Obj_ov110_0229ecb8::func_ov110_0229e4fc,
                         &Obj_ov110_0229ecb8::func_ov110_0229e4b0};
    func_ov110_0229e330();
    (this->*tbl[state])();
    func_ov110_0229e2f8();
    return 1;
}

void Obj_ov110_0229ecb8::func_ov110_0229e7cc()
{
    static struct {
        PMF a[16];
        PMF b[6];
    } tbl = {
        {&Obj_ov110_0229ecb8::func_ov110_0229e14c, &Obj_ov110_0229ecb8::func_ov110_0229e0f8,
         &Obj_ov110_0229ecb8::func_ov110_0229e05c, &Obj_ov110_0229ecb8::func_ov110_0229df2c,
         &Obj_ov110_0229ecb8::func_ov110_0229ddb4, &Obj_ov110_0229ecb8::func_ov110_0229dcc0,
         &Obj_ov110_0229ecb8::func_ov110_0229dc40, &Obj_ov110_0229ecb8::func_ov110_0229dbf4,
         &Obj_ov110_0229ecb8::func_ov110_0229dba4, &Obj_ov110_0229ecb8::func_ov110_0229db70,
         &Obj_ov110_0229ecb8::func_ov110_0229db48, &Obj_ov110_0229ecb8::func_ov110_0229db18,
         &Obj_ov110_0229ecb8::func_ov110_0229daec, &Obj_ov110_0229ecb8::func_ov110_0229da98,
         &Obj_ov110_0229ecb8::func_ov110_0229da50, &Obj_ov110_0229ecb8::func_ov110_0229da00},
        {&Obj_ov110_0229ecb8::func_ov110_0229d9c8, &Obj_ov110_0229ecb8::func_ov110_0229d98c,
         &Obj_ov110_0229ecb8::func_ov110_0229d948, &Obj_ov110_0229ecb8::func_ov110_0229d928,
         &Obj_ov110_0229ecb8::func_ov110_0229d8f4, &Obj_ov110_0229ecb8::func_ov110_0229d8b0},
    };
    unsigned char idx;

    idx = subState;
    (this->*tbl.a[idx])();
}
