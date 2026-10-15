/* func_ov003_02235f34 @ 0x02235f34, 0x84 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

int func_ov003_02235fec(void *self);
unsigned int func_020644cc(int count);
int func_ov003_0223605c(void *e, int *x, int *y);

int func_ov003_02235f34(char *self, int *px, int *py)
{
    unsigned int i;
    unsigned int j;
    int sel;
    int count;
    int n;
    int x;
    int y;
    char *e;

    if ((count = func_ov003_02235fec(self)) != 0) {
        sel = func_020644cc(count);
        n = 0;
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                e = self + i * 0x88 + j * 0x22;
                if (*(u16 *) (e + 0x20) != 0) {
                    if (sel == n) {
                        if (func_ov003_0223605c(e, &x, &y) != 0) {
                            *px = ((j + 1) << 4) + x;
                            *py = ((i + 1) << 4) + y;
                            return 1;
                        }
                        return 0;
                    }
                    n++;
                }
            }
        }
    }
    return 0;
}
