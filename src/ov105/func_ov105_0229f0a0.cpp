/* func_ov105_0229f0a0 @ 0x0229f0a0, 0x7c bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern "C" int func_ov002_02207f48(void *, int);
extern "C" unsigned char *func_ov002_022080a0(void *, unsigned char value);
extern "C" void func_ov105_0229db14(void *);
extern "C" void func_ov105_0229c320(void *, int);
extern "C" int func_0206fe54(void);
extern "C" int func_ov105_0229d73c(void *, unsigned char);
extern "C" void func_0208e4c0(void *, int);
extern "C" void func_ov105_0229d17c(void *);
extern "C" unsigned char *func_ov002_02208098(void *, unsigned char value);
extern "C" void func_ov105_0229ed78(void *);

class VirtualObj {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

extern "C" void func_ov105_0229f0a0(void *arg)
{
    if (func_ov002_02207f48(arg, 0) == 0) {
        goto finish;
    }
    func_ov002_022080a0(arg, 2);
    func_ov105_0229db14(arg);
    func_ov105_0229c320(arg, 0x40);
    if (((unsigned char *) arg)[0x2b4] == 0) {
        goto finish;
    }
    if (func_0206fe54() == 0) {
        goto finish;
    }
    if (func_ov105_0229d73c(arg, ((unsigned char *) arg)[0x2ba]) == 0) {
        func_0208e4c0((char *) arg + 0x24a4, 4);
    }
    ((VirtualObj *) ((char *) arg + 0x24a4))->f3();
    func_ov105_0229d17c(arg);
    func_ov002_02208098(arg, 8);
finish:
    func_ov105_0229ed78(arg);
}
