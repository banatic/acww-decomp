/* func_020637d0 @ 0x020637d0, 0xb4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02063414(u16 *out, int a3, int a4, u16 *arr, int i, int a5, int a6, int a7, int a8, int a9);
extern int func_0204bcdc(u16 *);
extern int func_0204bc64(u16 *);

static __inline int EqA(u16 *a, u16 *b)
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

int func_020637d0(u16 *arr, unsigned int count, int a3, int a4, int a5, int a6, int a7, int a8, int a9)
{
    int result;
    int flag;
    int i;
    u16 tmp[2];

    result = 1;

    for (i = 0; i < count; i++) {
        func_02063414(tmp, a3, a4, arr, i, a5, a6, a7, a8, a9);
        arr[i] = tmp[0];

        if (func_0204bcdc(&arr[i]) != 0) {
            tmp[1] = 0xfff1;
            flag = EqA(&arr[i], &tmp[1]);
        } else {
            flag = EqB(arr[i], 0xfff1);
        }

        if (flag != 0) {
            result = 0;
        }
    }

    return result;
}
