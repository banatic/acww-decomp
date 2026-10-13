/* func_ov073_02278d60 @ 0x02278d60, 0x34 bytes, Thumb, module ov073
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02278d60 {
  public:
    virtual void f0() = 0;
    virtual void f1() = 0;
    virtual void f2() = 0;
    char pad_04[0xAC];
    int unk_B0;
    int unk_B4;
    char pad_B8[0x8];
    int unk_C0;
    int unk_C4;
    char unk_C8;
};

extern "C" void func_ov073_02278d60(UnkStruct_02278d60 *obj, int arg)
{
    obj->f2();
    obj->unk_B4 = arg;
    obj->unk_B0 = 0;
    obj->unk_C0 = 0;
    obj->unk_C4 = 0;
    obj->unk_C8 = 0;
}
