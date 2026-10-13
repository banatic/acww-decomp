/* func_0208d6dc @ 0x0208d6dc, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_020b45d0(void *sub, int arg1, int arg2, int arg3, int arg4, int arg5);
extern "C" void func_02051694(void *ptr);

class UnkStruct_0208d6dc {
  public:
    virtual int f0();
    virtual int f1();
    virtual int f2();
    virtual int f3();
};

struct Ptr2c {
    char pad_00[0x10];
    int unk_10;
};

struct UnkStruct_0208d6dc_2 {
    char pad_00[0x2c];
    Ptr2c *unk_2C;
    char pad_30[0x49 - 0x30];
    unsigned char unk_49;
    char pad_4A[0x60 - 0x4a];
    unsigned char unk_60;
    char pad_61[0x84 - 0x61];
    UnkStruct_0208d6dc sub;
};

extern "C" void func_0208d6dc(UnkStruct_0208d6dc_2 *self)
{
    if (self->unk_2C == 0) {
        return;
    }
    if (self->unk_49 == 0) {
        return;
    }
    self->unk_49 = 0;
    func_020b45d0(&self->sub, self->unk_60, 2, 0, 0, 1);
    Ptr2c *p = self->unk_2C;
    p->unk_10 = self->sub.f3();
    func_02051694(self->unk_2C);
}
