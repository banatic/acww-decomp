/* room_object_02252f2c_3: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0221a420 @ 0x0221a420, 0x8c bytes, Thumb
 * func_ov004_0221a2dc @ 0x0221a2dc, 0x144 bytes, Thumb, emits _ZN18Obj_ov004_02252f2c19func_ov004_0221a2dcEv
 */

#include "cpp/ov004/Obj_ov004_02252f2c.h"

class UnkStruct_0221a420 {
  public:
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual void s27();
    virtual void s28(int a, int b);
};

extern "C" int func_ov004_0221062c(UnkStruct_0221a420 *self, int a);
extern "C" int func_020644cc(int);
extern "C" void func_ov004_0221041c(UnkStruct_0221a420 *self, int a, int b, int c, int d);
extern "C" int func_ov004_0220d0a0(void *p, int a, int b);
extern "C" int func_ov004_0220d2b8(void *p);
extern "C" int func_ov004_0220ffbc(char *);
extern "C" void func_ov004_0220d030(void *);
extern "C" int func_ov004_0220d058(void *, int, int, int);
extern "C" int func_ov004_0221081c(char *);
extern "C" int func_ov004_0220fde0(char *);
extern "C" int func_ov004_0220e5c8(char *);
extern "C" void func_ov004_0223cf40(void *, int, void *);
extern "C" int func_02056f28(void *, int);
extern "C" void func_ov004_0223cf18(void *, short);
extern "C" int func_ov004_022107d4(char *);

extern "C" int func_ov004_0221a420(UnkStruct_0221a420 *self)
{
    char *s = (char *) self;
    int r;
    int t;
    if (*(int *) (s + 0x780) == 1) {
        r = func_ov004_0221062c(self, 0);
        if (*(int *) (s + 0x76c) == 1) {
            t = 0;
        } else {
            t = func_020644cc(r);
        }
        func_ov004_0221041c(self, 0, 0, 0x1000, (unsigned short) t);
        func_ov004_0220d0a0(s + 0x848, *(int *) (s + 0x594), 1);
    }
    if (func_ov004_0220d2b8(s + 0x740) != 0) {
        self->s28(1, 0xff);
    } else {
        self->s28(0, 0xff);
    }
    return 1;
}

int Obj_ov004_02252f2c::func_ov004_0221a2dc()
{
    char *self = (char *) this;
    if (*(int *) (self + 0x780) == 1) {
        func_ov004_0220ffbc(self);
    }
    func_ov004_0220d030(self + 0x848);
    func_ov004_0220d058(self + 0x848, 1, 0, 0);
    func_ov004_0221081c(self);
    ((Obj_ov004_02252f2c *) self)->func_ov004_0221a1d4();
    switch (func_ov004_0220fde0(self)) {
        case 0x123:
            if (!func_ov004_0220e5c8(self)) {
                func_ov004_0223cf40(self + 0x798, 0x429, self + 0x7b8);
                if (func_02056f28(self + 0x5d4, 0x43)) {
                    func_ov004_0223cf18(self + 0x798, 1);
                }
            }
            break;
        case 0x1fb:
            if (!func_ov004_0220e5c8(self)) {
                func_ov004_0223cf40(self + 0x798, 0x42b, self + 0x7b8);
                if (func_02056f28(self + 0x5d4, 4)) {
                    func_ov004_0223cf18(self + 0x798, 1);
                } else if (func_02056f28(self + 0x5d4, 0x16)) {
                    func_ov004_0223cf18(self + 0x798, 2);
                }
            }
            break;
        case 0x1fc:
            if (!func_ov004_0220e5c8(self)) {
                func_ov004_0223cf40(self + 0x798, 0x42c, self + 0x7b8);
                if (func_02056f28(self + 0x5d4, 5) || func_02056f28(self + 0x5d4, 0x12)) {
                    func_ov004_0223cf18(self + 0x798, 1);
                }
            }
            break;
        default:
            func_ov004_022107d4(self);
            break;
    }
    return 1;
}
