/* func_ov048_02262680 @ 0x02262680, 0x22 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02262680 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    char pad_04[0xac];
    int unk_B0;
    int pad_B4;
    int unk_B8;
};

extern "C" void func_ov048_02262680(UnkStruct_02262680 *obj, int val)
{
    obj->f2();
    obj->unk_B8 = val;
    obj->unk_B0 = 11;
}
