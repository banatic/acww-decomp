/* func_020aed60 @ 0x020aed60, 0x1c8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u32 data_021f4a00;
extern u16 data_021f4abc[7];
extern u16 data_021f4a20;
extern u16 data_021f4a2c;
extern u16 data_021f4a38;
extern u16 data_021f4a50;
extern u16 data_021f4a5c;
extern u16 data_021f4a74;
extern u16 data_021f4a8c;
extern void func_020051b0(void *);
extern void __register_global_object(void *, void *, void *);
extern int func_020af028(u8 *);
extern u32 func_020aefec(u8 *);
extern void func_020b00fc(void *, void *, int, int, u32, int, int);
extern int func_0204bcdc(u16 *);
extern u32 func_0204bc64(void *);
extern int func_020644cc(int);
inline static int EqA(u16 *p, u16 *q)
{
    if (func_0204bc64(p) == func_0204bc64(q)) {
        return 1;
    }
    return 0;
}

inline static int EqB(u16 x, u16 y)
{
    if (x == y) {
        return 1;
    }
    return 0;
}

inline char *inline_fn(char *arg0, u32 arg1)
{
    return arg0 + ((arg1 + func_020644cc(2)) * 2);
}

void func_020aed60(u8 *a, u32 *b)
{
    int mode;
    int count;
    int result;
    u32 i;
    u32 start;
    u16 val;
    u16 *base;
    u16 *p;
    u16 *q;
    if ((data_021f4a00 & 1) == 0) {
        data_021f4abc[0] = 0x1369;
        __register_global_object((void *) (&data_021f4abc[0]), (((void *) func_020051b0)), (void *) (&data_021f4a20));
        data_021f4abc[1] = 0x1378;
        __register_global_object((void *) (&data_021f4abc[1]), (((void *) func_020051b0)), (void *) (&data_021f4a2c));
        data_021f4abc[2] = 0x1376;
        __register_global_object((void *) (&data_021f4abc[2]), (((void *) func_020051b0)), (void *) (&data_021f4a38));
        data_021f4abc[3] = 0x1374;
        __register_global_object((void *) (&data_021f4abc[3]), (((void *) func_020051b0)), (void *) (&data_021f4a50));
        data_021f4abc[4] = 0x156c;
        __register_global_object((void *) (&data_021f4abc[4]), (((void *) func_020051b0)), (void *) (&data_021f4a5c));
        data_021f4abc[5] = 0x136b;
        __register_global_object((void *) (&data_021f4abc[5]), (((void *) func_020051b0)), (void *) (&data_021f4a74));
        data_021f4abc[6] = 0x137a;
        __register_global_object((void *) (&data_021f4abc[6]), (((void *) func_020051b0)), (void *) (&data_021f4a8c));
        data_021f4a00 |= 1;
    }
    if (func_020af028(a) == 0) {
        mode = -3;
    } else {
        mode = 0;
    }
    start = *b;
    func_020b00fc(a + 4, b, 0, mode + 7, func_020aefec(a), 0x25, 0);
    if (func_020af028(a) != 0) {
        goto after_loop;
    }
    count = 0;
    i = 0;
    base = (u16 *) (a + (start * 2));
    while (i < func_020aefec(a)) {
        p = (u16 *) ((a + 4) + ((start + i) * 2));
        if (func_0204bcdc(p) != 0) {
            u16 tmp = 3;
            result = EqA(p, &tmp);
        } else {
            q = base + i;
            result = EqB(q[2], 3);
        }
        if (result != 0) {
            count++;
        }
        i++;
    }

    if (count == 0) {
        char *p_base = ((char *) a) + 4;
        *((u16 *) inline_fn(p_base, start)) = 3;
    }
after_loop:
    i = 0;

    base = (u16 *) (a + (start * 2));
    while (i < func_020aefec(a)) {
        p = (base + i) + 2;
        val = *p;
        *p = data_021f4abc[val];
        i++;
    }
}
