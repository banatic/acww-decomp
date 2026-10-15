/* func_ov004_0220c6fc @ 0x0220c6fc, 0x78 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

class UnknownClass {
  public:
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
    virtual void m12();
    virtual void m13();
    virtual void m14();
    virtual void m15();
    virtual void m16();
    virtual void m17();
    virtual void m18();
    virtual void m19();
    virtual void m20();
    virtual void m21();
    virtual void m22();
    virtual void m23();
    virtual void m24();
    virtual void m25();
    virtual void m26();
    virtual void m27();
    virtual void m28();
    virtual void m29();
    virtual void m30();
    virtual void m31();
    virtual void m32();
    virtual void m33();
    virtual void m34();
    virtual void m35();
    virtual void m36();
    virtual void m37(int arg);
};

extern "C" void func_020eaca0(void *, void *, void *);
extern "C" int func_ov004_0220d594(void *, void *);
extern "C" void func_ov004_0220ee90(void *, void *, int);
extern "C" int func_ov004_0223b22c(void);
extern "C" int func_ov004_0223b058(int, void *, void *, short);
extern "C" void func_ov004_0220e674(void *, int);

extern "C" int func_ov004_0220c6fc(UnknownClass *obj)
{
    int local[4];
    int cond;

    func_020eaca0(&local, (char *) obj + 0x170, (char *) obj + 0x5c);
    func_ov004_0220d594((char *) obj + 0x18c, obj);
    func_ov004_0220ee90(obj, &local, 0);
    cond = func_ov004_0223b22c();
    if (cond != 0) {
        if (func_ov004_0223b058(cond, (char *) obj + 0x250, (char *) obj + 0x5c, *(short *) ((char *) obj + 0x16c))) {
            obj->m37(0);
            func_ov004_0220e674(obj, 1);
            return 1;
        }
    }
    return 0;
}
