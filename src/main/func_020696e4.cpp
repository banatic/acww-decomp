/* func_020696e4 @ 0x020696e4, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" int func_020a8718(void *, unsigned char *, unsigned char *);
extern "C" int func_020984d4(int);
extern "C" int func_020988d8(int);
extern "C" void func_0206b964(void *, unsigned char *);

struct UnkStruct_020696e4 {
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
    virtual void method(int, int);
};

struct SubWrapper {
    char pad_00[0x14a8];
    UnkStruct_020696e4 *v;
};

struct Parent {
    char pad_00[0x24];
    SubWrapper *wrap;
    char pad_28[0x10];
    char obj;
};

extern "C" void func_020696e4(Parent *p)
{
    unsigned char result;
    unsigned char local[2];

    p->wrap->v->method(12, 2);

    result = local[(func_020988d8(func_020984d4(func_020a8718(&p->obj, &local[0], &local[1]))) != 1)];

    func_0206b964(p, &result);
}
