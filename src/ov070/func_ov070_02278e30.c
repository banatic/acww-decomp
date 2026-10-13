/* func_ov070_02278e30 @ 0x02278e30, 0x29c bytes, Thumb, module ov070
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02278e30_2 {
    char pad_00[0xc0];
    int unk_C0;
    u16 h[3];
} UnkStruct_02278e30_2;

typedef struct UnkStruct_02278e30 {
    u16 ids[3];
    u8 flags[3];
    u8 thresh;
    u8 pad_0A[2];
    int unk_0C;
} UnkStruct_02278e30;

extern UnkStruct_02278e30 data_ov070_02279be0[];

extern int func_020644cc(int);
extern void func_ov070_02279238(UnkStruct_02278e30_2 *);
extern int func_020984e8(void);
extern void func_020996d4(int, u16 *);
extern void func_020996ec(int, u16 *);
extern void func_02095b40(u16 *);
extern void func_02095b4c(u16 *);
extern void func_02095b58(u16 *);
extern void func_02063ccc(void *, int, int);
extern void func_020638d4(u16 *, void *, int, int, int, int, int);
extern void func_02063cc8(void *);
extern int func_0204bcdc(u16 *);
extern int func_0204bc64(u16 *);
extern void func_02099704(int, u16 *);
extern void func_02015de4(UnkStruct_02278e30_2 *, u16 *, int, int);
extern void func_0209a000(u16 *, int);

int func_ov070_02278e30(UnkStruct_02278e30_2 *self)
{
    int ret;
    int t;
    u16 w[20];
    int o[2][2];
    u8 n;
    u8 k;
    int i;
    int j;
    int g;
    int ok;
    int flag;
    u16 id;
    int x;
    u16 *p;

    n = (u8) func_020644cc(4);
    k = 6;
    w[0] = 0xfff1;
    func_ov070_02279238(self);
    for (i = 0; i < 7; i++) {
        if (data_ov070_02279be0[i].unk_0C >= self->unk_C0) {
            k = (u8) i;
            break;
        }
    }

    g = func_020984e8();
    if (n < 3) {
        w[1] = 0xfff1;
        func_020996d4(g, &w[1]);
        if (data_ov070_02279be0[k].flags[n] == 0) {
            id = data_ov070_02279be0[k].ids[n];
            w[2] = id;
            func_02095b40(&w[2]);
            w[3] = id;
            func_020996ec(g, &w[3]);
            w[4] = 0xfff1;
            func_02095b4c(&w[4]);
            w[5] = 0xfff1;
            func_020996d4(g, &w[5]);
        } else {
            id = data_ov070_02279be0[k].ids[n];
            w[6] = id;
            func_02095b4c(&w[6]);
            w[7] = id;
            func_020996d4(g, &w[7]);
            w[8] = 0xfff1;
            func_02095b40(&w[8]);
            w[9] = 0xfff1;
            func_020996ec(g, &w[9]);
        }
    } else {
        w[10] = 0xfff1;
        func_020996d4(g, &w[10]);
        w[11] = 0xfff1;
        func_020996ec(g, &w[11]);
        w[12] = 0xfff1;
        func_02095b4c(&w[12]);
        w[13] = 0xfff1;
        func_02095b40(&w[13]);
    }

    x = func_020644cc(0x65);
    if (data_ov070_02279be0[k].thresh >= (u8) x) {
        func_02063ccc(o[0], 2, 0x22);
        func_020638d4(&w[14], o[0], 0, 0, 1, 1, 0);
        w[0] = w[14];
        func_02063cc8(o[0]);
        ret = 1;
    } else {
        func_02063ccc(o[1], 2, 0);
        func_020638d4(&w[15], o[1], 0, 0, 1, 1, 0);
        w[0] = w[15];
        func_02063cc8(o[1]);
        ret = 0;
    }

    if (func_0204bcdc(&w[0]) != 0) {
        w[17] = 0xfff1;
        t = func_0204bc64(&w[0]);
        if (t == func_0204bc64(&w[17])) {
            ok = 1;
        } else {
            ok = 0;
        }
    } else {
        ok = (w[0] == 0xfff1) ? 1 : 0;
    }
    if (ok == 0) {
        w[16] = w[0];
        func_02095b58(&w[16]);
        func_02099704(g, &w[0]);
        func_02015de4(self, &w[0], 0, 7);
    }

    for (j = 0; j < 3; j++) {
        p = &self->h[j];
        if (func_0204bcdc(p) != 0) {
            w[18] = 0xfff1;
            t = func_0204bc64(p);
            ok = (t == func_0204bc64(&w[18])) ? 1 : 0;
        } else {
            ok = (self->h[j] == 0xfff1) ? 1 : 0;
        }
        if (ok == 0) {
            flag = 0;
            if (self->h[j] >= 0x1429 && self->h[j] <= 0x1430) {
                flag = 1;
            }
            if (flag == 0) {
                if (self->h[j] < 0x12a8 || self->h[j] > 0x12af) {
                    func_0209a000(p, 0);
                }
            }
        }
    }
    return ret;
}
