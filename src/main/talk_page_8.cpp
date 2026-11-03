/* talk_page_8: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206c6fc @ 0x0206c6fc, 0x50 bytes, Thumb
 * func_0206c6ac @ 0x0206c6ac, 0x50 bytes, Thumb
 * func_0206c65c @ 0x0206c65c, 0x50 bytes, Thumb
 * func_0206c60c @ 0x0206c60c, 0x50 bytes, Thumb
 */

extern "C" int func_020677d0(void *p);
extern "C" void func_020a9334(void *self, int val);

class UnkStruct_0206c6fc {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual int method();
};

typedef struct UnkStruct_0206c6fc_2 {
    unsigned char pad_00[0x2c];
    void *unk_2C;
} UnkStruct_0206c6fc_2;

class Obj1 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual int method();
};

struct Sys {
    char pad_00[0x1a58];
    int unk_1A58;
    int pad_1A5C;
    int flag;
    char pad_1A64[0x3a0];
    Obj1 obj1;
};

struct Parent {
    char pad_00[0x2c];
    Sys *sys;
};

extern "C" int func_0206777c(Sys *sys);
extern "C" void func_020a7994(int *field1, int r);

class UnkStruct_0206c65c;

struct UnkStruct_0206c65c_2 {
    char pad_00[0x2c];
    char *unk_2C;
};

extern "C" int func_02067728(char *p);

class UnkStruct_0206c65c {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual int method();
};

extern "C" int func_0206781c(void *p);

class UnkStruct_0206c60c {
  public:
    virtual int vf0();
    virtual int vf1();
    virtual int vf2();
    virtual int vf3();
};

struct UnkStruct_0206c60c_2 {
    char pad_00[0x1a58];
    int unk_1A58;
    char pad_1A5C[0x1a60 - 0x1a58 - 4];
    int unk_1A60;
    char pad_1A64[0x1d4c - 0x1a60 - 4];
    UnkStruct_0206c60c obj;
};

struct UnkStruct_0206c60c_3 {
    char pad_00[0x2c];
    UnkStruct_0206c60c_2 *b;
};

extern "C" void func_0206c6fc(UnkStruct_0206c6fc_2 *self)
{
    func_020677d0(self->unk_2C);
    int ret1 = ((UnkStruct_0206c6fc *) ((char *) self->unk_2C + 0x1da8))->method();
    func_020a9334(self, ret1);
    int ret2 = ((UnkStruct_0206c6fc *) ((char *) self->unk_2C + 0x1da8))->method();
    func_020a7994((int *) ((char *) self->unk_2C + 0x1a58), ret2);
    *(int *) ((char *) self->unk_2C + 0x1a60) = 1;
}

extern "C" void func_0206c6ac(Parent *self)
{
    func_0206777c(self->sys);
    int r1 = self->sys->obj1.method();
    func_020a9334((void *) self, r1);
    int r2 = self->sys->obj1.method();
    func_020a7994(&self->sys->unk_1A58, r2);
    self->sys->flag = 1;
}

// Declarations for external functions and types
extern "C" void func_0206c65c(UnkStruct_0206c65c_2 *self)
{
    func_02067728(self->unk_2C);
    int res1 = ((UnkStruct_0206c65c *) (self->unk_2C + 0x1e24))->method();
    func_020a9334((void *) self, res1);
    int res2 = ((UnkStruct_0206c65c *) (self->unk_2C + 0x1e24))->method();
    func_020a7994((int *) (self->unk_2C + 0x1a58), res2);
    *((int *) (self->unk_2C + 0x1a60)) = 1;
}

extern "C" void func_0206c60c(UnkStruct_0206c60c_3 *this_)
{
    int r1;
    func_0206781c(this_->b);
    r1 = this_->b->obj.vf3();
    func_020a9334(this_, r1);
    r1 = this_->b->obj.vf3();
    func_020a7994(&this_->b->unk_1A58, r1);
    this_->b->unk_1A60 = 1;
}
