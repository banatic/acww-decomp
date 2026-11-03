/* talk_page_9: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206c9d0 @ 0x0206c9d0, 0x48 bytes, Thumb
 * func_0206c988 @ 0x0206c988, 0x48 bytes, Thumb
 * func_0206c940 @ 0x0206c940, 0x48 bytes, Thumb
 * func_0206c8f0 @ 0x0206c8f0, 0x50 bytes, Thumb
 * func_0206c8a0 @ 0x0206c8a0, 0x50 bytes, Thumb
 * func_0206c850 @ 0x0206c850, 0x50 bytes, Thumb
 */

class VirtualObj {
  public:
    virtual void a();
    virtual void b();
    virtual void c();
    virtual int getValue();
};

struct UnkStruct_0206c9d0;

struct UnkStruct_0206c9d0_2 {
    char pad_00[0x2c];
    UnkStruct_0206c9d0 *unk_2C;
};

extern "C" VirtualObj *func_02067fd4(UnkStruct_0206c9d0 *);
extern "C" void func_020a7994(char *, int);

class UnkStruct_0206c988 {
  public:
    virtual int m0();
    virtual int m1();
    virtual int m2();
    virtual int m3();
};

typedef struct {
    char pad_00[0x2c];
    void *unk_2C;
} UnkStruct_0206c988_2;

typedef struct {
    char pad_00[0x1a58];
    int unk_1A58;
    char pad_1A5C[4];
    int unk_1A60;
} BigStruct;

extern "C" UnkStruct_0206c988 *func_02067fa4(void *obj);
extern "C" void func_020a9334(void *a, int b);

class UnkStruct_0206c940 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual int f3();
};

struct UnkStruct_0206c940_2 {
    char pad_00[0x2c];
    UnkStruct_0206c940 *obj;
};

extern "C" UnkStruct_0206c940 *func_02067f74(UnkStruct_0206c940 *);

class VirtualClass {
  public:
    virtual int m0();
    virtual int m1();
    virtual int m2();
    virtual int m3();
};

typedef struct UnkStruct_0206c8f0 {
    char pad_00[0x2c];
    char *base;
} UnkStruct_0206c8f0;

extern "C" int func_020679b0(char *p);

extern "C" {
extern int func_02067964(void *);
}

struct SelfType {
    char pad_00[0x2c];
    char *ptr;
};

struct UnkStruct_0206c850 {
    char pad_00[0x2c];
    char *base;
};

class UnkStruct_0206c850_2 {
  public:
    virtual int vf0();
    virtual int vf1();
    virtual int vf2();
    virtual int vf3(); // vtable offset 0xc
};

extern "C" int func_020678f8(char *);

extern "C" void func_0206c9d0(UnkStruct_0206c9d0_2 *self)
{
    func_020a9334((void *) self, func_02067fd4(self->unk_2C)->getValue());
    func_020a7994((char *) self->unk_2C + 0x1a58, func_02067fd4(self->unk_2C)->getValue());
    *(int *) ((char *) self->unk_2C + 0x1a60) = 1;
}

extern "C" void func_0206c988(UnkStruct_0206c988_2 *param)
{
    UnkStruct_0206c988 *obj = func_02067fa4(param->unk_2C);
    int ret = obj->m3();
    func_020a9334(param, ret);

    obj = func_02067fa4(param->unk_2C);
    ret = obj->m3();
    func_020a7994((char *) (&((BigStruct *) param->unk_2C)->unk_1A58), ret);
    ((BigStruct *) param->unk_2C)->unk_1A60 = 1;
}

extern "C" void func_0206c940(UnkStruct_0206c940_2 *base)
{
    UnkStruct_0206c940 *p = func_02067f74(base->obj);
    int ret = p->f3();
    func_020a9334((void *) base, ret);

    UnkStruct_0206c940 *q = func_02067f74(base->obj);
    int ret2 = q->f3();
    func_020a7994((char *) ((char *) base->obj + 0x1a58), ret2);

    *((int *) ((char *) base->obj + 0x1a60)) = 1;
}

extern "C" void func_0206c8f0(UnkStruct_0206c8f0 *self)
{
    func_020679b0(self->base);
    int r1 = ((VirtualClass *) (self->base + 0x1ccc))->m3();
    func_020a9334((void *) self, r1);
    int r2 = ((VirtualClass *) (self->base + 0x1ccc))->m3();
    func_020a7994(self->base + 0x1a58, r2);
    *(int *) (self->base + 0x1a60) = 0;
}

extern "C" void func_0206c8a0(SelfType *self)
{
    func_02067964(self->ptr);
    int res1 = ((VirtualClass *) (self->ptr + 0x1cec))->m3();
    func_020a9334(self, res1);
    int res2 = ((VirtualClass *) (self->ptr + 0x1cec))->m3();
    func_020a7994((char *) (self->ptr + 0x1a58), res2);
    *(int *) (self->ptr + 0x1a60) = 0;
}

extern "C" void func_0206c850(struct UnkStruct_0206c850 *self)
{
    func_020678f8(self->base);
    int ret1 = ((UnkStruct_0206c850_2 *) (self->base + 0x1d0c))->vf3();
    func_020a9334((void *) self, ret1);
    int ret2 = ((UnkStruct_0206c850_2 *) (self->base + 0x1d0c))->vf3();
    func_020a7994(self->base + 0x1a58, ret2);
    *(int *) (self->base + 0x1a60) = 0;
}
