/* func_ov003_02219ebc @ 0x02219ebc, 0xc4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/helper_ctors.h"

struct Head {
    char pad[0xec];
};
struct UnkStruct_02219ebc {
    char pad[4];
};

struct Fl {
    unsigned short b0 : 2;
    unsigned short b2 : 2;
    unsigned short b4 : 4;
    unsigned short b8 : 1;
    unsigned short b9 : 7;
};

struct Res {
    char pad[8];
    int unk_08;
};

struct Loc {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual int v3();
    char pad[0x114];
};

// Same layout as Loc; built and torn down by its out-of-line pair.
struct LocBuf {
    void *vtbl;
    char pad[0x114];
};

extern "C" {
extern void func_0203ee14(void *self, UnkStruct_02219ebc *arg);
extern int func_020644cc(int);
extern void func_020a8164(UnkStruct_02219ebc *, const char *);
extern void func_02066954(UnkStruct_02219ebc *, int, int);
extern int func_020b4a20(Loc *, char *, const char *);
extern const char data_ov003_0223838c[];
extern const char data_ov003_0223839c[];
}

struct UnkStruct_02219ebc_2 : Head, UnkStruct_02219ebc {
    char pad_F0[0x1a];
    unsigned char unk_10A;
    char pad_10B[0x21];
    Res *unk_12C;
    char pad_130[0x248];
    Fl fl;
};

extern "C" int func_ov003_02219ebc(UnkStruct_02219ebc_2 *obj)
{
    int n;

    func_0203ee14(obj, obj);
    if (obj->fl.b8 != 0) {
        n = func_020644cc(3) + (obj->fl.b2 & 3) * 3;
    } else {
        n = func_020644cc(3) + ((obj->fl.b2 & 3) * 3 + 0xc);
    }
    func_020a8164(&(UnkStruct_02219ebc &) *obj, data_ov003_0223838c);
    obj->unk_10A = (unsigned char) n;
    obj->unk_12C->unk_08 = 1;
    {
        char buf[4];
        buf[0] = 0x26;
        {
            LocBuf loc;
            Loc *lp;
            func_020b55d0(&loc);
            func_020b4a20((Loc *) &loc, buf, data_ov003_0223839c);
            lp = (Loc *) &loc;
            func_02066954(&(UnkStruct_02219ebc &) *obj, lp->v3(), 0);
            obj->fl.b8 = 0;
            func_020b55b8(&loc);
        }
    }
    return 1;
}
