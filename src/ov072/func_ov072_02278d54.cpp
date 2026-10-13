/* func_ov072_02278d54 @ 0x02278d54, 0x22 bytes, Thumb, module ov072
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02278d54 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    char pad_04[0xB8 - 4];
    int unk_B8;
    int unk_BC;
};

extern "C" void func_ov072_02278d54(UnkStruct_02278d54 *obj, int value)
{
    obj->f2();
    obj->unk_BC = value;
    obj->unk_B8 = 0;
}
