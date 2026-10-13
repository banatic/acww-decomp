/* func_ov003_0221a538 @ 0x0221a538, 0xd0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    s16 dx;
    s16 dy;
} UnkStruct_0221a538;
typedef struct {
    int a, b, c;
} Pt;

extern int data_021c80bc;
extern UnkStruct_0221a538 data_ov003_0223660c[];

extern u16 func_0204bb14(void *a);
extern void func_0204f818(int *x, int *y, void *pos);
extern void func_0204f794(Pt *p, int x, int y);
extern int func_ov003_0221a68c(Pt *p);
extern int func_020644cc(int n);
extern int func_ov003_0221a608(void *a, Pt *p, int c);

int func_ov003_0221a538(void *a, void *pos, int c)
{
    volatile u16 v;
    int x, y;
    Pt tmp;
    Pt tmp2;
    u8 mask;
    int n;
    unsigned int i;
    int k;
    int j;
    unsigned int m;

    if (data_021c80bc != 0) {
        v = func_0204bb14(a);
        func_0204f818(&x, &y, pos);
        mask = 0;
        n = 0;
        for (i = 0; i < 8; i++) {
            UnkStruct_0221a538 *e = &data_ov003_0223660c[i];
            func_0204f794(&tmp, x + e->dx, y + e->dy);
            if (func_ov003_0221a68c(&tmp) != 0) {
                mask = (u8) (mask | (1 << i));
                n++;
            }
        }
        if (n != 0) {
            k = func_020644cc(n);
            j = 0;
            for (m = 0; m < 8; m++) {
                if (((mask >> m) & 1) != 0) {
                    if (j == k) {
                        func_0204f794(&tmp2, x + data_ov003_0223660c[m].dx, y + data_ov003_0223660c[m].dy);
                        if (func_ov003_0221a608(a, &tmp2, c) != 0) {
                            return 1;
                        } else {
                            return 0;
                        }
                    }
                    j++;
                }
            }
        }
    }
    return 0;
}
