/* func_ov078_02278f74 @ 0x02278f74, 0x3c bytes, Thumb, module ov078
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02278f74 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    unsigned char pad_04[0xac];
    int unk_B0;
    int unk_B4;
    unsigned short unk_B8[2];
};

extern "C" void func_ov078_02278f74(UnkStruct_02278f74 *obj, int arg)
{
    int i;
    obj->v2();
    obj->unk_B0 = arg;
    obj->unk_B4 = -1;
    for (i = 0; i < 2; i++) {
        obj->unk_B8[i] = 0xfff1;
    }
}
