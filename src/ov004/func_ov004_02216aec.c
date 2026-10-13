/* func_ov004_02216aec @ 0x02216aec, 0xe4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov004_0220ffa4(void *s);
extern void func_0209def4(void *p);
extern int func_0209d324(int h);
extern int func_02055140(void *p, int a);
extern int func_ov004_0220e220(void *p);
extern int func_ov004_0220da04(int a, int b);
extern void func_02055060(void *p, int a, int b, int c, int d, int e);
extern void func_02055050(void *p);
extern void func_ov004_0221041c(void *s, int a, int b, int c, int d);

int func_ov004_02216aec(char *s)
{
    int h;
    int st;
    h = func_ov004_0220ffa4(s);
    func_0209def4(s + 0x848);
    *(u16 *) (s + 0x846) = *(u16 *) (s + 0x848);
    *(char *) (s + 0x844) = -1;
    st = *(int *) (s + 0x780);
    if (st == 0x10) {
        if (func_02055140(s + 0x538, func_0209d324(h)) != 0) {
            func_02055060(s + 0x538, func_ov004_0220da04(func_ov004_0220e220(s + 0x6cc), 0), 1, 0x1000, 0, 0);
            func_02055050(s + 0x538);
        }
    } else if (st == 0x11) {
        if (func_02055140(s + 0x538, func_0209d324(h)) != 0) {
            func_02055060(s + 0x538, func_ov004_0220da04(func_ov004_0220e220(s + 0x6cc), 0), 0, 0x1000, 0, 0);
            func_02055050(s + 0x538);
        }
    } else if (st == 0x2b) {
        func_ov004_0221041c(s, 0, 0, 0x1000, 0);
    }
    return 1;
}
