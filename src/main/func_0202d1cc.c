/* func_0202d1cc @ 0x0202d1cc, 0xd4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct Entry {
    int unk_00;
    u8 unk_04;
    u8 pad_05[3];
} Entry;

extern u8 data_021c1d20[6];

extern void MI_CpuFill8(void *, int, int);
extern int func_02061798(u8);
extern int func_0202d34c(int, int, u8, int, int);
extern int func_020644cc(int);
extern int func_0202d2a0(int, int, int, int, u8, int, int);

int func_0202d1cc(int a, int b, int *c, int d, Entry *e, int f, int g, u8 h, u8 i)
{
    int result;
    int last;
    int lim;
    u8 *flag;
    int n;
    int idx;
    int j;
    int k;
    int m;

    n = 0;
    result = 0;
    if (e != 0) {
        last = 6;
        MI_CpuFill8(data_021c1d20, n, last);
        j = h;
        lim = i;
        while (j <= lim) {
            idx = func_02061798((u8) j);
            flag = &data_021c1d20[idx];
            if (data_021c1d20[idx] == 0 && idx != last) {
                if (func_0202d34c(d, e[idx].unk_00, e[idx].unk_04, f, g) > 0) {
                    *flag = 1;
                    n++;
                }
                last = idx;
            }
            j++;
        }
        if (n > 0) {
            k = func_020644cc(n);
            for (m = 0; m < 6; m++) {
                if (data_021c1d20[m] != 0) {
                    if (k == 0) {
                        result = func_0202d2a0(a, b, d, e->unk_00, e->unk_04, f, g);
                        *c = m;
                        break;
                    }
                    k--;
                }
                e++;
            }
        }
    }
    return result;
}
