/* func_020526b8 @ 0x020526b8, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_020526b8 {
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
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28(int d, unsigned char e);
    virtual void v29();
    virtual int v30();
};

extern "C" int func_ov004_0223cd50(void);
extern "C" UnkStruct_020526b8 *func_ov004_0223cc10(int r, int a, int b, int c);
extern "C" int func_02052794(int a, int b, int c, int d, int r0, unsigned char f, int g);
extern unsigned char data_020e54a8;

extern "C" int func_020526b8(int a, int b, int c, int d, unsigned char e, unsigned char f, unsigned char g)
{
    UnkStruct_020526b8 *obj;
    unsigned int x;
    int r;

    x = (data_020e54a8 == 1) ? 1 : 0;
    if (x == 0) {
        return 0;
    }
    obj = func_ov004_0223cc10(func_ov004_0223cd50(), a, b, c);
    if (obj == 0) {
        return 0;
    }
    obj->v28(d, e);
    if (g != 0) {
        r = obj->v30();
        return func_02052794(a, b, c, d, r, f, 4);
    }
    return 1;
}
