/* func_020abe48 @ 0x020abe48, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_020abe48 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
};

struct Main {
    char pad_00[0x20];
    UnkStruct_020abe48 sub1;
    char pad_24[0x48];
    UnkStruct_020abe48 sub2;
    char pad_70[0x74];
    UnkStruct_020abe48 sub3;
    char pad_E8[0x5d];
    unsigned char flag;
};

extern "C" void func_020abe48(Main *self)
{
    if (self->flag) {
        self->sub1.f2();
    }
    self->sub2.f2();
    self->sub3.f2();
}
