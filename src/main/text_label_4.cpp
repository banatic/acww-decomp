/* text_label_4: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02070a04 @ 0x02070a04, 0x4e bytes, Thumb
 * func_020709c4 @ 0x020709c4, 0x40 bytes, Thumb
 * func_0207099c @ 0x0207099c, 0x28 bytes, Thumb
 * func_02070978 @ 0x02070978, 0x24 bytes, Thumb
 */

#include "types.h"

extern "C" void func_02051648(void *p);
extern "C" void func_02051694(void *p);

struct UnkStruct_02070a04 {
    unsigned char pad_00[0x10];
    int unk_10;
    unsigned char pad_14[0x1c];
    int unk_30;
    unsigned char pad_34[0x23];
    unsigned char unk_57;
};

class UnkStruct_02070a04_2 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual int f3();
    unsigned char pad_04[0x64];
    UnkStruct_02070a04 *unk_68;
};

struct UnkStruct_020709c4 {
    u32 pad_00[4];
    int unk_10;
    u32 pad_14[7];
    int unk_30;
};

class UnkStruct_020709c4_2 {
  public:
    virtual int m0();
    virtual int m1();
    virtual int m2();
    virtual int m3();
    unsigned char pad_04[0x64];
    UnkStruct_020709c4 *s;
};

extern "C" void func_02051624(void *);

struct Target {
    char pad[0x10];
    int unk_10;
};

class UnkStruct_0207099c {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual int v3();
    char pad[0x64];
    Target *p;
};

struct UnkStruct_02070978 {
    unsigned char pad0[0x10];
    int unk_10;
    unsigned char pad_14[0x30 - 0x14];
    int unk_30;
};

class UnkStruct_02070978_2 {
  public:
    virtual int v0();
    virtual int v1();
    virtual int v2();
    virtual int v3();
    unsigned char pad0[0x64];
    UnkStruct_02070978 *sub;
};

extern "C" void func_02070a04(UnkStruct_02070a04_2 *a, int b, int c)
{
    UnkStruct_02070a04 *p = a->unk_68;
    if (p) {
        p->unk_10 = a->f3();
        if (c) {
            a->unk_68->unk_57 = 1;
        } else {
            a->unk_68->unk_57 = 0;
        }
        if (b) {
            func_02051648(a->unk_68);
        } else {
            a->unk_68->unk_30 = 0;
        }
        func_02051694(a->unk_68);
    }
}

extern "C" void func_020709c4(UnkStruct_020709c4_2 *obj, int flag, int add)
{
    UnkStruct_020709c4 *sp = obj->s;
    if (sp) {
        sp->unk_10 = obj->m3();
        if (flag) {
            func_02051648((void *) obj->s);
        } else {
            obj->s->unk_30 = 0;
        }
        obj->s->unk_30 += add;
        func_02051694((void *) obj->s);
    }
}

extern "C" void func_0207099c(UnkStruct_0207099c *self)
{
    Target *q;
    if ((q = self->p) != 0) {
        q->unk_10 = self->v3();
        func_02051624(self->p);
        func_02051694(self->p);
    }
}

extern "C" void func_02070978(UnkStruct_02070978_2 *self, int arg)
{
    UnkStruct_02070978 *p = self->sub;
    if (p == 0) {
        return;
    }
    p->unk_10 = self->v3();
    self->sub->unk_30 = arg;
    func_02051694((void *) self->sub);
}
