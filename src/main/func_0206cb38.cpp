/* func_0206cb38 @ 0x0206cb38, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0206cb38;

extern "C" int func_02067a3c(char *ptr);
extern "C" void func_020a9334(UnkStruct_0206cb38 *self, int a);
extern "C" void func_020a7994(char *ptr, int b);

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

extern "C" void func_0206cb38(UnkStruct_0206cb38 *self)
{
    func_02067a3c(self->unk_2C);
    int a = ((UnkStruct_0206cb38_2 *) (self->unk_2C + 0x1c8c))->f3();
    func_020a9334(self, a);
    int b = ((UnkStruct_0206cb38_2 *) (self->unk_2C + 0x1c8c))->f3();
    func_020a7994(self->unk_2C + 0x1a58, b);
    *(int *) (self->unk_2C + 0x1a60) = 0;
}
