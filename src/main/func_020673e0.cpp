/* func_020673e0 @ 0x020673e0, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_020673e0(void *arg);

class SomeObj {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual int v3();
};

extern "C" SomeObj *func_020ab4d4(void *p);
extern "C" void *func_0206923c(void *buf, void *arg);
extern "C" void func_020691cc(void *buf, int val);
extern "C" volatile int *func_0206921c(void *buf);

extern "C" void func_020673e0(void *arg)
{
    char buf[0x44];
    SomeObj *obj = func_020ab4d4((char *) arg + 0x31c);
    func_0206923c(buf, arg);
    int result = obj->v3();
    func_020691cc(buf, result);
    func_0206921c(buf);
}
