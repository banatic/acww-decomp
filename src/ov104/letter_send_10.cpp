/* letter_send_10: 2 functions, module ov104
 * mwccarm 1.2/base -O4,s
 * func_ov104_0229f33c @ 0x0229f33c, 0xe8 bytes, Thumb
 * func_ov104_0229f248 @ 0x0229f248, 0xf4 bytes, Thumb
 */

extern "C" {
int func_ov104_0229c364(char *self, int flag);
int func_0206fe54(void);
void func_ov104_0229d580(char *self);
void func_ov002_02209eb8(char *p);
void func_ov002_0220ad18(char *p, unsigned int v);
void func_ov094_0229a850(char *p, int a, int b);
void func_ov094_0229b738(char *p, int a, int b);
void func_ov094_02299d84(void *receiver, int value);
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

class UnkStruct_0229f248 {
  public:
    unsigned char data[0x8c];
    unsigned char idx;
};

typedef void (UnkStruct_0229f248::*PMF)();

extern PMF data_ov104_0229f668;
extern PMF data_ov104_0229f6c0;
extern PMF data_ov104_0229f6b8;
extern PMF data_ov104_0229f6b0;
extern PMF data_ov104_0229f6a8;
extern PMF data_ov104_0229f6a0;
extern PMF data_ov104_0229f698;
extern PMF data_ov104_0229f690;
extern PMF data_ov104_0229f688;
extern PMF data_ov104_0229f680;
extern PMF data_ov104_0229f678;
extern "C" void func_ov104_0229e9f8(UnkStruct_0229f248 *self);
extern "C" void func_ov104_0229e9c0(UnkStruct_0229f248 *self);

extern "C" int func_ov104_0229f33c(char *self)
{
    if (func_ov104_0229c364(self, 1) == 0) {
        return 1;
    }
    if (((void) (((UnkStruct_0229f33c *) (self + 0x23b8))->vf2()), func_0206fe54()) != 0) {
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

extern "C" int func_ov104_0229f248(UnkStruct_0229f248 *self)
{
    static PMF table[11] = {data_ov104_0229f668, data_ov104_0229f6c0, data_ov104_0229f6b8, data_ov104_0229f6b0,
                            data_ov104_0229f6a8, data_ov104_0229f6a0, data_ov104_0229f698, data_ov104_0229f690,
                            data_ov104_0229f688, data_ov104_0229f680, data_ov104_0229f678};
    func_ov104_0229e9f8(self);
    (self->*table[self->idx])();
    func_ov104_0229e9c0(self);
    return 1;
}
