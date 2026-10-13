/* func_ov140_0229a590 @ 0x0229a590, 0x20 bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov002_0220a0ec(void *addr);

class UnkStruct_0229a590 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

extern "C" void func_ov140_0229a590(int p)
{
    func_ov002_0220a0ec((void *) (p + 0x128c));
    ((UnkStruct_0229a590 *) (p + 0x128c))->f3();
}
