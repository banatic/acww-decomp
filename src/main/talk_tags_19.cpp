/* talk_tags_19: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02069bd0 @ 0x02069bd0, 0x4c bytes, Thumb
 * func_02069b80 @ 0x02069b80, 0x50 bytes, Thumb
 * func_02069af0 @ 0x02069af0, 0x90 bytes, Thumb
 */

class UnkStruct_02069bd0 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13(int a, int b);
};

struct UnkStruct_02069bd0_2 {
    unsigned char pad_00[0x14a8];
    UnkStruct_02069bd0 *obj;
};

struct UnkStruct_02069bd0_3 {
    unsigned char pad_00[0x24];
    UnkStruct_02069bd0_2 *inner;
    unsigned char pad_28[0x10];
};

extern "C" void func_020a8718(char *dst, char *a, char *b);
extern "C" int func_020644cc(int x);
extern "C" void func_0206b964(UnkStruct_02069bd0_3 *self, char *c);

class UnkStruct_02069b80 {
  public:
    virtual void m0() = 0;
    virtual void m1() = 0;
    virtual void m2() = 0;
    virtual void m3() = 0;
    virtual void m4() = 0;
    virtual void m5() = 0;
    virtual void m6() = 0;
    virtual void m7() = 0;
    virtual void m8() = 0;
    virtual void m9() = 0;
    virtual void m10() = 0;
    virtual void m11() = 0;
    virtual void m12() = 0;
    virtual void m13(int a, int b) = 0;
};

struct InnerStruct {
    char pad_00[0x14a8];
    UnkStruct_02069b80 *vtobj;
};

struct UnkStruct_02069b80_2 {
    char pad_00[0x24];
    InnerStruct *inner;
    char pad_28[0x10];
    char someField;
};

extern "C" int func_020a86e4(void *, unsigned char *, unsigned char *, unsigned char *);

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

extern "C" int func_020984e8(void);
extern "C" int func_02099870(int);
extern "C" int func_020807a8(UnkStruct_02069af0 *, int);
extern "C" int func_02081d20(void *object);
extern "C" void func_0206bb9c(void *object, int code, const void *message);
extern "C" void *data_020df140;

extern "C" void func_02069bd0(UnkStruct_02069bd0_3 *self)
{
    unsigned char local[8];
    self->inner->obj->v13(0, 2);
    func_020a8718((char *) self + 0x38, (char *) &local[1], (char *) &local[2]);
    local[0] = ((unsigned char *) &local[1])[func_020644cc(2)];
    func_0206b964(self, (char *) local);
}

extern "C" void func_02069b80(UnkStruct_02069b80_2 *self)
{
    unsigned char data[4];
    self->inner->vtobj->m13(1, 3);
    func_020a86e4(&self->someField, &data[1], &data[2], &data[3]);
    data[0] = (&data[1])[func_020644cc(3)];
    func_0206b964((UnkStruct_02069bd0_3 *) self, (char *) data);
}

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
    func_0206b964((UnkStruct_02069bd0_3 *) self, (char *) (&b));
}
