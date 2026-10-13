/* func_ov105_0229da9c @ 0x0229da9c, 0x60 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

class Sub1 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

typedef struct Sub2 {
    char pad_00;
} Sub2;

typedef struct UnkStruct_0229da9c {
    char pad_00[0x2c2];
    char flag;
    char pad_2C3[0x24a4 - 0x2c2 - 1];
    Sub1 sub1;
    char pad2[0x5fb8 - 0x24a4 - sizeof(Sub1)];
    Sub2 sub2;
} UnkStruct_0229da9c;

extern "C" void func_ov002_02207fc0(UnkStruct_0229da9c *self);
extern "C" void func_ov002_0220a374(Sub1 *sub);
extern "C" int func_ov002_0220a768(Sub2 *sub, int);
extern "C" int func_ov002_0220a72c(Sub2 *sub, int);
extern "C" void func_ov002_0220a0b4(Sub1 *sub, int, int);
extern "C" void func_ov002_02208098(UnkStruct_0229da9c *self, int);

extern "C" void func_ov105_0229da9c(UnkStruct_0229da9c *self)
{
    int ret1, ret2;
    func_ov002_02207fc0(self);
    self->flag = 1;
    func_ov002_0220a374(&self->sub1);
    self->sub1.f3();
    ret1 = func_ov002_0220a768(&self->sub2, 4);
    ret2 = func_ov002_0220a72c(&self->sub2, 4);
    func_ov002_0220a0b4(&self->sub1, ret1, ret2);
    func_ov002_02208098(self, 30);
}
