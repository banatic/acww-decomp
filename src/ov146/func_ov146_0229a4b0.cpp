/* func_ov146_0229a4b0 @ 0x0229a4b0, 0x20 bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov002_0220a0ec(void *);

class UnkStruct_0229a4b0 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual int f3();
};

extern "C" int func_ov146_0229a4b0(void *p)
{
    char *base = (char *) p;
    func_ov002_0220a0ec(base + 0x15cc);
    return ((UnkStruct_0229a4b0 *) (base + 0x15cc))->f3();
}
