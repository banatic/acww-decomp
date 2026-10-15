/* func_ov068_0226a3e0 @ 0x0226a3e0, 0xbc bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0226a3e0 UnkStruct_0226a3e0;
struct UnkStruct_0226a3e0 {
    unsigned char pad_00[0x1c];
    unsigned char unk_1C;
};

class UnkStruct_0226a3e0_2 {
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
    virtual int GetVal() = 0;
};

extern "C" UnkStruct_0226a3e0_2 *func_0201ce50(UnkStruct_0226a3e0_2 *obj);
extern "C" int func_ov068_0226aca8(UnkStruct_0226a3e0 *self, int *a, int *b, int c, int d);
extern "C" void func_0207daf4(int b, int a);
extern "C" void func_020801c4(int b, int a, int c);
extern "C" void func_ov068_0226ada8(UnkStruct_0226a3e0 *self, UnkStruct_0226a3e0_2 *obj, void *data);
extern "C" unsigned int *func_02082164(void *buf);
extern "C" unsigned int func_0208150c(int a);
extern "C" int func_02003648(void *argument0);
extern "C" int func_02082308(void *buf, int a);
extern "C" void func_02080a7c(int a, void *buf);
extern "C" void func_ov068_0226ad44(UnkStruct_0226a3e0 *self, UnkStruct_0226a3e0_2 *obj, void *data, int a, int b, int c);
extern "C" void *func_0208214c(void *buf);
extern int data_ov068_0227676c;
extern int data_ov068_02276738;

extern "C" int func_ov068_0226a3e0(UnkStruct_0226a3e0 *self, UnkStruct_0226a3e0_2 *obj)
{
    UnkStruct_0226a3e0_2 *other;
    int a, b;
    int c, d;
    unsigned char buf[0x1c];

    other = func_0201ce50(obj);
    a = 0;
    b = 0;
    c = obj->GetVal();
    d = other->GetVal();
    func_ov068_0226aca8(self, &a, &b, c, d);
    func_0207daf4(b, a);
    func_020801c4(b, a, 0);
    func_ov068_0226ada8(self, obj, &data_ov068_0227676c);
    func_02082164(buf);

    if (func_02082308(buf, func_02003648((void *) func_0208150c(b))) != 0) {
        func_02080a7c(b, buf);
    }
    func_ov068_0226ad44(self, obj, &data_ov068_02276738, 4, 2, 1);
    func_ov068_0226ad44(self, other, &data_ov068_02276738, 4, 2, 1);
    self->unk_1C = 3;
    func_0208214c(buf);
    return 1;
}
