/* func_ov110_0229d1b8 @ 0x0229d1b8, 0x1d0 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov110_0229d0fc(void);
extern int func_ov110_0229d078(void *a, void *b);
extern int func_ov110_0229d0b8(void *a, void *b);
extern int func_ov094_02299a54(void);
extern int func_ov094_02299b04(int id);
extern int func_0206fca4(void);
extern int MB_GetBeaconRecvStatus(void);

int func_ov110_0229d1b8(void *a, void *b)
{
    volatile u16 id;
    int v;

    if (func_ov110_0229d0fc() != 0) {
        return 0;
    }
    if (func_ov110_0229d078(a, b) != 0) {
        return 1;
    }
    v = func_ov110_0229d0b8(a, b);
    if (func_ov094_02299a54() != 0) {
        return 1;
    }
    id = (u16) v;
    switch (func_0206fca4()) {
        case 0x1e: {
            unsigned int ok = 0;
            u16 hi = id;
            u16 lo = id;
            if (lo >= 0x1492 && hi <= 0x14fd) {
                ok = 1;
            }
            if (ok > 0) {
                return 1;
            }
            if ((hi >= 0x11a8 && hi <= 0x12a7) || (hi >= 0x13c8 && hi <= 0x1407) || (hi >= 0x13a8 && hi <= 0x13c7) ||
                (hi >= 0x1408 && hi <= 0x1428) || (hi >= 0x1431 && hi <= 0x1470) || (hi >= 0x1471 && hi <= 0x1491) ||
                (hi >= 0x1380 && hi <= 0x139f)) {
                return 0;
            }
            return 1;
        }
        case 0x1d: {
            unsigned int ok = 0;
            u16 hi = id;
            u16 lo = id;
            if (lo >= 0x1492 && hi <= 0x14fd) {
                ok = 1;
            }
            if (ok > 0) {
                return 1;
            }
        }
            if (MB_GetBeaconRecvStatus() == 0) {
                unsigned int ok = 0;
                u16 hi = id;
                u16 lo = id;
                if (lo >= 0x1531 && hi <= 0x153a) {
                    ok = 1;
                }
                if (ok > 0) {
                    return 1;
                }
            }
            return 0;
        case 0x1f:
            return 1;
        case 0x20:
            if (func_ov094_02299b04(v) != 0) {
                unsigned int ok = 0;
                u16 hi = id;
                u16 lo = id;
                if (lo >= 0x1531 && hi <= 0x153a) {
                    ok = 1;
                }
                if (ok || (hi >= 0x153b && hi <= 0x1541) || (hi >= 0x154a && hi <= 0x1553)) {
                    return 0;
                }
                return 1;
            }
            return 0;
    }
    return 0;
}
