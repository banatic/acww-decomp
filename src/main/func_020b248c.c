/* func_020b248c @ 0x020b248c, 0x11c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 lo : 4;
    u8 hi : 4;
} UnkStruct_020b248c;
typedef struct {
    u8 d[10];
} UnkStruct_020b248c_4;
typedef struct {
    u8 a : 2;
    u8 b : 6;
    u8 pad_01;
    UnkStruct_020b248c_4 sub;
} UnkStruct_020b248c_2;

typedef struct {
    int pad_00;
} UnkStruct_020b248c_3;

extern UnkStruct_020b248c_3 *data_020ccf94;
extern UnkStruct_020b248c data_021f4bac[];
extern UnkStruct_020b248c_4 data_020d1f24[];

extern u32 func_020b3f58(void *);
extern int func_02073d90(UnkStruct_020b248c_3 *);
extern int func_02073918(UnkStruct_020b248c_3 *, int);
extern u32 func_020b3fc0(u8);
extern void func_020b2a68(UnkStruct_020b248c_4 *, UnkStruct_020b248c_4 *);
extern u32 func_020b2a3c(UnkStruct_020b248c_4 *);
extern int func_020b278c(void *);
extern void func_020b2a64(UnkStruct_020b248c_4 *);
extern void func_02073820(UnkStruct_020b248c_3 *);
extern void func_020737f0(UnkStruct_020b248c_3 *, UnkStruct_020b248c_2 *, int);
extern void func_02073770(UnkStruct_020b248c_3 *, int, int);

void func_020b248c(void *a0)
{
    u32 x;
    UnkStruct_020b248c_2 m;
    u32 idx;
    UnkStruct_020b248c_3 *g;
    u8 lo;
    u32 y;
    UnkStruct_020b248c *e;

    idx = func_020b3f58(a0);
    g = data_020ccf94;
    if (func_02073d90(g) == 0 || func_02073918(g, 0) != 0) {
        e = &data_021f4bac[idx];
        lo = data_021f4bac[idx].lo;
        x = func_020b3fc0(lo);
        lo = (u8) (lo | 1);
        y = func_020b3fc0(lo);
        func_020b2a68(&m.sub, idx < 0x22 ? &data_020d1f24[idx] : &data_020d1f24[0]);
        if (y > func_020b2a3c(&m.sub)) {
            e->hi = 2;
        } else if (func_020b278c(a0) && x == 0) {
            e->hi = 3;
        } else {
            e->lo = lo;
            e->hi = 1;
            func_020b278c(a0);
        }
        func_020b2a64(&m.sub);
    } else {
        data_021f4bac[idx].hi = 0;
        m.a = 0;
        m.b = idx;
        g = data_020ccf94;
        func_02073820(g);
        func_020737f0(g, &m, 1);
        func_02073770(g, 0x23, 0);
    }
}
