/* func_ov086_02278a54 @ 0x02278a54, 0x44 bytes, Thumb, module ov086
 * mwccarm 1.2/base -O4,s
 */

extern "C" int func_0201c2a4(void *, int);
extern "C" void func_02016108(void *, int);
extern "C" void func_ov086_02278f80(void *, int);

class VBase {
  public:
    virtual void vfunc_00();
    virtual void vfunc_04();
    virtual void method();
};

extern "C" void func_ov086_02278a54(void *obj, int mode)
{
    switch (mode) {
        case 0: {
            VBase *p = (VBase *) ((char *) obj + 0x658);
            p->method();
            int tmp = func_0201c2a4(obj, 4);
            func_02016108((char *) obj + 0x658, tmp);
            func_ov086_02278f80(obj, 1);
            break;
        }
        case 8:
            func_ov086_02278f80(obj, 0);
            break;
        default:
            break;
    }
}
