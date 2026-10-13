/* func_0207a02c @ 0x0207a02c, 0xec bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0204c7c0(void);
extern int func_0207b3dc(int a);
extern int func_0207cf74(int id);
extern int func_0207d6c4(void *p);
extern int func_020644cc(int n);

void func_0207a02c(int p0, u8 *out, int *count, s8 *list, char *base, int limit)
{
    u8 mask;
    int n;
    s8 *p;
    int id;
    int self;
    int i;
    int k;
    s8 *q;
    int j;
    int t;
    int b;

    mask = 0;
    n = 0;
    self = func_0207b3dc(func_0204c7c0() + 0x9284);
    p = list;
    for (i = 0; i < 8; i++) {
        id = *p;
        if (func_0207cf74(id) != 0) {
            if (id != self) {
                id = id * 0x7ec;
                if (func_0207d6c4(base + id) != 0) {
                    mask = (u8) (mask | (1 << i));
                    n++;
                    if (n >= 6) {
                        break;
                    }
                }
            }
        }
        p++;
    }
    while (n > 0 && *count < limit) {
        k = func_020644cc(n);
        q = list;
        for (j = 0; j < 8; j++) {
            b = *q;
            t = mask;
            t = t >> j;
            t = t & 1;
            if (t != 0) {
                if (k == 0) {
                    out[*count] = (u8) b;
                    *count = *count + 1;
                    *q = -1;
                    mask = (u8) (mask & ~(1 << j));
                    break;
                }
                k--;
            }
            q++;
        }
        n--;
    }
}
