/* func_ov074_02278fa8 @ 0x02278fa8, 0x1a bytes, Thumb, module ov074
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02278fa8 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void method();
    char pad_04[0xac];
    int unk_B0;
};

extern "C" void func_ov074_02278fa8(UnkStruct_02278fa8 *obj, int value)
{
    obj->method();
    obj->unk_B0 = value;
}
