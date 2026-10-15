/* func_02069af0 @ 0x02069af0, 0x90 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02069af0 {
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
    virtual void f13(int a, int b);
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
    virtual void f25();
    virtual UnkStruct_02069af0 *f26();
};

struct UnkStruct_02069af0_2 {
    char pad_00[0x14a8];
    UnkStruct_02069af0 *a;
};

struct UnkStruct_02069af0_3 {
    char pad_00[0x24];
    UnkStruct_02069af0_2 *c;
};

extern "C" int func_020a86e4(void *, unsigned char *, unsigned char *, unsigned char *);
extern "C" int func_020984e8(void);
extern "C" int func_02099870(int);
extern "C" int func_020807a8(UnkStruct_02069af0 *, int);
extern "C" int func_02081d20(void *object);
extern "C" void func_0206bb9c(void *object, int code, const void *message);
extern "C" void func_0206b964(UnkStruct_02069af0_3 *, unsigned char *);
extern "C" void *data_020df140;

extern "C" void func_02069af0(UnkStruct_02069af0_3 *self)
{
    int forwarded_value;

    UnkStruct_02069af0 *a = self->c->a;
    a->f13(2, 2);
    unsigned char p, b, arr[2];
    func_020a86e4((char *) self + 0x38, &p, &arr[0], &arr[1]);
    int idx = 0;
    a = a->f26();
    int profile = func_020984e8();
    if (a != 0) {
        int tmp = func_02099870(profile);
        if ((forwarded_value = (int) func_020807a8(a, tmp)) != 0) {
            if (func_02081d20((void *) forwarded_value) < p) {
                idx = 1;
            }
        }
    } else {
        func_0206bb9c(self, 0xe9a, &data_020df140);
    }
    b = arr[idx];
    func_0206b964(self, &b);
}
