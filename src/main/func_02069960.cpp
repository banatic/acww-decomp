/* func_02069960 @ 0x02069960, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02069960 {
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
    virtual void target(int a, int b);
};

struct UnkStruct_02069960_2 {
    char pad_00[0x14a8];
    UnkStruct_02069960 *obj;
};

struct UnkStruct_02069960_3 {
    char pad_00[0x24];
    UnkStruct_02069960_2 *inner;
    char pad_28[0x10];
    unsigned char unk_38;
};

extern "C" unsigned int func_020a86e4(void *a, unsigned char *b, unsigned char *c, unsigned char *d);
extern "C" unsigned int func_0203cc04(unsigned int x);
extern "C" void func_0206b964(void *self, unsigned char *arr);

extern "C" void func_02069960(UnkStruct_02069960_3 *self)
{
    unsigned char arr[4];
    int idx;
    UnkStruct_02069960 *obj;
    unsigned int x;

    obj = self->inner->obj;
    obj->target(6, 3);
    x = func_0203cc04(func_020a86e4((void *) &self->unk_38, &arr[1], &arr[2], &arr[3]));
    if (x == 0x38) {
        idx = 2;
    } else if (x >= 0x21) {
        idx = 1;
    } else {
        idx = 0;
    }
    arr[0] = (arr + 1)[idx];
    func_0206b964(self, arr);
}
