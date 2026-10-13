/* func_ov068_0226a020 @ 0x0226a020, 0x78 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

class VBase {
  public:
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual int Call(void);
};

extern "C" int func_020984e8(void);
extern "C" int func_02099870(void);
extern "C" int func_020951bc(int);
extern "C" VBase *func_0201ce50(VBase *);
extern "C" int func_020807a8(int, int);

extern "C" int func_ov068_0226a020(void *self, VBase *arg1, int threshold)
{
    int r5;
    VBase *obj2;
    int b1, b2;

    if (func_020984e8() != 0) {
        func_020984e8();
        r5 = func_02099870();
    } else {
        r5 = 0;
    }
    if (r5 == 0) {
        goto fail;
    }
    if (func_020951bc(r5) == 0) {
        goto fail;
    }

    obj2 = func_0201ce50(arg1);
    b1 = func_020807a8(arg1->Call(), r5);
    b2 = func_020807a8(obj2->Call(), r5);
    if (b1 != 0 && b2 != 0) {
        goto fail;
    }

    return threshold < 0x6000;
fail:
    return 0;
}
