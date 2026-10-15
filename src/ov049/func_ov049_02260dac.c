/* func_ov049_02260dac @ 0x02260dac, 0x11c bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02260dac {
    char pad_00[0x976];
    u8 unk_976;
} UnkStruct_02260dac;

typedef struct UnkStruct_02260dac_2 {
    char pad_00[0x40];
    void *unk_40;
    char pad_44[0xb0 - 0x44];
    UnkStruct_02260dac *unk_B0;
} UnkStruct_02260dac_2;

typedef struct Msg {
    u8 b[2];
    u16 unk_02;
    u16 unk_04;
} Msg;

extern int func_0206fc6c(void);
extern void *func_020984e8(void);
extern unsigned int func_0206fc8c(void);
extern void *func_020996b8(void *);
extern int func_02072ba4(int record);
extern unsigned int func_02072b64(int, unsigned int);
extern int func_02071aa8(int, unsigned int, int, int, int);
extern u16 *func_02099710(void *);
extern u16 *func_020996f8(void *);
extern int func_02095b58(u16 *);
extern int func_02095b40(u16 *);
extern void func_0206844c(void *, u8 *, int);
extern int data_ov049_02263298;

void func_ov049_02260dac(UnkStruct_02260dac_2 *this)
{
    Msg m;
    void *a;
    unsigned int t;
    u16 x, y;
    int p, q;

    if (func_0206fc6c() != 0) {
        a = func_020984e8();
        t = func_0206fc8c();
        t = func_02072b64(func_02072ba4((int) func_020996b8(a)), t);
        func_02071aa8(9, t, 4, this->unk_B0->unk_976, 1);
        if (t < 8) {
            x = (u16) (t + 0x12a8);
        } else {
            x = 0x12a8;
        }
        if (t < 8) {
            y = (u16) (t + 0x1429);
        } else {
            y = 0x1429;
        }
        p = *func_02099710(a);
        q = *func_020996f8(a);
        if (x == p) {
            u16 *ptr = func_02099710(a);
            int ok = 0;
            u16 v = *ptr;
            if (v >= 0x12a8 && v <= 0x12af) {
                ok = 1;
            }
            if (ok != 0) {
                m.unk_02 = x;
                func_02095b58(&m.unk_02);
            }
        }
        if (y == q) {
            u16 *ptr = func_020996f8(a);
            int ok = 0;
            u16 v = *ptr;
            if (v >= 0x1429 && v <= 0x1430) {
                ok = 1;
            }
            if (ok != 0) {
                m.unk_04 = y;
                func_02095b40(&m.unk_04);
            }
        }
        m.b[0] = 0x21;
        func_0206844c(this->unk_40, &m.b[0], data_ov049_02263298);
    } else {
        m.b[1] = 0x22;
        func_0206844c(this->unk_40, &m.b[1], data_ov049_02263298);
    }
}
