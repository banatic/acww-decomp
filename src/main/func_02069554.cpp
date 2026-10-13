/* func_02069554 @ 0x02069554, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_020a8750(void *);

struct UnkStruct_02069554 {
    virtual void *f0();
    virtual void *f1();
    virtual void *f2();
    virtual void *f3();
    virtual void *f4();
    virtual void *f5();
    virtual void *f6();
    virtual void *f7();
    virtual void *f8();
    virtual void *f9();
    virtual void *f10();
    virtual void *f11();
    virtual void *f12();
    virtual void *f13();
    virtual void *f14();
    virtual void *f15();
    virtual void *f16();
    virtual void *f17();
    virtual void *f18();
    virtual void *f19();
    virtual void *f20();
    virtual void *f21();
    virtual void *f22();
};

struct UnkStruct_02069554_2 {
    char pad_00[0x14a8];
    UnkStruct_02069554 *obj;
};

struct UnkStruct_02069554_3 {
    char pad_00[0x24];
    UnkStruct_02069554_2 *base;
    char pad_28[0x38 - 0x28];
    char unk_38;
};

extern "C" void *func_02069554(UnkStruct_02069554_3 *self)
{
    UnkStruct_02069554 *obj = self->base->obj;
    func_020a8750(&self->unk_38);
    return obj->f22();
}
