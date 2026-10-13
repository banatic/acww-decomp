/* func_ov068_0226e598 @ 0x0226e598, 0x1a bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0226e598 {
  public:
    virtual void m0();
    virtual void m1();
    virtual void m2();
    char pad_04[180]; // 0xb4
    int unk_B8;
};

extern "C" void func_ov068_0226e598(UnkStruct_0226e598 *obj, int value)
{
    obj->m2();
    obj->unk_B8 = value;
}
