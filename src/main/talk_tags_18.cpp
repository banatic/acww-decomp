/* talk_tags_18: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02069a20 @ 0x02069a20, 0x74 bytes, Thumb
 * func_020699c0 @ 0x020699c0, 0x60 bytes, Thumb
 */

extern "C" void func_020a86a4(void *p1, void *p2, void *p3, void *p4, void *p5);
extern "C" int func_02060e78(void *p);
extern "C" void func_0206b964(void *a, void *b);
extern int data_021ebcd4;

class UnkStruct_02069a20 {
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
    virtual void method(int a, int b);
};

struct UnkStruct_02069a20_2;

struct UnkStruct_02069a20_3 {
    char pad_00[0x24];
    UnkStruct_02069a20_2 *inner;
};

class UnkStruct_020699c0_2 {
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
    virtual void f13(int, int);
};

struct UnkStruct_020699c0 {
    unsigned char pad_00;
};

struct Class {
    char pad_00[0x24];
    char *unk_24;
    char pad_28[0x10];
    UnkStruct_020699c0 sub;
};

extern "C" unsigned int func_020a86e4(UnkStruct_020699c0 *, unsigned char *, unsigned char *, unsigned char *);
extern "C" unsigned int func_0203cbf4(void);

extern "C" void func_02069a20(UnkStruct_02069a20_3 *s)
{
    unsigned char arr[4];
    unsigned char *p;
    void *local_ptr;
    int v = 4;
    int idx;
    UnkStruct_02069a20 *obj = *(UnkStruct_02069a20 **) ((char *) s->inner + 0x14a8);
    obj->method(v, v);
    func_020a86a4((char *) s + 0x38, &arr[1], &arr[2], &arr[3], &local_ptr);
    int ret = func_02060e78(&data_021ebcd4);
    if (ret == 0) {
        idx = 0;
    } else if (ret >= 1 && ret <= 2) {
        idx = 1;
    } else if (ret == 3) {
        idx = 2;
    } else {
        idx = 3;
    }
    p = arr + 1;
    arr[0] = p[idx];
    func_0206b964(s, arr);
}

extern "C" void func_020699c0(Class *self)
{
    unsigned char result;
    unsigned char arr[3];
    int idx;
    unsigned int r;
    UnkStruct_020699c0_2 *obj;

    obj = *(UnkStruct_020699c0_2 **) ((char *) self->unk_24 + 0x14a8);
    obj->f13(5, 3);

    r = (func_020a86e4(&self->sub, &arr[0], &arr[1], &arr[2]), func_0203cbf4());

    if (r == 0x38) {
        idx = 2;
    } else {
        idx = (r < 0x21) ? 0 : 1;
    }

    result = arr[idx];
    func_0206b964((void *) self, (void *) (&result));
}
