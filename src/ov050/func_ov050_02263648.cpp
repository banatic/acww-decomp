/* func_ov050_02263648 @ 0x02263648, 0x24 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02263648 {
  public:
    virtual void vf0();
    virtual void vf1();
    virtual void vf2();
    char pad_04[0xb0];
    int unk_B4;
    char pad_B8[0x14];
    int unk_CC;
};

extern "C" void func_ov050_02263648(UnkStruct_02263648 *obj, int val)
{
    obj->vf2();
    obj->unk_B4 = val;
    obj->unk_CC = -1;
}
