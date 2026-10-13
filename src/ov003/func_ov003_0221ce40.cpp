/* func_ov003_0221ce40 @ 0x0221ce40, 0x114 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov009_02264884(void *);
extern "C" int func_ov009_02264cf8(void *, int);
extern "C" int func_02003348(int, int, int *, int, int);
extern "C" void func_02055dc8(void *, void *, void *);
extern "C" int func_02057a50(int, int *);
extern "C" int func_0205650c(void *, int, int *);
extern "C" void func_02056478(void *, int, int, int, int);
extern "C" int func_02055e00(void *);
extern "C" void func_020563dc(void *, int);
extern "C" void func_0209e474(int *);
extern "C" void func_ov003_0221d038(void);
extern int data_ov003_0223662c[];
extern char data_ov003_0223c8b0;
extern int data_ov003_02238d90;
extern int *data_021c9b1c;

class UnkStruct_0221ce40 {
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
    virtual void v25() = 0;
    virtual void v26() = 0;
    virtual void v27(int) = 0;

    char pad_04[0x58];
    int unk_5C;
    int unk_60;
    int unk_64;
    char pad_68[0xd4];
    char sub_13c[0x5c];
    int unk_198;
    char pad_19C[0x118];
    char sub_2b4[0x20];
    unsigned char unk_2D4;
    char pad_2D5[3];
    int array_2d8[6];
};

extern "C" int func_ov003_0221ce40(UnkStruct_0221ce40 *obj)
{
    int zero = 0;
    int local2[2];
    int local3[3];
    unsigned int i;

    func_ov009_02264884(obj);
    obj->v6();

    for (i = 0; i < 6; i++) {
        int c = obj->unk_64 + 0x500;
        int b = obj->unk_60 + 0x2500;
        int a = obj->unk_5C + data_ov003_0223662c[i];
        local3[0] = a;
        local3[1] = b;
        local3[2] = c;
        data_ov003_0223c8b0 = (char) i;
        int ret = func_02003348(0x26, 0x501f, local3, zero, zero);
        obj->array_2d8[i] = ret;
    }

    func_02055dc8(obj->sub_13c, (void *) func_ov003_0221d038, obj);
    obj->unk_2D4 = (unsigned char) func_02057a50(obj->unk_198, &data_ov003_02238d90);
    int ret2 = func_0205650c(obj->sub_2b4, obj->unk_198, data_021c9b1c);
    if (ret2 != 0) {
        int x = func_ov009_02264cf8(obj, 0);
        func_02056478(obj->sub_2b4, x, 0, 0x1000, 0);
        int y = func_02055e00(obj->sub_13c);
        func_020563dc(obj->sub_2b4, y);
    }

    local2[0] = 0;
    local2[1] = 0;
    func_0209e474(local2);
    if (*(unsigned char *) &local2[1] == 1) {
        obj->v27(1);
    } else {
        obj->v27(0);
    }
    return 1;
}
