/* func_ov004_02210abc @ 0x02210abc, 0xd8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN10RoomObject19func_ov004_02210abcEv
 */

#include "cpp/ov004/RoomObject.h"

// The two slots this update calls, past the ones RoomObject declares.
class UnkStruct_02210abc {
  public:
    virtual void v00() = 0;
    virtual void v01() = 0;
    virtual void v02() = 0;
    virtual void v03() = 0;
    virtual void v04() = 0;
    virtual void v05() = 0;
    virtual void v06() = 0;
    virtual void v07() = 0;
    virtual void v08() = 0;
    virtual void v09() = 0;
    virtual void v10() = 0;
    virtual void v11() = 0;
    virtual void v12() = 0;
    virtual void v13() = 0;
    virtual void v14() = 0;
    virtual void v15() = 0;
    virtual void v16() = 0;
    virtual void v17() = 0;
    virtual void v18() = 0;
    virtual void v19() = 0;
    virtual void v20() = 0;
    virtual void v21() = 0;
    virtual void v22() = 0;
    virtual void v23() = 0;
    virtual void v24() = 0;
    virtual void v25() = 0;
    virtual void v26() = 0;
    virtual void v27() = 0;
    virtual void v28() = 0;
    virtual void v29() = 0;
    virtual void v30() = 0;
    virtual void v31() = 0;
    virtual int v32() = 0;
    virtual int v33() = 0;
};

extern "C" int func_ov004_0220cdd8(void *, int);
extern "C" void func_ov004_0220d290(unsigned char *self, int pending);
extern "C" int func_ov004_0220d2a8(void *);
extern "C" int func_ov004_0220d300(void *, void *);
extern "C" int func_ov004_0220e5c8(void *);
extern "C" void func_ov004_0220ed40(void *);
extern "C" void func_ov004_0220f7f0(void *);
extern "C" void func_ov004_0220f8c0(void *);
extern "C" void func_ov004_0220fb90(void *);
extern "C" void func_ov004_0220fefc(void *, void *);
extern "C" int func_ov004_0221081c(void *);
extern "C" void func_ov004_0223cf80(void *);

int RoomObject::func_ov004_02210abc()
{
    // DECLS
    UnkStruct_02210abc *selfp = (UnkStruct_02210abc *) this;
    char *self = (char *) selfp;
    char frame[0x10];
    // ENDDECLS
    if (func_ov004_0220e5c8(self) == 0x0) {
        func_ov004_0223cf80(self + 0x798);
        func_ov004_0220fefc(self, frame);
        *(int *) (self + 0x7b8) = *(int *) (frame);
        *(int *) (self + 0x7bc) = *(int *) (frame + 0x4);
        *(int *) (self + 0x7c0) = *(int *) (frame + 0x8);
    }
    func_ov004_0220cc28();
    func_ov004_0220f8c0(self);
    func_ov004_0220fb90(self);
    if (func_ov004_0220cdd8(self, 0x0) == 0x0 && func_ov004_0220cdd8(self, 0x5) == 0x0) {
        if (*(int *) (self + 0x780) == 0x0) {
            func_ov004_0221081c(self);
        }
        selfp->v32();
    } else {
        selfp->v33();
        if (func_ov004_0220d2a8(self + 0x740) != 0x0) {
            func_ov004_0220d290((unsigned char *) self + 0x740, 0x0);
        }
    }
    if (func_ov004_0220e5c8(self) == 0x0) {
        func_ov004_0220ed40(self);
        func_ov004_0220d300(self + 0x740, self);
        func_ov004_0220f7f0(self);
    }
    return 0x1;
}
