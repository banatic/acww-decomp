/* func_0202e3ac @ 0x0202e3ac, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" int func_0202df18(void *, void *, unsigned short *);
extern "C" void func_02080cd8(void *, unsigned short *);
extern "C" void func_020783a8(void *, unsigned short *);

class C032e3ac {
  public:
    virtual int vfunc_00();
    virtual int vfunc_04();
    virtual int vfunc_08();
    virtual int vfunc_0c();
    virtual int vfunc_10();
    virtual int vfunc_14();
    virtual int vfunc_18();
    virtual int vfunc_1c();
    virtual int vfunc_20();
    virtual int vfunc_24();
    virtual int vfunc_28();
    virtual int vfunc_2c();
    virtual int vfunc_30();
    virtual int vfunc_34();
    virtual int vfunc_38();
    virtual int vfunc_3c();
    virtual int vfunc_40();
    virtual int vfunc_44();
    virtual int vfunc_48();
    virtual int vfunc_4c();
    virtual int vfunc_50();
    virtual int vfunc_54();
    virtual int vfunc_58();
    virtual int vfunc_5c();
    virtual int vfunc_60();
    virtual int target();
};

extern "C" void func_0202e3ac(C032e3ac *obj, unsigned short *p, int flag)
{
    unsigned short val = *p;
    int cond = ((unsigned int) val >= 0x11a8u && (unsigned int) val <= 0x12a7u);
    if (!cond) {
        if ((unsigned int) val < 0x12a8u || (unsigned int) val > 0x12afu) {
            return;
        }
    }
    int result = obj->target();
    func_0202df18((char *) obj + 0x64c, obj, p);
    if (result != 0) {
        func_02080cd8((void *) result, p);
        if (flag) {
            func_020783a8((void *) result, p);
        }
    }
}
