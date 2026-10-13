/* func_02068cdc @ 0x02068cdc, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02068cdc {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
};

class UnkStruct_02068cdc_2 {
  public:
    char pad_00[0xc];
    UnkStruct_02068cdc sub;
};

extern "C" void func_02068cdc(UnkStruct_02068cdc_2 *self)
{
    self->sub.v2();
}
