/* func_ov070_02279654 @ 0x02279654, 0x38 bytes, Thumb, module ov070
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02279654 {
  public:
    virtual void vf0();
    virtual void vf1();
    virtual void vf2();
    unsigned char pad_04[0xac];
    int unk_B0;
    int unk_B4;
    unsigned char pad_B8[0xc];
    unsigned short arr[3];
};

extern "C" void func_ov070_02279654(UnkStruct_02279654 *obj, int val)
{
    int i;
    obj->vf2();
    obj->unk_B4 = val;
    for (i = 0; i < 3; i++) {
        obj->arr[i] = 0xfff1;
    }
    obj->unk_B0 = 0;
}
