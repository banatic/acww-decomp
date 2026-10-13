/* func_ov122_0229f1b4 @ 0x0229f1b4, 0x68 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229f1b4 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

struct UnkStruct_0229f1b4_2 {
    char pad_00[0x9c];
    unsigned int unk_9C;
    unsigned int unk_A0;
    char pad_A4[0x0f];
    unsigned char unk_B3;
    char pad_B4[0x0c];
    int unk_C0;
    char pad_C4[0x3f94];
    UnkStruct_0229f1b4 inner;
};

extern "C" int func_ov122_0229efe8(UnkStruct_0229f1b4_2 *self, int n);
extern "C" void func_ov002_0220a0b4(UnkStruct_0229f1b4 *a, int b, int c);
extern "C" int func_ov095_02299b7c(void *ptr);
extern "C" int func_ov095_02299b38(void *ptr);

extern "C" void func_ov122_0229f1b4(UnkStruct_0229f1b4_2 *self)
{
    if (func_ov122_0229efe8(self, 0x100)) {
        func_ov002_0220a0b4(&self->inner, self->unk_9C, self->unk_A0 - self->unk_B3);
    } else {
        int r1 = func_ov095_02299b7c(&self->unk_C0);
        int r2 = func_ov095_02299b38(&self->unk_C0);
        func_ov002_0220a0b4(&self->inner, r1, r2);
    }
    self->inner.f3();
}
