/* func_ov104_0229d198 @ 0x0229d198, 0x20 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229d198 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};

extern "C" void func_ov002_0220a0ec(UnkStruct_0229d198 *p);

extern "C" void func_ov104_0229d198(char *param)
{
    func_ov002_0220a0ec((UnkStruct_0229d198 *) (param + 0x24a0));
    ((UnkStruct_0229d198 *) (param + 0x24a0))->v3();
}
