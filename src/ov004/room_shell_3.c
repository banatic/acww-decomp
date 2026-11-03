/* room_shell_3: 6 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022321b8 @ 0x022321b8, 0xb4 bytes, Thumb
 * func_ov004_02232104 @ 0x02232104, 0xb4 bytes, Thumb
 * func_ov004_022320d8 @ 0x022320d8, 0x2c bytes, Thumb
 * func_ov004_022320ac @ 0x022320ac, 0x2c bytes, Thumb
 * func_ov004_02232080 @ 0x02232080, 0x2c bytes, Thumb
 * func_ov004_02232054 @ 0x02232054, 0x2c bytes, Thumb
 */

#include "types.h"

extern char *data_ov004_022589fc;
extern int func_ov004_022327a0(void *, void *, int, int);
extern int func_020b6730(void);
extern void func_0200467c(int);
extern u16 *func_ov004_022329c0(void *);
extern int func_ov004_02232514(void *, void *, int, int);
extern u16 *func_ov004_02232734(void *);
extern char data_ov004_022589ec[];
extern void *func_ov004_02232738(void *p);
extern void *func_ov004_022329c4(void *p);

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
                    func_0200467c(0x50);
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
                return ((char *) data_ov004_022589ec);
            }
        }
    }
    return ((char *) data_ov004_022589ec);
}

void *func_ov004_02232104(u16 *self, int p1, int p2)
{
    int ok = 0;
    u16 v = *self;
    if (v >= 0x1144 && v <= 0x1187) {
        ok = 1;
    }
    if (ok != 0 || (v >= 0x1188 && v <= 0x11a7)) {
        char *g = data_ov004_022589fc;
        if (g != 0) {
            if (func_ov004_02232514(g + 0x1228, self, *(int *) (g + 0xac), p1) != 0) {
                u16 *r;
                u16 w;
                if (p2 != 0 && func_020b6730() != 0) {
                    func_0200467c(0x50);
                }
                r = func_ov004_02232734(data_ov004_022589fc + 0x1228);
                ok = 0;
                w = *r;
                if (w >= 0x1144 && w <= 0x1187) {
                    ok = 1;
                }
                if (ok != 0) {
                    return func_ov004_02232734(data_ov004_022589fc + 0x1228);
                }
                return ((char *) data_ov004_022589ec);
            }
        }
    }
    return ((char *) data_ov004_022589ec);
}

void *func_ov004_022320d8(void)
{
    char *p = data_ov004_022589fc;
    if (p != 0) {
        return func_ov004_02232738(p + 0x1228);
    }
    return data_ov004_022589ec;
}

void *func_ov004_022320ac(void)
{
    char *p = data_ov004_022589fc;
    if (p != 0) {
        return (unsigned short *) func_ov004_02232734(p + 0x1228);
    }
    return data_ov004_022589ec;
}

void *func_ov004_02232080(void)
{
    char *p = data_ov004_022589fc;
    if (p != 0) {
        return func_ov004_022329c4(p + 0x128);
    }
    return data_ov004_022589ec;
}

void *func_ov004_02232054(void)
{
    char *p = data_ov004_022589fc;
    if (p != 0) {
        return (unsigned short *) func_ov004_022329c0(p + 0x128);
    }
    return data_ov004_022589ec;
}
