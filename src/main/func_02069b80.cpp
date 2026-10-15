/* func_02069b80 @ 0x02069b80, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02069b80 {
  public:
    virtual void m0() = 0;
    virtual void m1() = 0;
    virtual void m2() = 0;
    virtual void m3() = 0;
    virtual void m4() = 0;
    virtual void m5() = 0;
    virtual void m6() = 0;
    virtual void m7() = 0;
    virtual void m8() = 0;
    virtual void m9() = 0;
    virtual void m10() = 0;
    virtual void m11() = 0;
    virtual void m12() = 0;
    virtual void m13(int a, int b) = 0;
};

struct InnerStruct {
    char pad_00[0x14a8];
    UnkStruct_02069b80 *vtobj;
};

struct UnkStruct_02069b80_2 {
    char pad_00[0x24];
    InnerStruct *inner;
    char pad_28[0x10];
    char someField;
};

extern "C" int func_020a86e4(void *, unsigned char *, unsigned char *, unsigned char *);
extern "C" int func_020644cc(int arg);
extern "C" void func_0206b964(UnkStruct_02069b80_2 *, unsigned char *);

extern "C" void func_02069b80(UnkStruct_02069b80_2 *self)
{
    unsigned char data[4];
    self->inner->vtobj->m13(1, 3);
    func_020a86e4(&self->someField, &data[1], &data[2], &data[3]);
    data[0] = (&data[1])[func_020644cc(3)];
    func_0206b964(self, data);
}
