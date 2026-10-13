/* func_02073fdc @ 0x02073fdc, 0x9c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u16 *data_020ccf94;

extern u16 func_0207315c(u16 *);
extern int func_02073de4(u16 *);
extern void func_02073180(u16 *, u16);
extern void func_02073168(u16 *, u16);
extern u16 func_02073174(u16 *);
extern void func_02073044(void);
extern int func_020ec260(void);
extern int func_020ec920(void);
extern u16 func_020ec1f8(void);

int func_02073fdc(int a)
{
    u16 *p = data_020ccf94;
    u16 n = func_0207315c(p);
    u16 v;

    if (n != 0) {
        if (func_02073de4(p) != 0) {
            p = data_020ccf94;
            func_02073180(p, 0);
            func_02073168(p, 0);
        } else {
            u16 c = func_02073174(p);
            if (c >= n) {
                return 1;
            }
            func_02073180(p, (u16) (c + 1));
        }
    }

    if (a < 0) {
        goto neg;
    }
    v = (u16) a;
    if (func_020ec260() == 0) {
        goto chk;
    }
    if (a <= 0) {
        goto ret0;
    }
    func_02073044();
    if (func_020ec920() != 0) {
        goto ret0;
    }
    return 1;
chk:
    if ((v & func_020ec1f8()) == v) {
        goto ret0;
    }
    return 1;
neg:
    if (func_020ec1f8() != 0) {
        goto ret0;
    }
    return 1;
ret0:
    return 0;
}
