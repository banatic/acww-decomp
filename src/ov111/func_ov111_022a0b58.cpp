/* func_ov111_022a0b58 @ 0x022a0b58, 0x18 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_022a0b58 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

extern "C" void func_ov111_022a0b58(char *p)
{
    ((UnkStruct_022a0b58 *) (p + 0x3d38))->f3();
}
