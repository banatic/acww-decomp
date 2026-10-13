/* func_ov110_0229cbe0 @ 0x0229cbe0, 0x24 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov002_0220a374(void *p, int v);

class UnkStruct_0229cbe0 {
  public:
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
};

extern "C" void func_ov110_0229cbe0(char *base)
{
    func_ov002_0220a374(base + 0x22e0, 0);
    ((UnkStruct_0229cbe0 *) (base + 0x22e0))->m3();
}
