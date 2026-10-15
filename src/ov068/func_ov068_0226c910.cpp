/* func_ov068_0226c910 @ 0x0226c910, 0x54 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0226c910_2 {
    virtual int v0();
    virtual int v1();
    virtual int v2();
    virtual int v3();
    virtual int v4();
    virtual int v5();
    virtual int v6();
    virtual int v7();
    virtual int v8();
    virtual int v9();
    virtual int v10();
    virtual int v11();
    virtual int v12();
    virtual int v13();
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
    virtual int real();
};

struct UnkStruct_0226c910 {
    unsigned char pad_00[0x1d];
    unsigned char b0 : 1;
    unsigned char b1 : 1;
};

extern "C" int func_020984e8(void);
extern "C" int func_02099020(int, int);
extern "C" struct UnkStruct_0226c910 *func_0207f270(int);
extern "C" int func_0207d578(int, int);

extern "C" int func_ov068_0226c910(int a0, UnkStruct_0226c910_2 *obj)
{
    int r0;
    int r5;
    int r6;
    int r4;

    r0 = func_020984e8();
    if (r0 != 0) {
        r0 = func_02099020(r0, 1);
    } else {
        r0 = 0;
    }
    r5 = (r0 != 0);

    r6 = obj->real();

    r4 = 1;
    if (func_0207f270(r6)->b1 == 0) {
        if (r5 != 0 || func_0207d578(r6, 0) == 0) {
            r4 = 0;
        }
    }
    return r4;
}
