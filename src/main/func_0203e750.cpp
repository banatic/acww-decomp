/* func_0203e750 @ 0x0203e750, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0203e750 {
    unsigned char pad_00[0xc];
    void *unk_0C;
    unsigned char pad_10[0x6];
    unsigned char unk_16;
};

class CObj {
  public:
    virtual void f00();
    virtual void f01();
    virtual void f02();
    virtual void f03();
    virtual void f04();
    virtual void f05();
    virtual void f06();
    virtual void f07();
    virtual void f08();
    virtual void f09();
    virtual void f10();
    virtual void f11();
    virtual void f12();
    virtual void f13();
    virtual void f14();
    virtual void f15();
    virtual void f16();
    virtual void f17();
    virtual void f18();
    virtual void method(int, int);
};

extern unsigned char data_020dab94;
extern "C" CObj *func_0203ef90(void *);
extern "C" int func_0203f400(void *);
extern "C" void func_0203f394(void *);

extern "C" int func_0203e750(UnkStruct_0203e750 *self)
{
    CObj *obj;
    unsigned char g;

    obj = func_0203ef90(self->unk_0C);
    if (obj == 0) {
        return 0;
    }

    if (self->unk_16 == 7) {
        switch (func_0203f400(self->unk_0C)) {
            case 2:
                self->unk_16 = 2;
                break;
            case 1:
                self->unk_16 = 1;
                func_0203f394(self->unk_0C);
                break;
        }
    }

    if (self->unk_16 == 1) {
        g = data_020dab94;
        switch (g) {
            case 1:
                self->unk_16 = 2;
                break;
            case 2:
                func_0203f394(self->unk_0C);
                break;
        }
    }

    if (self->unk_16 == 2) {
        obj->method(6, 4);
        self->unk_16 = 5;
        return 1;
    }
    return 0;
}
