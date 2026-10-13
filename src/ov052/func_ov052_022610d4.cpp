/* func_ov052_022610d4 @ 0x022610d4, 0x2a bytes, Thumb, module ov052
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_022610d4 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    char pad_04[0xB0];
    int unk_B4;
    char pad_B8[4];
    int unk_BC;
    char unk_C0;
};

extern "C" void func_ov052_022610d4(UnkStruct_022610d4 *obj, int value)
{
    obj->f2();
    obj->unk_B4 = value;
    obj->unk_BC = -1;
    obj->unk_C0 = 0;
}
