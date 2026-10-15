/* func_ov071_022799c0 @ 0x022799c0, 0xb8 bytes, Thumb, module ov071
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
extern int func_ov071_02279c08(void *a, void *b);
extern int func_ov071_02279b2c(void *a, int b);
extern int func_ov071_02279b6c(void *a);
extern void func_ov071_02279d04(void *a, int b);
extern void func_0201b044(void *a, void *b);
extern int func_02019c20(void *a, int b, int c, int d, unsigned short e, int f);
extern unsigned short data_020c80f8;
}

class UnkStruct_022799c0 {
  public:
    virtual void f0() = 0;
    virtual void f1() = 0;
    virtual void f2() = 0;
    virtual void f3() = 0;
    virtual void f4() = 0;
    virtual void f5() = 0;
    virtual void f6() = 0;
    virtual void f7() = 0;
    virtual void f8() = 0;
    virtual void f9() = 0;
    virtual void f10() = 0;
    virtual void f11() = 0;
    virtual void f12() = 0;
    virtual void f13() = 0;
    virtual void f14() = 0;
    virtual void f15() = 0;
    virtual void f16() = 0;
    virtual void f17() = 0;
    virtual void f18() = 0;
    virtual void f19() = 0;
    virtual void f20() = 0;
    virtual void f21() = 0;
    virtual void f22() = 0;
    virtual void f23() = 0;
    virtual void f24() = 0;
    virtual void f25() = 0;
    virtual void f26() = 0;
    virtual void f27() = 0;
    virtual void f28() = 0;
    virtual void f29() = 0;
    virtual void f30() = 0;
    virtual void f31() = 0;
    virtual void f32() = 0;
    virtual void f33() = 0;
    virtual void f34() = 0;
    virtual void f35() = 0;
    virtual void f36() = 0;
    virtual void f37() = 0;
    virtual int f38() = 0;

    char pad_04[0x350 - 4];
    char unk_350;
    char pad_351[0x564 - 0x351];
    char unk_564;
    char pad_565[0x729 - 0x565];
    unsigned char unk_729;
    char pad_72A[0x72c - 0x72a];
    unsigned int unk_72C;
    unsigned int unk_730;
    void *unk_734;
};

extern "C" void func_ov071_022799c0(UnkStruct_022799c0 *self)
{
    char *p350 = (char *) self + 0x350;

    if (func_ov071_02279c08(self, (char *) self + 0x72c) && self->unk_734) {
        if (func_ov071_02279b2c(self, 0x3000)) {
            int ret = self->f38();

            func_02019c20((char *) self + 0x564, 1, ret, 0, data_020c80f8, 0);
            self->unk_729 = 2;
            self->unk_72C = 0xf0;
        } else {
            if (func_ov071_02279b6c(self)) {
                func_0201b044(p350, (char *) self->unk_734 + 0x5c);
            } else {
                self->unk_730 = 0xc8;
                func_ov071_02279d04(self, 3);
            }
        }
    } else {
        self->unk_730 = 0xc8;
        func_ov071_02279d04(self, 3);
    }
}
