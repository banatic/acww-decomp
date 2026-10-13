/* func_ov004_0221cb28 @ 0x0221cb28, 0xec bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int a, b;
} UnkStruct_0221cb28;

extern void func_02063ccc(UnkStruct_0221cb28 *t, int a, int b);
extern void func_02063cc8(UnkStruct_0221cb28 *t);
extern void func_020638d4(u16 *dst, UnkStruct_0221cb28 *t, int a, int b, int c, int d, int e);
extern int func_020644cc(int n);
extern int func_020984e8(void);
extern void func_020630bc(u16 *dst, int v, int b);

u16 func_ov004_0221cb28(int n)
{
    // DECLS
    u16 a[5];
    UnkStruct_0221cb28 t[4];
    u16 r;
    // ENDDECLS

    if (n <= 0) {
        func_02063ccc(&t[0], 1, 0);
        func_020638d4(&a[1], &t[0], 0, 0, 1, 1, 0);
        r = a[1];
        func_02063cc8(&t[0]);
        return r;
    }
    if (n <= 0x3f) {
        if (func_020644cc(2) == 0) {
            func_02063ccc(&t[1], 0, 0);
            func_020638d4(&a[2], &t[1], 0, 0, 1, 1, 0);
            r = a[2];
            func_02063cc8(&t[1]);
            return r;
        }
        func_02063ccc(&t[2], 2, 0);
        func_020638d4(&a[3], &t[2], 0, 0, 1, 1, 0);
        r = a[3];
        func_02063cc8(&t[2]);
        return r;
    }
    func_020630bc(&a[0], func_020984e8(), 0);
    if (a[0] == 0xfff1) {
        func_02063ccc(&t[3], 0, 0);
        func_020638d4(&a[4], &t[3], 0, 0, 1, 1, 0);
        r = a[4];
        func_02063cc8(&t[3]);
        return r;
    }
    return a[0];
}
