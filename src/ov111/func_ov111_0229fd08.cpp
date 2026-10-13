/* func_ov111_0229fd08 @ 0x0229fd08, 0x50 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov111_0229fd58(void *self);
extern "C" void func_020a8a70(void *a, void *b, int c, int d);
extern "C" void func_02051694(void *p);

struct UnkStruct_0229fd08 {
    char pad_00[0x10];
    int unk_10;
};

class UnkStruct_0229fd08_3 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual int f3();
};

struct UnkStruct_0229fd08_2 {
    char pad_00[0xa8];
    UnkStruct_0229fd08 *unk_A8;
    char pad_AC[0x3c28];
    UnkStruct_0229fd08_3 obj;
};

extern "C" void func_ov111_0229fd08(UnkStruct_0229fd08_2 *self)
{
    func_ov111_0229fd58(self);
    if (self->unk_A8 != 0) {
        func_020a8a70(&self->obj, (char *) self + 0x3d08, 0, 0);
        UnkStruct_0229fd08 *p = self->unk_A8;
        p->unk_10 = self->obj.f3();
        func_02051694(self->unk_A8);
    }
}
