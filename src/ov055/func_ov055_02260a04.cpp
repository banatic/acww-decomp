/* func_ov055_02260a04 @ 0x02260a04, 0x1a bytes, Thumb, module ov055
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02260a04 {
  public:
    virtual void m0();
    virtual void m1();
    virtual void m2();
    char pad_04[0xac];
    unsigned int val;
};

extern "C" void func_ov055_02260a04(UnkStruct_02260a04 *obj, unsigned int value)
{
    obj->m2();
    obj->val = value;
}
