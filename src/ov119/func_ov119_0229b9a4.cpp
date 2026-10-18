/* func_ov119_0229b9a4 @ 0x0229b9a4, 0x24 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229b9a4 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};

class Main {
  public:
    char pad_00[0xda8];
    UnkStruct_0229b9a4 sub;
};

extern "C" void func_ov002_0220a374(void *, int);

extern "C" void func_ov119_0229b9a4(Main *self)
{
    func_ov002_0220a374(&self->sub, 0);
    self->sub.v3();
}
