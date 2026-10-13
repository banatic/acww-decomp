/* func_020b8b74 @ 0x020b8b74, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_020b8b74 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
};

class UnkStruct_020b8b74_2 {
  public:
    char pad_00[8];
    UnkStruct_020b8b74 sub;
};

extern "C" void func_020b8b74(UnkStruct_020b8b74_2 *self)
{
    self->sub.v2();
}
