/* func_ov118_0229a854 @ 0x0229a854, 0x20 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov002_0220a0ec(void *);

class UnkStruct_0229a854 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

extern "C" void func_ov118_0229a854(void *arg)
{
    func_ov002_0220a0ec((char *) arg + 0x6c0);
    ((UnkStruct_0229a854 *) ((char *) arg + 0x6c0))->f3();
}
