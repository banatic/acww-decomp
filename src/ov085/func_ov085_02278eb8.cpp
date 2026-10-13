/* func_ov085_02278eb8 @ 0x02278eb8, 0x24 bytes, Thumb, module ov085
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02278eb8 {
  public:
    virtual void vfunc0();
    virtual void vfunc1();
    virtual void vfunc2();
    char pad_04[0xac];
    int unk_B0;
    int unk_B4;
};

extern "C" void func_ov085_02278eb8(UnkStruct_02278eb8 *obj, int arg)
{
    obj->vfunc2();
    obj->unk_B0 = arg;
    obj->unk_B4 = -1;
}
