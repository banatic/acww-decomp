/* func_02047ac0 @ 0x02047ac0, 0x108 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02047ac0 {
    u16 id;
} UnkStruct_02047ac0;

typedef struct Pair {
    int a;
    int b;
} Pair;

extern UnkStruct_02047ac0 *func_0204f5e0(void *, int, int, int, int, int);
extern int func_0204b910(UnkStruct_02047ac0 *);
extern void func_0204f800(int *, int *, int, int, int, int);
extern int func_020644cc(int);
extern void func_0204a25c(void *, int, int, int, int);
extern void func_020466a0(int, int);

void func_02047ac0(void *self, void *a1, int a2, int a3)
{
    int cnt;
    int o1;
    int o2;
    Pair arr[256];
    Pair *pp;
    int x;
    int y;
    int n;
    int k;
    int r;
    UnkStruct_02047ac0 *e;
    int t;

    pp = arr;
    do {
        pp->a = 0;
        pp->b = 0;
        pp++;
    } while (pp != arr + 256);
    n = 0;
    cnt = 0;
    for (y = 0; y < 16; y++) {
        for (x = 0; x < 16; x++) {
            e = func_0204f5e0(a1, a2 + 1, a3 + 1, x, y, 0);
            if (e) {
                t = (e->id >= 0x5d && e->id <= 0x61);
                if (t && func_0204b910(e)) {
                    func_0204f800(&o1, &o2, a2 + 1, a3 + 1, x, y);
                    arr[n].a = o1;
                    arr[n].b = o2;
                    n++;
                } else if (e->id == 0x6d) {
                    cnt++;
                }
            }
        }
    }
    for (k = 3 - cnt; k != 0; k--) {
        if (n > 0) {
            r = func_020644cc(n);
            func_0204a25c(a1, arr[r].a, arr[r].b, 0x6d, 0);
            func_020466a0(arr[r].a, arr[r].b);
            arr[r].a = arr[n - 1].a;
            arr[r].b = arr[n - 1].b;
            n--;
        }
    }
}
