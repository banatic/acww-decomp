/* func_0209b6c0 @ 0x0209b6c0, 0x90 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0204bcdc(u16 *p);
extern int func_0204bc64(u16 *p);
extern int func_020539e4(u16 *p);
extern int func_02053cf0(int t);
extern int func_02053cbc(int t);
extern int func_02053a88(u16 *p);
extern int func_02053b6c(u16 *p);
extern int func_02053c68(u16 *p);

int func_0209b6c0(u16 *p, int kind, int val)
{
    int res;
    int t;

    res = 0;
    if (func_0204bcdc(p) != 0) {
        switch (kind) {
            case 0:
                if (val == func_020539e4(p)) {
                    res = 2;
                }
                break;
            case 1:
                t = func_0204bc64(p);
                if (val == func_02053cf0(t)) {
                    res = 1;
                }
                if (val == func_02053cbc(t)) {
                    res++;
                }
                break;
            case 2:
                if (val == func_02053a88(p)) {
                    res = 2;
                }
                break;
            case 3:
                if (val == func_02053b6c(p)) {
                    res = 2;
                }
                break;
            case 4:
                if (val == func_02053c68(p)) {
                    res = 2;
                }
                break;
        }
    }
    return res;
}
