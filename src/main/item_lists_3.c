/* item_lists_3: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020638d4 @ 0x020638d4, 0x40 bytes, Thumb
 * func_020638b0 @ 0x020638b0, 0x24 bytes, Thumb
 * func_02063884 @ 0x02063884, 0x2a bytes, Thumb
 * func_020637d0 @ 0x020637d0, 0xb4 bytes, Thumb
 */

#include "types.h"

typedef struct {
    u32 x;
    u32 y;
} Pair;

extern void func_02063cc8(int *tmp);
extern int func_02063914(int, int, int, int, int, int, int, int, int);
extern void func_02063414(u16 *out, int a3, int a4, u16 *arr, int i, int a5, int a6, int a7, int a8, int a9);
extern int func_0204bcdc(u16 *);
extern int func_0204bc64(u16 *);

int func_020638b0(int a0, int a1, int a2, int a3, int a4, unsigned char a5, int a6, int a7);

void func_020638d4(unsigned short *out, int *inp, int value1, int value2, unsigned char byte_arg, int arg6, int arg7)
{
    int tmp[2];
    *out = 0xfff1;
    tmp[0] = inp[0];
    tmp[1] = inp[1];
    func_020638b0((int) out, 1, (int) tmp, value1, value2, byte_arg, arg6, arg7);
    func_02063cc8(tmp);
}

int func_020638b0(int a0, int a1, int a2, int a3, int a4, unsigned char a5, int a6, int a7)
{
    return func_02063914(a0, a1, a2, 1, a3, a4, a5, a6, a7);
}

void func_02063884(u32 arg0, Pair *arg1)
{
    Pair local;
    local.x = arg1->x;
    local.y = arg1->y;
    func_020638d4((unsigned short *) arg0, (int *) (&local), 0, 0, 1, 0, 0);
    func_02063cc8((int *) (&local));
}

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
