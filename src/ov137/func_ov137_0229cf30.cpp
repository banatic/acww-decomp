/* func_ov137_0229cf30 @ 0x0229cf30, 0x18 bytes, Thumb, module ov137
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov137_0229cf0c(struct UnkStruct_0229cf30 *self);

struct UnkStruct_0229cf30_2 {
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

struct UnkStruct_0229cf30 {
    char pad_00[0x94];
    UnkStruct_0229cf30_2 sub;
};

extern "C" void func_ov137_0229cf30(struct UnkStruct_0229cf30 *self)
{
    UnkStruct_0229cf30_2 *p;

    func_ov137_0229cf0c(self);
    p = &self->sub;
    p->f3();
}
