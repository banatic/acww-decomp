/* func_020f1c00 @ 0x020f1c00, 0x6c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern "C" void func_0210fc50(int *p, int arg);
extern "C" void *func_020f161c(void *self);

class UnkStruct_020f1c00 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10(int a, int b);
    signed char unk_04;
};

class UnkStruct_020f1c00_2 {
  public:
    char pad_00[0x2c];
    UnkStruct_020f1c00 *unk_2C;
    char pad_30[4];
    int unk_34;
};

extern "C" void func_020f1c00(UnkStruct_020f1c00_2 *self, int arg)
{
    int flag = (self->unk_34 != 0) ? 1 : 0;
    if (flag != 0) {
        if (self->unk_2C->unk_04 == 0x33) {
            arg++;
        }
        func_0210fc50(&self->unk_34, arg);
        return;
    } else {
        func_020f161c(self);
        self->unk_2C->v10(1, 0x270f);
        return;
    }
}
