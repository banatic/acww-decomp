/* func_ov068_0226b904 @ 0x0226b904, 0x78 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern "C" int func_02019e00(void *ptr);
extern "C" int func_02019de8(void *ptr);
extern "C" void func_0207f294(void);
extern "C" int func_ov003_02220340(void);
extern "C" void func_020800d0(void);
extern "C" void func_02019c20(void *ptr, int a, int b, int c, int d, int e);
extern unsigned short data_020c80f8;

class UnkStruct_0226b904 {
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
    virtual void v25();

    unsigned char pad_04[0x50D];
    unsigned char unk_511;
    unsigned char pad_512[0x52];
    char unk_564;
};

typedef struct StateStruct {
    unsigned char pad_00[0x1C];
    unsigned char unk_1C;
} StateStruct;

extern "C" void func_ov068_0226b904(StateStruct *param1, UnkStruct_0226b904 *param2)
{
    if (func_02019e00(&param2->unk_564) == 3) {
        if (func_02019de8(&param2->unk_564) != 0) {
            param2->v25();
            func_0207f294();
            if (func_ov003_02220340() != 0) {
                param2->v25();
                func_020800d0();
                func_02019c20(&param2->unk_564, 2, 0x3b, 1, data_020c80f8, 0);
                param2->unk_511 = 0;
                param1->unk_1C = 2;
            }
        }
    }
}
