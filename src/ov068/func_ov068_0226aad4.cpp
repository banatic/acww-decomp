/* func_ov068_0226aad4 @ 0x0226aad4, 0x84 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0226aad4 {
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
    virtual int target();
};

typedef struct UnkStruct_0226aad4_2 {
    char pad_00[0x1c];
    unsigned char unk_1C;
} UnkStruct_0226aad4_2;

extern "C" UnkStruct_0226aad4 *func_0201ce50(UnkStruct_0226aad4 *);
extern "C" int func_ov068_0226aca8(void *, int *, int *, int, int);
extern "C" void func_0207daf4(int, int);
extern "C" void func_020801c4(int, int, int);
extern "C" void func_ov068_0226ada8(void *, UnkStruct_0226aad4 *, int *);
extern "C" void func_ov068_0226ad78(void *, UnkStruct_0226aad4 *, int, int, int);
extern "C" int data_ov068_02276764;

extern "C" int func_ov068_0226aad4(UnkStruct_0226aad4_2 *arg0, UnkStruct_0226aad4 *arg1)
{
    int arg5, a, b;
    int r7;
    UnkStruct_0226aad4 *r6;

    r6 = func_0201ce50(arg1);
    a = 0;
    b = 0;
    r7 = arg1->target();
    arg5 = r6->target();
    func_ov068_0226aca8(arg0, &a, &b, r7, arg5);
    func_0207daf4(b, a);
    func_020801c4(b, a, 0);
    func_ov068_0226ada8(arg0, arg1, &data_ov068_02276764);
    arg5 = 1;
    func_ov068_0226ad78(arg0, arg1, 0, 0, arg5);
    arg5 = 1;
    func_ov068_0226ad78(arg0, r6, 0, 0, arg5);
    arg0->unk_1C = 3;
    return 1;
}
