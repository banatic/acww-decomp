/* func_020aa698 @ 0x020aa698, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_020aa698 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};

class UnkStruct_020aa698_2 {
  public:
    char pad_00[0xc];
    UnkStruct_020aa698 sub;
};

extern "C" void func_020ac3f8(UnkStruct_020aa698 *sub);

extern "C" void func_020aa698(UnkStruct_020aa698_2 *self)
{
    self->sub.v3();
    func_020ac3f8(&self->sub);
}
