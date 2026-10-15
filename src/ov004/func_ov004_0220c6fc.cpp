/* func_ov004_0220c6fc @ 0x0220c6fc, 0x78 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

class UnknownClass {
  public:
    virtual void vfunc_00();
    virtual void vfunc_04();
    virtual void vfunc_08();
    virtual void vfunc_0c();
    virtual void vfunc_10();
    virtual void vfunc_14();
    virtual void vfunc_18();
    virtual void vfunc_1c();
    virtual void vfunc_20();
    virtual void vfunc_24();
    virtual void vfunc_28();
    virtual void vfunc_2c();
    virtual void vfunc_30();
    virtual void vfunc_34();
    virtual void vfunc_38();
    virtual void vfunc_3c();
    virtual void vfunc_40();
    virtual void vfunc_44();
    virtual void vfunc_48();
    virtual void vfunc_4c();
    virtual void vfunc_50();
    virtual void vfunc_54();
    virtual void vfunc_58();
    virtual void vfunc_5c();
    virtual void vfunc_60();
    virtual void vfunc_64();
    virtual void vfunc_68();
    virtual void vfunc_6c();
    virtual void vfunc_70();
    virtual void vfunc_74();
    virtual void vfunc_78();
    virtual void vfunc_7c();
    virtual void vfunc_80();
    virtual void vfunc_84();
    virtual void vfunc_88();
    virtual void vfunc_8c();
    virtual void vfunc_90();
    virtual void vfunc_94(int arg);
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
            obj->vfunc_94(0);
            func_ov004_0220e674(obj, 1);
            return 1;
        }
    }
    return 0;
}
