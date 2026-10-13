/* func_ov081_02278fd8 @ 0x02278fd8, 0x2a bytes, Thumb, module ov081
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02278fd8 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();

  private:
    char pad0[0xac];

  public:
    int field_b0;

  private:
    char pad1[0x12];

  public:
    char field_c6;

  private:
    char pad2[1];

  public:
    int field_c8;
};

extern "C" void func_ov081_02278fd8(UnkStruct_02278fd8 *obj, int val)
{
    obj->v2();
    obj->field_b0 = val;
    obj->field_c6 = 0;
    obj->field_c8 = -1;
}
