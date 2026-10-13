/* func_ov049_02262094 @ 0x02262094, 0x1a bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02262094 {
  public:
    virtual void f0() = 0;
    virtual void f1() = 0;
    virtual void f2() = 0;
    char pad_04[0xac];
    int value;
};

extern "C" void func_ov049_02262094(UnkStruct_02262094 *obj, int arg)
{
    obj->f2();
    obj->value = arg;
}
