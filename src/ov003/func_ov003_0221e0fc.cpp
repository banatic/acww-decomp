/* func_ov003_0221e0fc @ 0x0221e0fc, 0x70 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0221e0fc {
    int pad_00;
    unsigned short unk_04;
};

class UnkStruct_0221e0fc_2 {
  public:
    virtual void v0() = 0;
    virtual void v1() = 0;
    virtual void v2() = 0;
    virtual void v3() = 0;
    virtual void v4() = 0;
    virtual void v5() = 0;
    virtual void v6() = 0;
    virtual void v7() = 0;
    virtual void v8() = 0;
    virtual void v9() = 0;
    virtual void v10() = 0;
    virtual void v11() = 0;
    virtual void v12() = 0;
    virtual void v13() = 0;
    virtual void v14() = 0;
    virtual void v15() = 0;
    virtual void v16() = 0;
    virtual void v17() = 0;
    virtual void v18() = 0;
    virtual void v19() = 0;
    virtual void v20() = 0;
    virtual void v21() = 0;
    virtual void v22() = 0;
    virtual void v23() = 0;
    virtual void v24() = 0;
    virtual UnkStruct_0221e0fc *getPtr() = 0;
    char pad_04[0x138];
    int unk_13C;
    char pad_140[0x178];
    int unk_2B8;
};

extern "C" void func_02055060(void *p1, UnkStruct_0221e0fc *p2, int a, int b, int v, int zero);
extern "C" UnkStruct_0221e0fc *func_02055e00(void *p);
extern "C" int func_ov009_02264cf8(UnkStruct_0221e0fc_2 *obj, int zero);
extern "C" void func_02056440(void *p1, UnkStruct_0221e0fc *p2, int a, int b, int c, int d);

extern "C" int func_ov003_0221e0fc(UnkStruct_0221e0fc_2 *obj)
{
    UnkStruct_0221e0fc *port = obj->getPtr();
    UnkStruct_0221e0fc *second = obj->getPtr();
    unsigned short v = (unsigned short) (port->unk_04 - 1);
    func_02055060(&obj->unk_13C, second, 1, 0x1000, v, 0);
    port = func_02055e00(&obj->unk_13C);
    int r = func_ov009_02264cf8(obj, 0);
    func_02056440(&obj->unk_2B8, port, r, 0, 0x1000, 0);
    return 1;
}
