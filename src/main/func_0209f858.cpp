/* func_0209f858 @ 0x0209f858, 0x18c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern "C" {
}

extern "C" {
extern s16 *func_0209d358(int, int);
extern int func_020984e8(void);
extern int func_020992fc(int object);
extern void func_020983ec(int, int);
extern int func_020983e0(void);
extern void func_020983c8(int);
extern int func_02099734(int);
extern int func_02098cf8(int, int);
extern void func_02098aa0(int, int, int);
extern int data_020d1b98[];
}

class UnkStruct_0209f858 {
  public:
    virtual void vf0();
    virtual void vf1();
    char pad_04[0x4c];
    u32 idx50;
};

typedef void (UnkStruct_0209f858::*PMF)();

union PMFStorage {
    PMF pmf;
    struct {
        u32 lo;
        u32 hi;
    } words;
};

struct PMFEntry {
    u32 pad_00;
    u32 pad_04;
    PMFStorage pmf;
};

extern PMFEntry data_021f3ba4[];

extern "C" int func_0209f858(UnkStruct_0209f858 *self)
{
    int profile;
    if (func_0209d358(0, 0x4b)[0] != 0) {
        if ((profile = func_020984e8()) != 0) {
            int v = func_020992fc(profile);
            int b = func_0209d358(0, 0x4b)[0];
            switch (b) {
                case 0:
                    break;
                case 1:
                    func_020983ec(v, 1000000);
                    break;
                case 2:
                    func_020983ec(v, 10000000);
                    break;
                case 3:
                    func_020983ec(v, 100000000);
                    break;
                case 4:
                    func_020983ec(v, 500000000);
                    break;
                case 5:
                    func_020983ec(v, 999999999);
                    break;
            }
        }
    }

    if (func_0209d358(0, 0x4c)[0] != 0) {
        if ((profile = func_020984e8()) != 0) {
            func_020992fc(profile);
            if (func_0209d358(0, 0x4c)[0] != 0) {
                int r4 = func_0209d358(0, 0x4c)[0];
                if (r4 < 1) {
                    r4 = 1;
                } else if (r4 > 21) {
                    r4 = 21;
                }
                int t = func_020983e0();
                if (data_020d1b98[r4] > t) {
                    func_020983c8(data_020d1b98[r4] - 100);
                }
            }
        }
    }

    if (func_0209d358(0, 0x48)[0] != 0) {
        int a = func_020984e8();
        int b = func_02099734(a);
        int r4 = func_02098cf8(b, 1);
        r4 += func_0209d358(0, 0x48)[0];
        if (r4 < 0) {
            r4 = 0;
        } else if (r4 > 0x1869f) {
            r4 = 0x1869f;
        }
        int c = func_02099734(a);
        func_02098aa0(c, r4, 1);
        func_0209d358(0, 0x48)[0] = 0;
    }

    if (data_021f3ba4[self->idx50].pmf.words.lo != 0) {
        (self->*data_021f3ba4[self->idx50].pmf.pmf)();
    }

    return 1;
}
