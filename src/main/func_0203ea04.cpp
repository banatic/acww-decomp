/* func_0203ea04 @ 0x0203ea04, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0203ea04 {
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
    virtual int v21(UnkStruct_0203ea04 *arg);
};

struct Param {
    char pad_00[0x0c];
    int unk_0C;
    int unk_10;
    char pad_14[3];
    char unk_17;
};

extern "C" UnkStruct_0203ea04 *func_0203ef90(int);
extern "C" int func_0203ef5c(UnkStruct_0203ea04 *);
extern "C" int func_0203efbc(void);
extern "C" int func_0203ee34(UnkStruct_0203ea04 *, UnkStruct_0203ea04 *);
extern "C" int func_0203eb08(Param *);
extern "C" int func_02095d84(void);
extern "C" void func_02095904(void);

extern "C" int func_0203ea04(Param *param)
{
    UnkStruct_0203ea04 *a, *b;
    a = func_0203ef90(param->unk_10);
    b = func_0203ef90(param->unk_0C);
    if (func_02095d84() == 0) {
        return 0;
    }
    param->unk_17 = 0;
    if (a == 0) {
        if (func_0203ef5c(b) == 0) {
            return 0;
        }
        param->unk_10 = func_0203efbc();
        goto L_common;
    } else {
        if (func_0203ee34(a, b) != 0) {
            goto L_common;
        }
        if (a->v21(b) == 0) {
            goto L_ret0;
        }
        param->unk_17 = 5;
        goto L_common;
    L_ret0:
        return 0;
    L_common:
        if (func_0203eb08(param) != 0) {
            func_02095904();
            return 1;
        } else {
            return 0;
        }
    }
}
