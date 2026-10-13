/* func_02069574 @ 0x02069574, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_020a8750(void *arg);

class VtblClass {
  public:
    virtual void vf0();
    virtual void vf1();
    virtual void vf2();
    virtual void vf3();
    virtual void vf4();
    virtual void vf5();
    virtual void vf6();
    virtual void vf7();
    virtual void vf8();
    virtual void vf9();
    virtual void vf10();
    virtual void vf11();
    virtual void vf12();
    virtual void vf13();
    virtual void vf14();
    virtual void vf15();
    virtual void vf16();
    virtual void vf17();
    virtual void vf18();
    virtual void vf19();
    virtual void vf20();
    virtual void vf21();
};

struct DataBlock {
    char pad_00[0x14a8];
    VtblClass *obj;
};

struct UnkStruct_02069574 {
    char pad_00[0x24];
    DataBlock *data;
    char pad_28[0x38 - 0x28];
    char sub;
};

extern "C" void func_02069574(UnkStruct_02069574 *self)
{
    DataBlock *dp = self->data;
    VtblClass *v = dp->obj;
    func_020a8750(&self->sub);
    v->vf21();
}
