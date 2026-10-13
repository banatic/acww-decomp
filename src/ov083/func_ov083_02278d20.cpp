/* func_ov083_02278d20 @ 0x02278d20, 0x24 bytes, Thumb, module ov083
 * mwccarm 1.2/base -O4,s
 */

class Something {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    char pad_04[0xac];
    int unk_B0;
    int unk_B4;
};

extern "C" void func_ov083_02278d20(Something *obj, int value)
{
    obj->v2();
    obj->unk_B0 = value;
    obj->unk_B4 = -1;
}
