/* func_ov068_0226ae80 @ 0x0226ae80, 0x40 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern "C" void *func_0201ce50(void *);
extern "C" void *func_0208150c(void *);
extern "C" void func_ov068_0226aec0(void *, void *);

class UnkStruct_0226ae80 {
  public:
    virtual void *m00();
    virtual void *m01();
    virtual void *m02();
    virtual void *m03();
    virtual void *m04();
    virtual void *m05();
    virtual void *m06();
    virtual void *m07();
    virtual void *m08();
    virtual void *m09();
    virtual void *m10();
    virtual void *m11();
    virtual void *m12();
    virtual void *m13();
    virtual void *m14();
    virtual void *m15();
    virtual void *m16();
    virtual void *m17();
    virtual void *m18();
    virtual void *m19();
    virtual void *m20();
    virtual void *m21();
    virtual void *m22();
    virtual void *m23();
    virtual void *m24();
    virtual void *m25();
};

extern "C" void func_ov068_0226ae80(void *unused, UnkStruct_0226ae80 *param)
{
    UnkStruct_0226ae80 *a = (UnkStruct_0226ae80 *) func_0201ce50(param);
    void *x = param->m25();
    void *y = a->m25();
    x = func_0208150c(x);
    y = func_0208150c(y);
    func_ov068_0226aec0(x, y);
}
