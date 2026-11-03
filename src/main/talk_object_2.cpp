/* talk_object_2: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206741c @ 0x0206741c, 0xbc bytes, Thumb
 * func_020673e0 @ 0x020673e0, 0x3c bytes, Thumb
 */

#include "types.h"

class UnkStruct_0206741c_2 {
  public:
    virtual void m0();
    virtual void m1();
    virtual int m2();
};

struct UnkStruct_0206741c {
    u8 pad_000[0x684];
    void *unk_684;
    u8 pad_688[0xb14 - 0x688];
    UnkStruct_0206741c_2 unk_B14;
    u8 pad_B18[0x13b8 - 0xb18];
    void *unk_13B8;
    u8 pad_13BC[0x149c - 0x13bc];
    void *unk_149C;
    u8 pad_14A0[0x14ac - 0x14a0];
    void *unk_14AC;
    u8 pad_14B0[0x1a48 - 0x14b0];
    u8 unk_1A48;
    u8 pad_1A49[0x1e94 - 0x1a49];
    u8 unk_1E94;
    u8 unk_1E95;
    u8 unk_1E96;
};

extern "C" {
int func_020a8248(void *);
int func_020a8260(void *);
void func_020a8290(void *, void *);
void func_0206c19c(void *, u32);
void func_0206844c(UnkStruct_0206741c *, void *, int);
void func_02067588(UnkStruct_0206741c *);
void func_020674d8(UnkStruct_0206741c *);
void func_020a9508(void *);
void func_020a94c8(void *, int);
void func_0206bd40(void *, int);
}

class SomeObj {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual int v3();
};

extern "C" SomeObj *func_020ab4d4(void *p);
extern "C" void *func_0206923c(void *buf, void *arg);
extern "C" void func_020691cc(void *buf, int val);
extern "C" volatile int *func_0206921c(void *buf);

extern "C" void func_0206741c(UnkStruct_0206741c *self)
{
    u32 flag;
    int ret;
    u32 local;
    int vres;

    self->unk_1E95 = 1;
    self->unk_1E94 = 1;
    self->unk_1E96 = 0;

    flag = (func_020a8248((void *) &self->unk_14AC) == 1);
    func_0206c19c((void *) &self->unk_684, flag);

    ret = func_020a8260((void *) &self->unk_14AC);
    func_0206bd40((void *) &self->unk_13B8, ret);
    self->unk_1A48 = (ret == 1);

    func_020a8290((void *) &local, (void *) &self->unk_14AC);
    func_0206844c(self, (void *) &local, 0);

    func_02067588(self);
    func_020674d8(self);

    func_020a9508((void *) &self->unk_149C);

    vres = self->unk_B14.m2();
    func_020a94c8((void *) &self->unk_149C, vres);
}

extern "C" void func_020673e0(void *arg)
{
    char buf[0x44];
    SomeObj *obj = func_020ab4d4((char *) arg + 0x31c);
    func_0206923c(buf, arg);
    int result = obj->v3();
    func_020691cc(buf, result);
    func_0206921c(buf);
}
