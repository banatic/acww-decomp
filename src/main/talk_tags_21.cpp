/* talk_tags_21: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206a4a0 @ 0x0206a4a0, 0x70 bytes, Thumb
 * func_0206a438 @ 0x0206a438, 0x68 bytes, Thumb
 * func_0206a3cc @ 0x0206a3cc, 0x6c bytes, Thumb
 * func_0206a384 @ 0x0206a384, 0x48 bytes, Thumb
 * func_0206a33c @ 0x0206a33c, 0x48 bytes, Thumb
 */

class UnkStruct_0206a4a0 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual int v3();
};

extern "C" int func_020a82f8(int k);
extern "C" void func_020a9334(void *self, int v);
extern "C" UnkStruct_0206a4a0 *func_020668d4(UnkStruct_0206a4a0 *o);
extern "C" void func_020a7994(void *p, int v);

typedef struct {
    char pad_00[0x24];
    char *unk_24;
} UnkStruct_0206a438;

extern "C" int func_02067a74(void *);
extern "C" void func_0206bb9c(void *object, int code, const void *message);

class UnkStruct_0206a438_2 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual int f3(); // offset 0xc
};

extern unsigned char data_020df1b8[];

struct UnkStruct_0206a3cc {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual int VFunc();
};

struct UnkStruct_0206a3cc_2 {
    char pad_00[0x24];
    char *unk_24;
    char pad_28[0x5c - 0x28];
    int unk_5C;
};

extern "C" int func_02067a3c(char *p);
extern "C" void *func_0206807c(void *);

class VBase {
  public:
    virtual void v0() = 0;
    virtual void v1() = 0;
    virtual void v2() = 0;
    virtual int getValue() = 0;
};

struct UnkStruct_0206a384 {
    char pad_00[0x24];
    void *unk_24;
};

class UnkStruct_0206a33c {
  public:
    virtual void f0() = 0;
    virtual void f1() = 0;
    virtual void f2() = 0;
    virtual int f3() = 0;
};

struct UnkStruct_0206a33c_2 {
    char pad_00[0x24];
    void *unk_24;
};

extern "C" UnkStruct_0206a33c *func_02068058(void *p);

extern "C" void func_0206a4a0(unsigned char *self)
{
    UnkStruct_0206a4a0 *obj;

    func_020a9334(self, func_020a82f8(*(int *) (self + 0x5c)));
    obj = *(UnkStruct_0206a4a0 **) (*(char **) (self + 0x24) + 0x14a8);
    func_020a9334(self, func_020668d4(obj)->v3());
    func_020a9334(self, func_020a82f8(6));
    func_020a7994((void *) (*(char **) (self + 0x24) + 0x1a58), func_020668d4(obj)->v3());
    *(int *) (*(char **) (self + 0x24) + 0x1a60) = 0;
}

extern "C" void func_0206a438(UnkStruct_0206a438 *obj)
{
    if (func_02067a74(obj->unk_24) == 0) {
        func_0206bb9c(obj, 0xc39, &data_020df1b8);
    }

    int result1 = ((UnkStruct_0206a438_2 *) (obj->unk_24 + 0x1c70))->f3();
    func_020a9334((void *) obj, result1);

    int result2 = ((UnkStruct_0206a438_2 *) (obj->unk_24 + 0x1c70))->f3();
    func_020a7994(obj->unk_24 + 0x1a58, result2);

    *(int *) (obj->unk_24 + 0x1a60) = 0;
}

extern "C" void func_0206a3cc(UnkStruct_0206a3cc_2 *obj)
{
    func_02067a3c(obj->unk_24);
    func_020a9334((void *) obj, func_020a82f8(obj->unk_5C));
    func_020a9334((void *) obj, ((UnkStruct_0206a3cc *) (obj->unk_24 + 0x1c8c))->VFunc());
    func_020a9334((void *) obj, func_020a82f8(8));
    func_020a7994((void *) (obj->unk_24 + 0x1a58), ((UnkStruct_0206a3cc *) (obj->unk_24 + 0x1c8c))->VFunc());
    *((int *) (obj->unk_24 + 0x1a60)) = 0;
}

extern "C" void func_0206a384(UnkStruct_0206a384 *obj)
{
    func_020a9334(obj, ((VBase *) func_0206807c(obj->unk_24))->getValue());
    func_020a7994((char *) obj->unk_24 + 0x1a58, ((VBase *) func_0206807c(obj->unk_24))->getValue());
    *((int *) ((char *) obj->unk_24 + 0x1a60)) = 1;
}

extern "C" void func_0206a33c(UnkStruct_0206a33c_2 *self)
{
    UnkStruct_0206a33c *v;
    int a, b;
    v = func_02068058(self->unk_24);
    a = v->f3();
    func_020a9334((void *) self, a);
    v = func_02068058(self->unk_24);
    b = v->f3();
    func_020a7994((char *) self->unk_24 + 0x1a58, b);
    *(int *) ((char *) self->unk_24 + 0x1a60) = 1;
}
