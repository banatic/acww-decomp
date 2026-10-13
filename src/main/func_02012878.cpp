/* func_02012878 @ 0x02012878, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" unsigned char *func_020800d0(void *ptr);

class UnkStruct_02012878 {
  public:
    virtual void *v00();
    virtual void *v01();
    virtual void *v02();
    virtual void *v03();
    virtual void *v04();
    virtual void *v05();
    virtual void *v06();
    virtual void *v07();
    virtual void *v08();
    virtual void *v09();
    virtual void *v10();
    virtual void *v11();
    virtual void *v12();
    virtual void *v13();
    virtual void *v14();
    virtual void *v15();
    virtual void *v16();
    virtual void *v17();
    virtual void *v18();
    virtual void *v19();
    virtual void *v20();
    virtual void *v21();
    virtual void *v22();
    virtual void *v23();
    virtual void *v24();
    virtual void *v25();
};

extern "C" void func_02012878(unsigned int *out, int a, int b, UnkStruct_02012878 *obj)
{
    out[0] = 0;
    out[1] = 0;
    if (obj->v25()) {
        unsigned char *p = func_020800d0(obj->v25());
        unsigned int b1 = p[1] + 1;
        unsigned int b0 = p[0];
        out[0] = b0;
        out[1] = b1;
    }
}
