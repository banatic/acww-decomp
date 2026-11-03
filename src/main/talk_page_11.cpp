/* talk_page_11: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206cb88 @ 0x0206cb88, 0x50 bytes, Thumb
 * func_0206cb38 @ 0x0206cb38, 0x50 bytes, Thumb
 * func_0206caf0 @ 0x0206caf0, 0x48 bytes, Thumb
 */

extern "C" int func_02067a74(void *arg);
extern "C" void func_020a9334(void *obj, int value);
extern "C" void func_020a7994(void *ptr, int value);

class UnkStruct_0206cb88 {
  public:
    virtual void f1();
    virtual void f2();
    virtual void f3();
    virtual int f4();
};

struct Context {
    char pad_00[0x2C];
    char *base;
};

struct UnkStruct_0206cb38;

extern "C" int func_02067a3c(char *ptr);

class UnkStruct_0206cb38_2 {
  public:
    virtual int f0();
    virtual int f1();
    virtual int f2();
    virtual int f3();
};

struct UnkStruct_0206cb38 {
    char pad_00[0x2c];
    char *unk_2C;
};

extern "C" {
struct UnkStruct_0206caf0;
struct UnkStruct_0206caf0_2;
struct UnkStruct_0206caf0_2 *func_0206807c(void *obj);
}

struct UnkStruct_0206caf0_2 {
    virtual void f0() = 0;
    virtual void f1() = 0;
    virtual void f2() = 0;
    virtual int f3() = 0;
};

struct UnkStruct_0206caf0 {
    char pad_00[0x2c];
    void *obj;
};

extern "C" void func_0206cb88(Context *p)
{
    func_02067a74(p->base);
    int result1 = ((UnkStruct_0206cb88 *) (p->base + 0x1C70))->f4();
    func_020a9334(p, result1);
    int result2 = ((UnkStruct_0206cb88 *) (p->base + 0x1C70))->f4();
    func_020a7994(p->base + 0x1A58, result2);
    *(int *) (p->base + 0x1A60) = 0;
}

extern "C" void func_0206cb38(UnkStruct_0206cb38 *self)
{
    func_02067a3c(self->unk_2C);
    int a = ((UnkStruct_0206cb38_2 *) (self->unk_2C + 0x1c8c))->f3();
    func_020a9334((void *) self, a);
    int b = ((UnkStruct_0206cb38_2 *) (self->unk_2C + 0x1c8c))->f3();
    func_020a7994((void *) (self->unk_2C + 0x1a58), b);
    *(int *) (self->unk_2C + 0x1a60) = 0;
}

extern "C" void func_0206caf0(struct UnkStruct_0206caf0 *self)
{
    func_020a9334((void *) self, func_0206807c(self->obj)->f3());
    func_020a7994((char *) self->obj + 0x1a58, func_0206807c(self->obj)->f3());
    *(int *) ((char *) self->obj + 0x1a60) = 1;
}
