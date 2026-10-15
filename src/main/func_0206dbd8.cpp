/* func_0206dbd8 @ 0x0206dbd8, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0206dbd8 {
    unsigned char pad_00[0x10];
    int value;
};

class UnkStruct_0206dbd8_2 {
  public:
    virtual void f0() = 0;
    virtual void f1() = 0;
    virtual void f2() = 0;
    virtual int f3() = 0;
    unsigned char pad_04[0x60];
    UnkStruct_0206dbd8 *sub;
    unsigned char pad_68[0x4];
    unsigned char flag;
};

extern "C" void func_0206dc1c(UnkStruct_0206dbd8_2 *self);
extern "C" void func_02051624(UnkStruct_0206dbd8 *p);
extern "C" void func_02051694(UnkStruct_0206dbd8 *p);

extern "C" void func_0206dbd8(UnkStruct_0206dbd8_2 *self, int flag)
{
    if (self->flag != 0) {
        func_0206dc1c(self);
        if (self->sub != 0) {
            self->flag = 0;
            UnkStruct_0206dbd8 *sub = self->sub;
            sub->value = self->f3();
            if (flag != 0) {
                func_02051624(self->sub);
            }
            func_02051694(self->sub);
        }
    }
}
