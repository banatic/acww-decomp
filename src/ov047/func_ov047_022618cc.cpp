/* func_ov047_022618cc @ 0x022618cc, 0x3c bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_022618cc {
  public:
    virtual void m0();
    virtual void m1();
    virtual void m2();
    char pad_04[0xAC];
    int unk_B0;
    int unk_B4;
    char pad_B8[0x10];
    int unk_C8;
    char unk_CC;
    char pad_CD[1];
    unsigned short unk_CE;
};

extern "C" void func_ov047_022618cc(UnkStruct_022618cc *obj, int value)
{
    obj->m2();
    obj->unk_B4 = value;
    obj->unk_B0 = 0;
    obj->unk_C8 = -1;
    obj->unk_CC = 0;
    obj->unk_CE = 0xfff1;
}
