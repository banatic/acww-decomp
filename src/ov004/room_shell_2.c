/* room_shell_2: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02231c7c @ 0x02231c7c, 0x7c bytes, Thumb
 * func_ov004_02231b98 @ 0x02231b98, 0xe4 bytes, Thumb
 */

#include "types.h"

typedef union {
    unsigned short value;
    struct {
        unsigned short r : 5, g : 5, b : 5, a : 1;
    } bits;
} Color;

extern char *data_021c80bc;
extern void func_ov004_0221ad0c(int *, int, int, int);
extern unsigned char *func_020ba4a0(void);
extern short func_020bbf00(int);

void func_ov004_02231c7c(void *receiver)
{
    int v[3];
    char *o, *e;
    unsigned i;
    int a, b, c;
    char *q = data_021c80bc;
    char *r;
    if (*(char **) (q + 4) > (char *) 0 && *(char **) (q + 8) > (char *) 0 && *(char **) q != 0) {
        r = *(char **) q;
    } else {
        r = 0;
    }
    o = *(char **) (r + 0x20);
    if (o == 0) {
        return;
    }
    e = *(char **) (o + 0x28);
    if (e == 0) {
        return;
    }
    if (*(unsigned *) (o + 0x2c) == 0) {
        return;
    }
    for (i = 0; i < *(unsigned *) (o + 0x2c); i++) {
        c = (*(s16 *) (e + 4) << 12) >> 4;
        b = (*(s16 *) (e + 2) << 12) >> 4;
        a = (*(s16 *) (e + 0) << 12) >> 4;
        v[0] = a;
        v[1] = b;
        v[2] = c;
        func_ov004_0221ad0c(v, (*(s16 *) (e + 6) << 12) >> 4, (*(u8 *) (e + 8) << 30) >> 16, *(u8 *) (e + 9));
        e += 0xa;
    }
}

short func_ov004_02231b98(void *receiver)
{
    unsigned char *owner = func_020ba4a0();
    // Keep the observed halfword store/reload before the color copy.
    struct {
        volatile unsigned short temp;
        Color result, add;
    } sample;
    sample.result.value = 0xffff;
    if (owner) {
        int r, g, b;
        sample.temp = func_020bbf00(0);
        sample.add.value = sample.temp;
        sample.result.value = *(unsigned short *) (owner + 10);
        r = sample.result.bits.r + (int) sample.add.bits.r / 3;
        g = sample.result.bits.g + (int) sample.add.bits.g / 3;
        b = sample.result.bits.b + (int) sample.add.bits.b / 3;
        if (r > 31) {
            r = 31;
        } else if (r < 0) {
            r = 0;
        }
        if (g > 31) {
            g = 31;
        } else if (g < 0) {
            g = 0;
        }
        if (b > 31) {
            b = 31;
        } else if (b < 0) {
            b = 0;
        }
        sample.result.bits.r = r;
        sample.result.bits.g = g;
        sample.result.bits.b = b;
    }
    return *(short *) &sample.result;
}
