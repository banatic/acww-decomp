/* func_02029a18 @ 0x02029a18, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_020984e8(void);
extern int func_02099734(int a);
extern u16 *func_02098f48(int h, int a);
extern int func_02098e8c(int h, int i);
extern int func_0204bcdc(u16 *p);
extern int func_0204bc64(u16 *p);

u16 func_02029a18(u16 *key)
{
    int h;
    u16 *p;
    int i;
    u16 mask;
    unsigned int ok;
    int r;

    h = func_02099734(func_020984e8());
    p = func_02098f48(h, 0);
    mask = 0;
    for (i = 0; i < 15; i++) {
        if (func_02098e8c(h, i) == 0) {
            if (func_0204bcdc(p) != 0) {
                r = func_0204bc64(p);
                ok = (r == func_0204bc64(key)) ? 1 : 0;
            } else {
                ok = (*p == *key) ? 1 : 0;
            }
            if (ok != 0) {
                mask = mask | (1 << i);
            }
        }
        p++;
    }
    return mask;
}
