/* layer_load_task_3: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b9c10 @ 0x020b9c10, 0x58 bytes, Thumb
 * func_020b9bbc @ 0x020b9bbc, 0x54 bytes, Thumb
 */

class UnkStruct_020b9c10 {
  public:
    virtual void func0();
    virtual void func1();
    char pad_04[8];
    unsigned char unk_0C;
    char pad_0D;
    unsigned char unk_0E;
    unsigned char unk_0F;
    struct UnkStruct_020b9c10_2 {
        int pad_00;
    } sub;
};

extern "C" void func_020b9c68(void *p);
extern "C" void func_020ba0f8(void *p, int a, int b, int c, int d, int e);
extern "C" int func_020ba0cc(void *p);
extern "C" int func_020b98c4(void *p);
extern "C" void func_020ba0c0(void *, int, int, int, int);
extern "C" unsigned char func_020ba0a4(void *);

class UnkStruct_020b9bbc {
  public:
    virtual void f0();
    virtual void f1();
    int unk_04;
    int unk_08;
    unsigned char unk_0C;
    unsigned char unk_0D;
    unsigned char unk_0E;
    unsigned char unk_0F;
};

extern "C" int func_020b9c10(UnkStruct_020b9c10 *self, int a, int b, int c, int d, int e)
{
    func_020b9c68(self);
    self->unk_0E = 4;
    func_020ba0f8(&self->sub, a, b, c, d, e);
    self->unk_0F = func_020ba0cc(&self->sub);
    self->unk_0C = 4;
    if (func_020b98c4(self)) {
        return 1;
    } else {
        self->func1();
        return 0;
    }
}

extern "C" int func_020b9bbc(UnkStruct_020b9bbc *self, int a, int b, int c, int d)
{
    func_020b9c68(self);
    self->unk_0E = 5;
    func_020ba0c0((void *) ((char *) self + 0x10), a, b, c, d);
    self->unk_0F = func_020ba0a4((void *) ((char *) self + 0x10));
    self->unk_0C = 4;
    if (func_020b98c4(self) != 0) {
        return 1;
    }
    self->f1();
    return 0;
}
