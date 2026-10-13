/* func_02068cf0 @ 0x02068cf0, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
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

extern "C" void func_02068cf0(MainType *self)
{
    func_0208a2a8((char *) self + 0xc, self->unk_74 + 0x55, self->unk_78 + 0x47);
    SubType *sub = (SubType *) ((char *) self + 0xc);
    sub->f3();
}
