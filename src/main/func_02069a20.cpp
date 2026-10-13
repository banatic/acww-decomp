/* func_02069a20 @ 0x02069a20, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
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
