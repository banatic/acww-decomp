/* func_ov066_02269320 @ 0x02269320, 0xd0 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct Mac {
    u8 b[6];
} Mac;

int func_ov066_02268024(const Mac *m);
void func_ov066_02266800(int kind, int idx);

void func_ov066_02269320(Mac *cur, Mac *next)
{
    u16 i;
    int zero = 0;
    int one = 1;
    for (i = 0; i < 0x10; i = (u16) (i + 1)) {
        Mac *pc = &cur[i];
        Mac *pn = &next[i];
        int had = func_ov066_02268024(pc);
        int has = func_ov066_02268024(pn);
        cur[i] = next[i];
        if (had == 0 && has != 0) {
            func_ov066_02266800(zero, i);
        }
        if (had != 0 && has == 0) {
            func_ov066_02266800(one, i);
        }
    }
}
