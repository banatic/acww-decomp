/* func_ov004_0220c7e0 @ 0x0220c7e0, 0x78 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0220c7e0 {
  public:
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
    virtual void vfunc_70();
    virtual void vfunc_74();
    virtual void vfunc_78();
    virtual void vfunc_7c();
    virtual void vfunc_80();
    virtual void vfunc_84();
    virtual void vfunc_88();
    virtual void vfunc_8c();
    virtual void vfunc_90();
    virtual void call_target(int);

    char pad_04[0x58];
    char unk_5C;
    char pad_5D[0x10f];
    short unk_16C;
    char pad_16E[0x2];
    char unk_170;
    char pad_171[0x1b];
    char unk_18C;
    char pad_18D[0xc3];
    char unk_250;
};

extern "C" void func_020eaca0(void *, void *, void *);
extern "C" void func_ov004_0220d594_unk(void *, void *);
extern "C" void func_ov004_0220ee90_unk(void *, void *, int);
extern "C" int func_ov004_0223b22c_unk(void);
extern "C" int func_ov004_0223b080_unk(int, void *, void *, short);
extern "C" void func_ov004_0220e674_unk(void *, int);

extern "C" int func_ov004_0220c7e0(UnkStruct_0220c7e0 *self)
{
    char buf[16];
    func_020eaca0(buf, &self->unk_170, &self->unk_5C);
    func_ov004_0220d594_unk(&self->unk_18C, self);
    func_ov004_0220ee90_unk(self, buf, 0);

    int cond = func_ov004_0223b22c_unk();
    if (cond != 0 && func_ov004_0223b080_unk(cond, &self->unk_250, &self->unk_5C, self->unk_16C) != 0) {
        self->call_target(1);
        func_ov004_0220e674_unk(self, 0);
        return 1;
    } else {
        return 0;
    }
}
