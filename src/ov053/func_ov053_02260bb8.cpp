/* func_ov053_02260bb8 @ 0x02260bb8, 0x22 bytes, Thumb, module ov053
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02260bb8 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    char pad_04[0xac];
    int unk_B0;
    int unk_B4;
};

extern "C" void func_ov053_02260bb8(UnkStruct_02260bb8 *obj, int arg)
{
    obj->f2();
    obj->unk_B4 = arg;
    obj->unk_B0 = 0xe;
}
