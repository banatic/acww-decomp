/* func_ov133_0229b938 @ 0x0229b938, 0x20 bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov002_0220a0ec(void *);

class UnkStruct_0229b938 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

extern "C" void func_ov133_0229b938(void *arg)
{
    func_ov002_0220a0ec((char *) arg + 0x11c);
    ((UnkStruct_0229b938 *) ((char *) arg + 0x11c))->f3();
}
