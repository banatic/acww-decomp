/* func_020ac25c @ 0x020ac25c, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_020ac25c {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
};

struct UnkStruct_020ac25c_2 {
    char pad_00[0x20];
    UnkStruct_020ac25c a;
    char pad_24[0x50];
    unsigned char flag;
};

extern "C" void func_020ac25c(UnkStruct_020ac25c_2 *self)
{
    if (self->flag) {
        self->a.f2();
    }
}
