/* func_ov142_0229af00 @ 0x0229af00, 0x1a bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov002_0220a0ec(void *);

class UnkStruct_0229af00 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void method();
};

extern "C" void func_ov142_0229af00(char *self)
{
    func_ov002_0220a0ec(self + 0xe8);
    ((UnkStruct_0229af00 *) (self + 0xe8))->method();
}
