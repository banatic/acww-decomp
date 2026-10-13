/* func_ov004_022321b8 @ 0x022321b8, 0xb4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern char *data_ov004_022589fc;
extern char data_ov004_022589ec;
extern int func_ov004_022327a0(void *, void *, int, int);
extern int func_020b6730(void);
extern void RtcSendPxiCommand(int);
extern u16 *func_ov004_022329c0(void *);

void *func_ov004_022321b8(u16 *self, int p1, int p2)
{
    int ok = 0;
    u16 v = *self;
    if (v >= 0x1100 && v <= 0x1143) {
        ok = 1;
    }
    if (ok != 0 || (v >= 0x1188 && v <= 0x11a7)) {
        char *g = data_ov004_022589fc;
        if (g != 0) {
            if (func_ov004_022327a0(g + 0x128, self, *(int *) (g + 0xac), p1) != 0) {
                u16 *r;
                u16 w;
                if (p2 != 0 && func_020b6730() != 0) {
                    RtcSendPxiCommand(0x50);
                }
                r = func_ov004_022329c0(data_ov004_022589fc + 0x128);
                ok = 0;
                w = *r;
                if (w >= 0x1100 && w <= 0x1143) {
                    ok = 1;
                }
                if (ok != 0) {
                    return func_ov004_022329c0(data_ov004_022589fc + 0x128);
                }
                return &data_ov004_022589ec;
            }
        }
    }
    return &data_ov004_022589ec;
}
