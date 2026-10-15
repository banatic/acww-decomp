/* func_020c2718 @ 0x020c2718, 0x90 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class CObj {
  public:
    virtual void m0();
    virtual void m1();
    virtual void m2();
};

extern "C" int func_0201c2a4(void *self, int value);
extern "C" void func_02016108(void *obj, int value);
extern "C" unsigned long func_020c1b20(void *p);
extern "C" void func_020c1b28(void *p, unsigned long v);
extern "C" void func_020c26b4(void *self, int i);
extern "C" int func_0208602c(void);
extern "C" int func_020860c4(int);
extern "C" int func_02087f30(void *);

extern "C" void func_020c2718(void *self, int code)
{
    switch (code) {
        case 0:
        case 1:
            ((CObj *) ((char *) self + 0x658))->m2();
            func_02016108((char *) self + 0x658, func_0201c2a4(self, 4));
            if (func_020c1b20((char *) self + 0x658) != 6) {
                func_020c26b4(self, 3);
            }
            break;
        case 8:
            func_020c1b28((char *) self + 0x658, 3);
            if (func_02087f30((void *) func_020860c4((int) func_0208602c())) != 0) {
                func_020c26b4(self, 5);
            } else {
                if (*((unsigned char *) self + 0x711) != 0) {
                    func_020c26b4(self, 2);
                } else {
                    func_020c26b4(self, 0);
                }
            }
            break;
    }
}
