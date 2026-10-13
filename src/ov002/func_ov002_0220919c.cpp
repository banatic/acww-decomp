/* func_ov002_0220919c @ 0x0220919c, 0x30 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0220919c {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
};

extern "C" int func_ov002_02208a14(void *self, int bit);

extern "C" void func_ov002_0220919c(char *self)
{
    if (func_ov002_02208a14(self, 1)) {
        ((UnkStruct_0220919c *) (self + 0x26c))->f2();
        ((UnkStruct_0220919c *) (self + 0x2e4))->f2();
    }
}
