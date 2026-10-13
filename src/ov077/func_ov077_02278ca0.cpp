/* func_ov077_02278ca0 @ 0x02278ca0, 0x1a bytes, Thumb, module ov077
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02278ca0 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    char pad_04[0xb4];
    int unk_B8;
};

extern "C" void func_ov077_02278ca0(UnkStruct_02278ca0 *obj, int value)
{
    obj->f2();
    obj->unk_B8 = value;
}
