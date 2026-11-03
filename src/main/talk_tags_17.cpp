/* talk_tags_17: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020696e4 @ 0x020696e4, 0x58 bytes, Thumb
 * func_02069660 @ 0x02069660, 0x84 bytes, Thumb
 */

extern "C" void func_020a8718(void *, unsigned char *, unsigned char *);
extern "C" int func_020984d4(void);
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

struct UnkStruct_02069660 {
    virtual int v00();
    virtual int v01();
    virtual int v02();
    virtual int v03();
    virtual int v04();
    virtual int v05();
    virtual int v06();
    virtual int v07();
    virtual int v08();
    virtual int v09();
    virtual int v10();
    virtual int v11();
    virtual int v12();
    virtual int v13(int, int);
    virtual int v14();
    virtual int v15();
    virtual int v16();
    virtual int v17();
    virtual int v18();
    virtual int v19();
    virtual int v20();
    virtual int v21();
    virtual int v22();
    virtual int v23();
    virtual int v24();
    virtual int v25();
    virtual int v26();
};

extern "C" {
extern int func_020a86e4(void *, void *, void *, void *);
extern int func_020808ec(unsigned int);
extern void func_0206bb9c(void *object, int code, const void *message);
extern int data_020df138;
}

extern "C" void func_020696e4(Parent *p)
{
    unsigned char result;
    unsigned char local[2];

    p->wrap->v->method(12, 2);

    result = local[(func_020988d8((((int) (func_020a8718(&p->obj, &local[0], &local[1]), &p->obj)), func_020984d4())) != 1)];

    func_0206b964(p, &result);
}

extern "C" void func_02069660(void *a0)
{
    unsigned char buf[4];
    UnkStruct_02069660 *obj;

    obj = *(UnkStruct_02069660 **) (*(char **) ((char *) a0 + 0x24) + 0x14a8);

    obj->v13(0xd, 2);

    func_020a86e4((char *) a0 + 0x38, &buf[0], &buf[2], &buf[3]);
    buf[0] = (unsigned char) (buf[0] - 1);

    {
        int flag;
        int callResult = obj->v26();
        flag = 0;
        if (callResult) {
            int x = func_020808ec((unsigned int) callResult);
            if (x != buf[0]) {
                flag = 1;
            }
        } else {
            func_0206bb9c(a0, 0x1021, &data_020df138);
        }
        buf[1] = (&buf[2])[flag];
    }

    func_0206b964(a0, (unsigned char *) (&buf[1]));
}
