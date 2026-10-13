/* func_020b2734 @ 0x020b2734, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e54a8;
extern "C" int func_0204bbd4(int);
extern "C" void func_020b30e8(int, int);

class VirtualObj {
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
    virtual void v26();
    virtual void v27(int arg);
};

extern "C" VirtualObj *func_ov003_02220174(int);

struct Flags {
    unsigned short a : 6;
    unsigned short b : 6;
    unsigned short c : 4;
};

extern "C" void func_020b2734(struct Flags *p)
{
    int a_res;
    unsigned char b;
    int cond;
    VirtualObj *obj;

    a_res = func_0204bbd4(p->a);
    b = p->b;

    cond = (data_020e54a8 == 0) ? 1 : 0;
    if (cond != 0) {
        obj = func_ov003_02220174(a_res);
        if (obj != 0) {
            obj->v27(b);
            return;
        }
    }
    func_020b30e8(a_res, b);
}
