/* func_ov009_0226305c @ 0x0226305c, 0x42 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern "C" int func_ov009_02264c90(void *p);

class UnkStruct_0226305c {
  public:
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
    virtual int v25();
    virtual int v26();
    virtual int method(int arg);
};

extern "C" int func_ov009_0226305c(UnkStruct_0226305c *p)
{
    int ret = func_ov009_02264c90(p);
    switch (ret) {
        case 2:
            return p->method(1);
        case 3:
            return p->method(5);
        case 1:
            return p->method(3);
        default:
            return 0;
    }
}
