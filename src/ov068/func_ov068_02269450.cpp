/* func_ov068_02269450 @ 0x02269450, 0xf8 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02269450 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
    virtual void f4();
    virtual void f5();
    virtual void f6();
    virtual void f7();
    virtual void f8();
    virtual void f9();
    virtual void f10();
    virtual void f11();
    virtual void f12();
    virtual void f13();
    virtual void f14();
    virtual void f15();
    virtual void f16();
    virtual void f17();
    virtual void f18();
    virtual void f19();
    virtual void f20();
    virtual void f21();
    virtual void f22();
    virtual void f23();
    virtual void f24();
    virtual int v25();
};

struct UnkStruct_02269450_2 {
    char pad_00[0x1c];
    unsigned char unk_1C;
    char pad_1D[0x20 - 0x1d];
    int f20;
    char pad_24[0xe4 - 0x24];
    int unk_E4;
    char pad_E8[0xf4 - 0xe8];
    int unk_F4;
};

extern "C" int func_ov068_022697cc(UnkStruct_02269450_2 *, UnkStruct_02269450 *, int);
extern "C" int func_0201c314(UnkStruct_02269450 *, int);
extern "C" void func_02019d0c(void *, int, int, int, int, int, int, int, int, int, int);
extern "C" void func_ov068_0226cce8(UnkStruct_02269450_2 *, UnkStruct_02269450 *, int);
extern "C" int func_ov068_0226c0e0(UnkStruct_02269450_2 *, UnkStruct_02269450 *);
extern "C" void func_0207d148(int);
extern "C" void func_0207d0f0(int, int);

extern unsigned short data_020c80f8;      // 0x020c80f8
extern const short data_ov068_02276724[]; // 0x02276724

extern "C" void func_ov068_02269450(UnkStruct_02269450_2 *self, UnkStruct_02269450 *obj)
{
    if (self->unk_E4 == 0) {
        goto tail;
    }
    if (func_ov068_022697cc(self, obj, 0x5000) == 0) {
        func_02019d0c((char *) obj + 0x564, 3, 1, 0, 0, 0, func_0201c314(obj, self->unk_E4), 0, 0, data_020c80f8, 0);
        self->unk_1C = 3;
        return;
    }
    if (*(unsigned short *) ((char *) obj + 0xa06) >= data_ov068_02276724[0]) {
        func_ov068_0226cce8(self, obj, 0x15);
        return;
    }
    if (func_ov068_0226c0e0(self, obj) != 0) {
        func_ov068_0226cce8(self, obj, 0x13);
        return;
    }
    if (self->f20 != 0) {
        return;
    }
    func_ov068_0226cce8(self, obj, 0);
    self->unk_F4 = 0x4b0;
    if (obj->v25() != 0) {
        func_0207d148(obj->v25());
    }
    return;
tail:
    func_ov068_0226cce8(self, obj, 0);
    self->unk_F4 = 0x4b0;
    if (obj->v25() != 0) {
        func_0207d0f0(obj->v25(), -1);
    }
}
