/* func_ov002_022080a8 @ 0x022080a8, 0xac bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_022080a8 {
  public:
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void m5();
    char pad_04[0x4c];
    char sub[0x3f];
    unsigned char idx;
};

typedef void (UnkStruct_022080a8::*ClsPMF)();

extern "C" void func_ov002_02208938(void *);

extern "C" int func_ov002_022080a8(UnkStruct_022080a8 *self)
{
    static ClsPMF tbl[6] = {&UnkStruct_022080a8::m0, &UnkStruct_022080a8::m1, &UnkStruct_022080a8::m2,
                            &UnkStruct_022080a8::m3, &UnkStruct_022080a8::m4, &UnkStruct_022080a8::m5};
    func_ov002_02208938(self->sub);
    (self->*tbl[self->idx])();
    return 1;
}
