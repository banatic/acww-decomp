/* func_020129c0 @ 0x020129c0, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_020129c0 {
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
    virtual int vfunc();
};

extern int data_021e5a2c;
extern "C" char *func_02137550(int *, int);
extern "C" int func_0208150c(int);
extern "C" int func_0207cc94(int *, int *, int);
extern "C" unsigned char *func_020800d0(int object);

extern "C" void func_020129c0(int *out, int unused1, int unused2, UnkStruct_020129c0 *obj)
{
    int forwarded_value;

    int local;
    out[0] = 0;
    out[1] = 0;
    if (obj->vfunc() != 0) {
        func_02137550(&local, 4);
        local = func_0208150c(obj->vfunc());
        if ((forwarded_value = (int) func_0207cc94(&data_021e5a2c, &local, 1)) != 0) {
            unsigned char *p = func_020800d0((int) forwarded_value);
            int b = p[1] + 1;
            int a = p[0];
            out[0] = a;
            out[1] = b;
        }
    }
}
