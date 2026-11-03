/* talk_box_2: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02068cf0 @ 0x02068cf0, 0x22 bytes, Thumb
 * func_02068cdc @ 0x02068cdc, 0x12 bytes, Thumb
 */

extern "C" void func_0208a2a8(void *p, int a, int b);

class SubType {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

typedef struct {
    char pad_00[0x74];
    int unk_74;
    int unk_78;
} MainType;

class UnkStruct_02068cdc {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
};

class UnkStruct_02068cdc_2 {
  public:
    char pad_00[0xc];
    UnkStruct_02068cdc sub;
};

extern "C" void func_02068cf0(MainType *self)
{
    func_0208a2a8((char *) self + 0xc, self->unk_74 + 0x55, self->unk_78 + 0x47);
    SubType *sub = (SubType *) ((char *) self + 0xc);
    sub->f3();
}

extern "C" void func_02068cdc(UnkStruct_02068cdc_2 *self)
{
    self->sub.v2();
}
