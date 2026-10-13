/* func_020abaa8 @ 0x020abaa8, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_020abaa8 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
    virtual void f4(int a, int b);
};

struct UnkStruct_020abaa8_2 {
    char pad_00[0x1a];
    short unk_1A;
    char pad_1C[4];
    UnkStruct_020abaa8 inner;
    char pad_24[0x48];
    char unk_6C[0x78];
    char unk_E4[0x58];
    int unk_13C;
};

extern "C" void func_0208e508(UnkStruct_020abaa8 *p, int v);
extern "C" void func_020aca48(void *p);
extern "C" void func_0208f0c4(void *p, int v);

extern "C" void func_020abaa8(UnkStruct_020abaa8_2 *self)
{
    self->unk_13C = 6;
    self->inner.f4(0, -self->unk_1A);
    func_0208e508(&self->inner, 7);
    func_020aca48(&self->unk_E4);
    func_0208f0c4(&self->unk_6C, 1);
}
