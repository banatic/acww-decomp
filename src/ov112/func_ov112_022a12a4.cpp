/* func_ov112_022a12a4 @ 0x022a12a4, 0x38 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov112_0229fbf4(void *self);
extern "C" void func_ov002_0220af74(void *self);

class UnkStruct_022a12a4 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

extern "C" void func_ov112_022a12a4(void *self)
{
    func_ov112_0229fbf4(self);
    ((UnkStruct_022a12a4 *) ((char *) self + 0x4234))->f3();
    ((UnkStruct_022a12a4 *) ((char *) self + 0x4448))->f3();
    func_ov002_0220af74((char *) self + 0x427c);
}
