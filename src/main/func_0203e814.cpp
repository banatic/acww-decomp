/* func_0203e814 @ 0x0203e814, 0x4a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0203e814_2 {
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
    virtual void f19(int a, int b);
};

typedef struct UnkStruct_0203e814 {
    char pad_00[0xc];
    unsigned int unk_0C;
    char pad_10[0x6];
    unsigned char unk_16;
} UnkStruct_0203e814;

extern "C" UnkStruct_0203e814_2 *func_0203ef90(unsigned int);
extern "C" int func_02095d84(void);
extern "C" int func_0209583c(void);
extern "C" int func_020b5e10(void);
extern "C" void func_020b6098(int, unsigned char);

extern "C" int func_0203e814(UnkStruct_0203e814 *self)
{
    UnkStruct_0203e814_2 *obj;
    int ret;

    obj = func_0203ef90(self->unk_0C);
    if (!func_02095d84()) {
        return 0;
    }
    if (!func_0209583c()) {
        return 0;
    }
    if (obj) {
        obj->f19(2, 4);
    }
    ret = func_020b5e10();
    func_020b6098(ret, self->unk_16);
    return 1;
}
