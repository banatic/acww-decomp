/* func_0201c45c @ 0x0201c45c, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
extern int func_020555c8(void *p, int a, int b);
extern int data_021c9ab8;
}

struct Class {
    virtual void vfunc_00();
    virtual void vfunc_04();
    virtual void vfunc_08();
    virtual void vfunc_0c();
    virtual void vfunc_10();
    virtual void vfunc_14();
    virtual void vfunc_18();
    virtual void vfunc_1c();
    virtual void vfunc_20();
    virtual void vfunc_24();
    virtual void vfunc_28();
    virtual void vfunc_2c();
    virtual void vfunc_30();
    virtual void vfunc_34();
    virtual void vfunc_38();
    virtual void vfunc_3c();
    virtual void vfunc_40();
    virtual void vfunc_44();
    virtual void vfunc_48();
    virtual void vfunc_4c();
    virtual void vfunc_50();
    virtual void vfunc_54();
    virtual void vfunc_58();
    virtual void vfunc_5c();
    virtual void vfunc_60();
    virtual void vfunc_64();
    virtual void vfunc_68();
    virtual void vfunc_6c();
    virtual int someMethod();
    unsigned char pad_04[0xE8];
    int unk_EC;
};

extern "C" int func_0201c45c(Class *self)
{
    int ret = self->someMethod();
    int result = 0;
    if (func_020555c8(&self->unk_EC, ret, data_021c9ab8) != 0) {
        result = 1;
    }
    return result;
}
