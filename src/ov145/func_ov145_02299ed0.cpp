/* func_ov145_02299ed0 @ 0x02299ed0, 0x1c bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov002_0220a374(void *, int);

class ObjType {
  public:
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void method();
};

class UnkStruct_02299ed0 {
  public:
    unsigned char pad_00[0xc8];
    ObjType obj;
};

extern "C" void func_ov145_02299ed0(UnkStruct_02299ed0 *self)
{
    func_ov002_0220a374(&self->obj, 0);
    self->obj.method();
}
