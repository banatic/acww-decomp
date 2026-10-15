/* func_ov003_02224140 @ 0x02224140, 0x64 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *data_021c80bc;
extern int func_020b6660(void);
extern int func_0204f538(void *h, volatile u16 *p, void *a, void *b, int k);
extern void func_0204f380(void *h, void *a, void *b);
extern int func_0204f31c(void *h, void *a, void *b);

void func_ov003_02224140(void *a, void *b, u16 id, int flag)
{
    void *h;
    volatile u16 t;
    func_020b6660();
    h = data_021c80bc;
    if (h) {
        t = 0xfff1;
        t = id;
        func_0204f538(h, &t, a, b, 0);
        if (id != 0xfff1 && flag != 0) {
            func_0204f380(h, a, b);
        } else {
            func_0204f31c(h, a, b);
        }
    }
}
