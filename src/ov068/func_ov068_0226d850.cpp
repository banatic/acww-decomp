/* func_ov068_0226d850 @ 0x0226d850, 0x110 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0226d850 {
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
    virtual int v25();
    unsigned char pad_04[0x894];
    unsigned char unk_898[0x18];
    unsigned int unk_8B0;
    unsigned int unk_8B4;
    unsigned char unk_8B8[0x13c];
    unsigned char unk_9F4[4];
};

extern "C" double data_ov068_02276eb0;

extern "C" int func_0202e1fc(UnkStruct_0226d850 *obj);
extern "C" int func_0207918c(void);
extern "C" int func_020791ec(void);
extern "C" int func_0207f294(int x);
extern "C" int func_0207f1d8(int x);
extern "C" void func_ov068_02266cb0(void *a, UnkStruct_0226d850 *obj);
extern "C" void func_ov068_0226cbc8(void *a);
extern "C" void func_ov068_0226cce8(void *a, UnkStruct_0226d850 *obj, int val);
extern "C" void func_0202e118(void *out, UnkStruct_0226d850 *obj);
extern "C" void func_ov068_0226d5f4(UnkStruct_0226d850 *obj);
extern "C" void func_ov068_02266f30(void *a);

extern "C" int func_ov068_0226d850(UnkStruct_0226d850 *obj)
{
    int r5;
    int r6;
    int idx;
    unsigned short tmp;

    r5 = obj->v25();

    if (func_0202e1fc(obj) == 0) {
        return 0;
    }

    *(double *) ((char *) obj + 0x8b0) = data_ov068_02276eb0;

    func_ov068_02266cb0(obj->unk_898, obj);

    r6 = func_0207918c();
    func_ov068_0226cbc8(obj->unk_8B8);

    if (r6 == func_0207f294(r5)) {
        func_ov068_0226cce8(obj->unk_8B8, obj, 0xd);
    } else {
        r6 = func_020791ec();
        if (r6 == func_0207f294(r5)) {
            func_ov068_0226cce8(obj->unk_8B8, obj, 0xc);
        } else {
            idx = func_0207f1d8(r5);
            switch (idx) {
                case 0:
                    func_ov068_0226cce8(obj->unk_8B8, obj, 0);
                    func_0202e118(&tmp, obj);
                    if (tmp != 0xfff1) {
                        func_ov068_0226d5f4(obj);
                    }
                    break;
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                    func_ov068_0226cce8(obj->unk_8B8, obj, 0xc);
                    break;
                default:
                    func_ov068_0226cce8(obj->unk_8B8, obj, 3);
                    break;
            }
        }
    }

    func_ov068_02266f30(obj->unk_9F4);
    return 1;
}
