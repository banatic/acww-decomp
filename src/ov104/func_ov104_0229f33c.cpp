/* func_ov104_0229f33c @ 0x0229f33c, 0xe8 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
int func_ov104_0229c364(char *self, int flag);
int func_0206fe54(int value);
void func_ov104_0229d580(char *self);
void func_ov002_02209eb8(char *p);
void func_ov002_0220ad18(char *p, unsigned int v);
void func_ov094_0229a850(char *p, int a, int b);
void func_ov094_0229b738(char *p, int a, int b);
void func_ov094_02299d84(char *p, int a);
void func_ov094_0229b690(char *p, unsigned int v, int mask);
int func_ov002_02207f60(char *self);
void func_0208f210(char *p, int a, int b);
}

class UnkStruct_0229f33c {
  public:
    virtual int vf0();
    virtual int vf1();
    virtual int vf2();
};

extern "C" int func_ov104_0229f33c(char *self)
{
    if (func_ov104_0229c364(self, 1) == 0) {
        return 1;
    }
    if (func_0206fe54(((UnkStruct_0229f33c *) (self + 0x23b8))->vf2()) != 0) {
        func_ov002_02209eb8(self + 0x24a0);
    }
    func_ov104_0229d580(self);
    if (func_ov104_0229c364(self, 2) != 0) {
        func_ov002_0220ad18(self + 0x41b4, *(unsigned int *) (self + 0x98));
        unsigned int r4 = *(unsigned int *) (self + 0x98) - 0x10;
        func_ov094_0229a850(self + 0x2f8, 0, r4);
        func_ov094_0229b738(self + 0xd58, 0, r4);
        func_ov094_02299d84(self + 0xd80, r4);
    }
    if (func_ov104_0229c364(self, 0x200) != 0) {
        func_ov094_0229b690(self + 0xd58, *(unsigned int *) (self + 0x9c), -16);
    }
    if (func_ov104_0229c364(self, 0x80) != 0) {
        int v = func_ov002_02207f60(self);
        func_0208f210(self + 0x2d3c, 0, v);
        ((UnkStruct_0229f33c *) (self + 0x2d3c))->vf2();
    }
    return 1;
}
