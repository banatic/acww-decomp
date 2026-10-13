/* func_ov096_0229ddd8 @ 0x0229ddd8, 0x24 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov002_0220a374(unsigned char *, int);

class UnkStruct_0229ddd8 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void Method();
};

extern "C" void func_ov096_0229ddd8(unsigned char *obj)
{
    func_ov002_0220a374(obj + 0x2500, 0);
    ((UnkStruct_0229ddd8 *) (obj + 0x2500))->Method();
}
