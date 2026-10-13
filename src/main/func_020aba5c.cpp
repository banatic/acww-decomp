/* func_020aba5c @ 0x020aba5c, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_020aba5c {
  public:
    virtual void vf0();
    virtual void vf1();
    virtual void vf2();
    virtual void vf3();
    virtual void method(int a, int b);
};

class Main {
  public:
    char pad_00[0x1a];
    short unk_1A;
    char pad_1C[4];
    UnkStruct_020aba5c sub;
    char pad2[0x13c - 0x20 - sizeof(UnkStruct_020aba5c)];
    int unk_13C;
};

extern "C" void func_020abc6c(Main *self, int);

extern "C" void func_020aba5c(Main *self)
{
    self->unk_13C = 7;
    self->sub.method(0, -self->unk_1A);
    func_020abc6c(self, 8);
}
