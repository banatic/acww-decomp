/* func_ov068_0226b88c @ 0x0226b88c, 0x78 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0226b88c {
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
};

typedef struct {
    unsigned char pad_00[0x1c];
    unsigned char flag;
} UnkStruct_0226b88c_2;

extern unsigned short data_020c80f8;
extern "C" int func_02019e00(void *);
extern "C" int func_02019de8(void *);
extern "C" int func_0207f294(int);
extern "C" int func_ov003_02220340(int index);
extern "C" int func_020800d0(int);
extern "C" int func_02019c20(void *, int, int, int, int, int);

extern "C" void func_ov068_0226b88c(UnkStruct_0226b88c_2 *out, UnkStruct_0226b88c *obj)
{
    if (func_02019e00((char *) obj + 0x564) == 1) {
        if (func_02019de8((char *) obj + 0x564) != 0) {
            if (func_ov003_02220340(func_0207f294(obj->v25())) != 0) {
                func_020800d0(obj->v25());
                func_02019c20((char *) obj + 0x564, 2, 0x3b, 1, data_020c80f8, 0);
                *((unsigned char *) obj + 0x511) = 0;
                out->flag = 2;
            }
        }
    }
}
