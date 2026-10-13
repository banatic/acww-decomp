/* func_ov140_0229a638 @ 0x0229a638, 0x24 bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229a638 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};

class UnkStruct_0229a638_2 {
  public:
    unsigned char pad_00[0x128c];
    UnkStruct_0229a638 inner;
};

extern "C" void func_ov002_0220a374(void *, int);

extern "C" void func_ov140_0229a638(UnkStruct_0229a638_2 *o)
{
    func_ov002_0220a374(&o->inner, 0);
    o->inner.v3();
}
