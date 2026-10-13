/* func_0202ccc0 @ 0x0202ccc0, 0xb8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct Slot {
    void *p;
} Slot;

extern u8 data_021c1ce8[3];
extern void MI_CpuFill8(void *, int, int);
extern int func_0204fb08(u8);
extern int func_0202cdf8(int, Slot *);
extern int func_020644cc(int);
extern int func_0202cd78(int, int, int, Slot *);

int func_0202ccc0(int a, int b, int *c, int key, Slot **pp, u8 first, u8 last8)
{
    int result;
    int last;
    int lim;
    u8 *flag;
    Slot *e;
    int n;
    int idx;
    int j;
    int i;
    int k;

    e = *pp;
    result = 0;
    if (e != 0) {
        last = 3;
        n = 0;
        MI_CpuFill8(data_021c1ce8, n, last);
        j = first;
        lim = last8;
        while (j <= lim) {
            idx = func_0204fb08((u8) j);
            flag = &data_021c1ce8[idx];
            if (data_021c1ce8[idx] == 0 && idx != last) {
                if (func_0202cdf8(key, &e[idx]) > 0) {
                    *flag = 1;
                    n++;
                }
                last = idx;
            }
            j++;
        }
        if (n > 0) {
            k = func_020644cc(n);
            for (i = 0; i < 3; i++) {
                if (data_021c1ce8[i] == 1) {
                    if (k == 0) {
                        result = func_0202cd78(a, b, key, e);
                        *c = i;
                        break;
                    }
                    k--;
                }
                e += 1;
            }
        }
    }
    return result;
}
