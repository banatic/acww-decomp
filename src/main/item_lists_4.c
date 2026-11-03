/* item_lists_4: 11 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02063ccc @ 0x02063ccc, 0x6 bytes, Thumb
 * func_02063cc8 @ 0x02063cc8, 0x2 bytes, Thumb
 * func_02063cc4 @ 0x02063cc4, 0x4 bytes, Thumb
 * func_02063cc0 @ 0x02063cc0, 0x4 bytes, Thumb
 * func_02063cb4 @ 0x02063cb4, 0xc bytes, Thumb
 * func_02063ca8 @ 0x02063ca8, 0xc bytes, Thumb
 * func_02063ca0 @ 0x02063ca0, 0x6 bytes, Thumb
 * func_02063c3c @ 0x02063c3c, 0x62 bytes, Thumb
 * func_02063c24 @ 0x02063c24, 0x16 bytes, Thumb
 * func_02063bb4 @ 0x02063bb4, 0x6e bytes, Thumb
 * func_02063b98 @ 0x02063b98, 0x1c bytes, Thumb
 */

#include "types.h"

extern unsigned short func_0204bc50(int a, int b);
extern unsigned short func_0204bd20(int, int);
extern int func_0204bcdc(void *);
extern int func_0204bc64(void *);
extern int func_020996ac(int a);
extern int func_0203cdcc(int a, int b);

void func_02063ccc(int *p, int a, int b)
{
    p[0] = a;
    p[1] = b;
}

void func_02063cc8(void *object) {}

int func_02063cc4(int *p0)
{
    return p0[0];
}

int func_02063cc0(int *p0)
{
    return p0[1];
}

void func_02063cb4(int a)
{
    func_0204bc50(a, 0);
}

void func_02063ca8(int a, int b, int c)
{
    func_0204bd20(a, 4);
}

int func_02063ca0(void)
{
    return -1;
}

static __inline int EqA(void *a, void *b)
{
    if (func_0204bc64(a) == func_0204bc64(b)) {
        return 1;
    }
    return 0;
}

static __inline int EqB(u16 a, u16 b)
{
    if (a == b) {
        return 1;
    }
    return 0;
}

int func_02063c3c(u16 *target, u16 *arr, unsigned int count)
{
    unsigned int i;
    int r;

    for (i = 0; i < count; i++) {
        if (func_0204bcdc(arr)) {
            r = EqA(arr, target);
        } else {
            r = EqB(*arr, *target);
        }
        if (r != 0) {
            return i;
        }
        arr++;
    }
    return -1;
}

int func_02063c24(int a, int b)
{
    int result = 0;
    if (a == -1 || a == 4 || a == b) {
        result = 1;
    }
    return result;
}

int func_02063bb4(int month, unsigned int day)
{
    switch (month) {
        case 1:
            return 3;
        case 2:
            if (day > 0x18) {
                return 0;
            }
            return 3;
        case 3:
        case 4:
            return 0;
        case 5:
            if (day > 0x1a) {
                return 1;
            }
            return 0;
        case 6:
        case 7:
            return 1;
        case 8:
            if (day > 0x1a) {
                return 2;
            }
            return 1;
        case 9:
        case 10:
            return 2;
        case 11:
            if (day > 0x1a) {
                return 3;
            }
            return 2;
        case 0:
        default:
            return 3;
    }
}

int func_02063b98(int a, int b)
{
    int result;
    if (a) {
        result = func_0203cdcc(func_020996ac(a), b);
    } else {
        result = 0;
    }
    return result;
}
