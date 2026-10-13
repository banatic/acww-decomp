/* func_ov111_0229f10c @ 0x0229f10c, 0x58 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
int func_ov111_0229efd8(void *, int);
void func_ov002_0220a0b4(void *, int, int);
int func_ov095_02299b7c(void *);
int func_ov095_02299b38(void *);
}

class UnkStruct_0229f10c {
  public:
    virtual void f0() = 0;
    virtual void f1() = 0;
    virtual void f2() = 0;
    virtual void f3() = 0;
};

extern "C" void func_ov111_0229f10c(unsigned char *self)
{
    if (func_ov111_0229efd8(self, 2) != 0) {
        func_ov002_0220a0b4(self + 0x3d38, self[0xa1] + 0x18, 0x28);
    } else {
        int v1 = func_ov095_02299b7c(self + 0xac);
        int v2 = func_ov095_02299b38(self + 0xac);
        func_ov002_0220a0b4(self + 0x3d38, v1, v2);
    }

    ((UnkStruct_0229f10c *) (self + 0x3d38))->f3();
}
