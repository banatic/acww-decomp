/* func_0206a33c @ 0x0206a33c, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

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
extern "C" void func_020a9334(UnkStruct_0206a33c_2 *self, int value);
extern "C" void func_020a7994(void *p, int value);

extern "C" void func_0206a33c(UnkStruct_0206a33c_2 *self)
{
    UnkStruct_0206a33c *v;
    int a, b;
    v = func_02068058(self->unk_24);
    a = v->f3();
    func_020a9334(self, a);
    v = func_02068058(self->unk_24);
    b = v->f3();
    func_020a7994((char *) self->unk_24 + 0x1a58, b);
    *(int *) ((char *) self->unk_24 + 0x1a60) = 1;
}
