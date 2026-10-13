/* func_ov068_0226ae00 @ 0x0226ae00, 0x48 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0226ae00 {
  public:
    virtual void *v0();
    virtual void *v1();
    virtual void *v2();
    virtual void *v3();
    virtual void *v4();
    virtual void *v5();
    virtual void *v6();
    virtual void *v7();
    virtual void *v8();
    virtual void *v9();
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

extern "C" UnkStruct_0226ae00 *func_0201ce50(UnkStruct_0226ae00 *);
extern "C" void *func_0208150c(void *);
extern "C" void func_ov068_0226ae48(UnkStruct_0226ae00 *, void *, void *, void *);

extern "C" void func_ov068_0226ae00(UnkStruct_0226ae00 *p0, UnkStruct_0226ae00 *p1, void *p2)
{
    UnkStruct_0226ae00 *e = func_0201ce50(p1);
    void *a = p1->v25();
    void *b = e->v25();

    a = func_0208150c(a);
    b = func_0208150c(b);

    func_ov068_0226ae48(p0, a, b, p2);
}
