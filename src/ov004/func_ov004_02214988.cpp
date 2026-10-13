/* func_ov004_02214988 @ 0x02214988, 0x238 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

class Actor {
  public:
    virtual void slot0() = 0;
    virtual void slot1() = 0;
    virtual void slot2() = 0;
    virtual void slot3() = 0;
    virtual void slot4() = 0;
    virtual void slot5() = 0;
    virtual void slot6() = 0;
    virtual void slot7() = 0;
    virtual void slot8() = 0;
    virtual void slot9() = 0;
    virtual void slot10() = 0;
    virtual void slot11() = 0;
    virtual void slot12() = 0;
    virtual void slot13() = 0;
    virtual void slot14() = 0;
    virtual void slot15() = 0;
    virtual void slot16() = 0;
    virtual void slot17() = 0;
    virtual void slot18() = 0;
    virtual void slot19() = 0;
    virtual void slot20() = 0;
    virtual void slot21() = 0;
    virtual void slot22() = 0;
    virtual void slot23() = 0;
    virtual void slot24() = 0;
    virtual void slot25() = 0;
    virtual void slot26() = 0;
    virtual void slot27() = 0;
    virtual void setState(int, int) = 0;
};
extern "C" {
extern void *func_ov004_0220ffa4(char *);
extern void *func_ov004_0220e220(void *);
extern void *func_ov004_0220d9ec(void *, int);
extern void *func_ov004_0220d9e0(void *, int);
extern void *func_ov004_0220da04(void *, int);
extern void *func_ov004_0220d9d4(void *, int);
extern void *func_ov004_0220d9f8(void *, int);
extern void *func_ov004_0220e050(void *);
extern int func_0209d324(void *);
extern int func_020564d0(void *, void *, int);
extern int func_0205650c(void *, void *, int);
extern int func_02055140(void *, int);
extern void func_02056478(void *, void *, u8, int, u16);
extern void func_02056424(void *, void *, void *, u8, int, u16);
extern void func_02055060(void *, void *, int, int, u16, u16);
extern void func_02055050(void *);
extern void *func_02055e00(void *);
extern void func_020563dc(void *, void *);
extern u8 func_ov004_0220d2b8(void *);
extern int func_ov004_0223c10c(void);
}
extern "C" int func_ov004_02214988(Actor *actor)
{
    char *self = (char *) actor;
    void *context = func_ov004_0220ffa4(self);
    if (func_ov004_0220d9ec(func_ov004_0220e220(self + 0x6cc), 0)) {
        void *resource = *(void **) (self + 0x594);
        if (func_020564d0(self + 0x824, resource, func_0209d324(context))) {
            func_02056478(self + 0x824, func_ov004_0220d9ec(func_ov004_0220e220(self + 0x6cc), 0), 0, 0x1000, 0);
            func_020563dc(self + 0x824, func_02055e00(self + 0x538));
        }
    }
    if (func_ov004_0220d9e0(func_ov004_0220e220(self + 0x6cc), 0)) {
        void *resource = *(void **) (self + 0x594);
        if (func_0205650c(self + 0x7e4, resource, func_0209d324(context))) {
            func_02056478(self + 0x7e4, func_ov004_0220d9e0(func_ov004_0220e220(self + 0x6cc), 0), 0, 0x1000, 0);
            func_020563dc(self + 0x7e4, func_02055e00(self + 0x538));
        }
    }
    if (func_ov004_0220da04(func_ov004_0220e220(self + 0x6cc), 0)) {
        if (func_02055140(self + 0x538, func_0209d324(context))) {
            func_02055060(self + 0x538, func_ov004_0220da04(func_ov004_0220e220(self + 0x6cc), 0), 0, 0x1000, 0, 0);
            func_02055050(self + 0x538);
        }
    }
    if (func_ov004_0220d9d4(func_ov004_0220e220(self + 0x6cc), 0)) {
        void *resource = *(void **) (self + 0x594);
        if (func_0205650c(self + 0x804, resource, func_0209d324(context))) {
            void *res = func_ov004_0220d9d4(func_ov004_0220e220(self + 0x6cc), 0);
            func_02056424(self + 0x804, res, func_ov004_0220e050(self + 0x6cc), 0, 0x1000, 0);
            func_020563dc(self + 0x804, func_02055e00(self + 0x538));
        }
    }
    if (func_ov004_0220d9f8(func_ov004_0220e220(self + 0x6cc), 0)) {
        void *resource = *(void **) (self + 0x594);
        if (func_0205650c(self + 0x7c4, resource, func_0209d324(context))) {
            func_02056478(self + 0x7c4, func_ov004_0220d9f8(func_ov004_0220e220(self + 0x6cc), 0), 3, 0x1000, 0);
            func_020563dc(self + 0x7c4, func_02055e00(self + 0x538));
        }
    }
    if (func_ov004_0220d2b8(self + 0x740) && !func_ov004_0223c10c()) {
        actor->setState(2, 255);
    } else {
        actor->setState(0, 255);
    }
    return 1;
}
