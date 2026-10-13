/* func_ov004_0222d790 @ 0x0222d790, 0x21c bytes, Thumb, module ov004
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
    virtual void setState(int) = 0;
};
struct Vec {
    int x, y, z;
};
extern "C" {
extern void *func_0208602c(void);
extern void *func_020860cc(void *);
extern void func_ov004_0222c3f4(char *, void *);
extern void func_ov004_0222c348(char *, void *);
extern void *func_ov004_0222c3a0(char *);
extern void func_02055f2c(char *, void *, int);
extern int func_02057a50(void *, void *);
extern void func_02055dc8(char *, void (*)(void *), char *);
extern void func_ov004_0222da90(void *);
extern void func_ov004_0222d69c(char *);
extern void func_ov004_0222d624(char *);
extern void func_ov004_0222d5c0(char *);
extern void func_ov004_0222d548(char *);
extern int func_020b65c4(void);
extern int func_02073dd4(char *, int);
extern int func_02087e84(void *);
extern void func_ov004_0222d53c(char *);
extern void __register_global_object(void *, void (*)(void *), void *);
extern void func_020012dc(void *);
extern int func_020321bc(char *, int, int, int, Vec *, short, Vec *);
extern char data_ov004_02254eb4[], data_ov004_02254ed0[], data_ov004_02254eec[], data_ov004_02254ef4[], data_ov004_02254f00[];
extern char *data_020ccf94;
extern u32 data_ov004_02258298, data_ov004_02258294;
extern Vec data_ov004_022582a8, data_ov004_022582c0;
extern char data_ov004_0225829c[], data_ov004_022582b4[];
}
extern "C" int func_ov004_0222d790(Actor *actor)
{
    char *self = (char *) actor;
    void *context = func_020860cc(func_0208602c());
    func_ov004_0222c3f4(self + 0x1a4, data_ov004_02254eb4);
    func_ov004_0222c348(self + 0x248, data_ov004_02254ed0);
    func_02055f2c(self + 0xec, func_ov004_0222c3a0(self + 0x1a4), 0);
    *(int *) (self + 0x2b0) = func_02057a50(func_ov004_0222c3a0(self + 0x1a4), data_ov004_02254eec);
    *(int *) (self + 0x2b4) = func_02057a50(func_ov004_0222c3a0(self + 0x1a4), data_ov004_02254ef4);
    *(int *) (self + 0x2b8) = func_02057a50(func_ov004_0222c3a0(self + 0x1a4), data_ov004_02254f00);
    func_02055dc8(self + 0xec, func_ov004_0222da90, self);
    func_ov004_0222d69c(self);
    func_ov004_0222d624(self);
    func_ov004_0222d5c0(self);
    func_ov004_0222d548(self);
    switch (func_020b65c4()) {
        case 11:
            if (func_02073dd4(data_020ccf94, *(int *) (data_020ccf94 + 0x64))) {
                actor->setState(2);
            } else {
                actor->setState(0);
            }
            break;
        case 12:
            if (func_02087e84(context) == 1) {
                actor->setState(0);
            } else {
                actor->setState(2);
            }
            break;
        case 13:
        case 14:
        case 47:
            actor->setState(2);
            break;
    }
    func_ov004_0222d53c(self);
    *(int *) (self + 0x494) = -1;
    if (!(data_ov004_02258298 & 1)) {
        data_ov004_022582a8.x = 0xb000;
        data_ov004_022582a8.y = 0;
        data_ov004_022582a8.z = 0x10800;
        __register_global_object(&data_ov004_022582a8, func_020012dc, data_ov004_0225829c);
        data_ov004_02258298 |= 1;
    }
    if (!(data_ov004_02258294 & 1)) {
        data_ov004_022582c0.x = 0x15000;
        data_ov004_022582c0.y = 0;
        data_ov004_022582c0.z = 0x10800;
        __register_global_object(&data_ov004_022582c0, func_020012dc, data_ov004_022582b4);
        data_ov004_02258294 |= 1;
    }
    func_020321bc(self + 0x358, 0x2000, 0x1c00, 0x2000, &data_ov004_022582a8, 0, 0);
    func_020321bc(self + 0x3f4, 0x2000, 0x1c00, 0x2000, &data_ov004_022582c0, 0, 0);
    return 1;
}
