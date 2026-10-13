/* func_02043368 @ 0x02043368, 0x11c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x;
    int y;
} Pt;
typedef struct {
    int e[9];
} Row;
typedef struct {
    u16 unk_00;
} Res;
typedef struct {
    u8 pad_00[0x68];
    int unk_68;
} UnkStruct_02043368;
typedef struct {
    u8 pad_00[0x5c];
    u8 unk_5C[0x8e - 0x5c];
    short unk_8E;
} UnkStruct_02043368_2;

extern void *data_021c80bc;
extern UnkStruct_02043368 *data_020ccf94;
extern Row data_020cb638[];
extern u8 data_020ca634[];

extern UnkStruct_02043368_2 *func_020961a8(int);
extern int func_020644e4(short);
extern void func_0204f818(volatile int *, volatile int *, u8 *);
extern Res *func_02043484(void *, void *, int, int, Pt *);
extern int func_02045d80(Pt *, int);
extern int func_02045ac4(Pt *, int);
extern int func_020b6660(void);
extern int func_02051d44(int, int);

int func_02043368(void *a0, volatile Pt *a1, u8 *a2)
{
    int ret;
    int *p;
    int i;
    void *ptr;
    UnkStruct_02043368 *g2;
    int w;
    Pt tmp;
    Pt pt;
    Pt pt2;
    UnkStruct_02043368_2 *obj;
    int v;
    int b;
    int nx;
    int ny;
    Res *res;
    int n;

    ptr = data_021c80bc;
    obj = func_020961a8(4);
    ret = 0;
    if (ptr != 0 && obj != 0) {
        p = data_020cb638[func_020644e4(obj->unk_8E)].e;
        func_0204f818(&a1->x, &a1->y, obj->unk_5C);
        i = 0;
        g2 = data_020ccf94;
        w = i;
        for (; i < 9; i++) {
            v = *p;
            b = data_020ca634[v];
            nx = a1->x + ((b >> 4) - 8);
            ny = a1->y + ((b & 0xf) - 8);
            tmp.x = a1->x;
            tmp.y = a1->y;
            res = func_02043484(a0, ptr, nx, ny, &tmp);
            if (res != 0 && res->unk_00 == 0xfff1) {
                pt.x = nx;
                pt.y = ny;
                if (func_02045d80(&pt, w) < 0) {
                    n = g2->unk_68;
                    pt2.x = nx;
                    pt2.y = ny;
                    if (func_02045ac4(&pt2, n)) {
                        a1->x = nx;
                        a1->y = ny;
                        if (a2) {
                            *a2 = 0;
                        }
                        ret = 1;
                        break;
                    }
                }
            }
            if (func_020b6660() == 0) {
                if (func_02051d44(nx, ny)) {
                    a1->x = nx;
                    a1->y = ny;
                    if (a2) {
                        *a2 = 1;
                    }
                    ret = 1;
                    break;
                }
            }
            p++;
        }
    }
    return ret;
}
