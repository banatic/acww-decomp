/* func_ov068_022752e4 @ 0x022752e4, 0x70 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022752e4 {
    int unk_00;
    int unk_04;
};

class UnkStruct_022752e4_2 {
  public:
    virtual void m00();
    virtual void m01();
    virtual void m02();
    virtual void m03();
    virtual void m04();
    virtual void m05();
    virtual void m06();
    virtual void m07();
    virtual void m08();
    virtual void m09();
    virtual void m10();
    virtual void m11();
    virtual void m12();
    virtual void m13();
    virtual void m14();
    virtual void m15();
    virtual void m16();
    virtual void m17();
    virtual void m18();
    virtual void m19();
    virtual void m20();
    virtual void m21();
    virtual void m22();
    virtual void m23();
    virtual void m24();
    virtual int m25();

    char pad_04[0x8d8];
    UnkStruct_022752e4 *unk_8DC;
    char pad_8E0[0x178];
    unsigned char unk_A58;
};

extern "C" void func_020b23c8(void);
extern "C" int func_0207f270(int);
extern "C" void func_02079500(void);
extern "C" void func_ov068_022763c8(UnkStruct_022752e4_2 *self);
extern "C" int func_020b5e10(void);
extern "C" void func_020b5ee4(int, int);
extern "C" void func_020b6098(int, int);

extern "C" void func_ov068_022752e4(UnkStruct_022752e4_2 *self)
{
    if (self->unk_8DC && self->unk_8DC->unk_04 == 0) {
        func_020b23c8();
        if (self->m25()) {
            func_0207f270(self->m25());
            func_02079500();
        }
        func_ov068_022763c8(self);
        if (self->unk_A58) {
            func_020b5ee4(func_020b5e10(), 0);
            func_020b6098(func_020b5e10(), 6);
        } else {
            func_020b6098(func_020b5e10(), 0);
        }
    }
}
