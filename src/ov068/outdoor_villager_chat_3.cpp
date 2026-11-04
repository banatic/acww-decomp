/* outdoor_villager_chat_3: 2 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_0226a020 @ 0x0226a020, 0x78 bytes, Thumb
 * func_ov068_02269fd4 @ 0x02269fd4, 0x4c bytes, Thumb
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
extern "C" int func_02099870(int argument0);
extern "C" int func_020951bc(int);
extern "C" VBase *func_0201ce50(VBase *);
extern "C" int func_020807a8(int, int);

class UnkStruct_02269fd4 {
  public:
    virtual int v0() = 0;
    virtual int v1() = 0;
    virtual int v2() = 0;
    virtual int v3() = 0;
    virtual int v4() = 0;
    virtual int v5() = 0;
    virtual int v6() = 0;
    virtual int v7() = 0;
    virtual int v8() = 0;
    virtual int v9() = 0;
    virtual int v10() = 0;
    virtual int v11() = 0;
    virtual int v12() = 0;
    virtual int v13() = 0;
    virtual int v14() = 0;
    virtual int v15() = 0;
    virtual int v16() = 0;
    virtual int v17() = 0;
    virtual int v18() = 0;
    virtual int v19() = 0;
    virtual int v20() = 0;
    virtual int v21() = 0;
    virtual int v22() = 0;
    virtual int v23() = 0;
    virtual int v24() = 0;
    virtual int v25() = 0;
};

extern int data_021e5a2c;
extern "C" int func_0207bb30(int *a, int b, int c);

extern "C" int func_ov068_0226a020(void *self, VBase *arg1, int threshold)
{
    int r5;
    VBase *obj2;
    int b1, b2;

    if (func_020984e8() != 0) {

        r5 = func_02099870((int) func_020984e8());
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

extern "C" int func_ov068_02269fd4(int, UnkStruct_02269fd4 *obj, int limit)
{
    UnkStruct_02269fd4 *v6 = (UnkStruct_02269fd4 *) func_0201ce50((VBase *) obj);
    int v4 = obj->v25();
    int v2 = v6->v25();
    if (func_0207bb30(&data_021e5a2c, v4, v2) >= 4) {
        if (limit < 0x6000) {
            return 1;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}
