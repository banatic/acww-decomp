/* func_02051ad8 @ 0x02051ad8, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" void MI_CpuFill8(int a, int b, int c);

class UnkStruct_02051ad8 {
  public:
    virtual int m0();
    virtual int m1();
    virtual int m2();
    virtual int m3();
};

extern "C" void func_02051ad8(UnkStruct_02051ad8 *obj)
{
    int a = obj->m2();
    int b = obj->m3();
    MI_CpuFill8(b, 0, a);
}
