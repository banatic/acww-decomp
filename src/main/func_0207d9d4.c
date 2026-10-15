/* func_0207d9d4 @ 0x0207d9d4, 0xf4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern unsigned int func_0207f1c8(void *a);
extern void *func_0209b5ec(void *);
extern int func_0208150c(void *a);
extern int func_02003704(int a);
extern int func_0209c370(void *a);
extern int func_0209c380(void *a);
extern void *func_0209bfe8(void *a);
extern void *func_02080814(void *a);
extern int func_0209dffc(void *a);
extern int func_0209e350(void *a, void *b);
extern int func_0209c1c0(void *a, void *b);
extern void *func_0209bfec(void *a);
extern void MI_CpuCopy8(void *a, void *b, int c);
extern void func_0209e29c(void *a, int b);
extern int func_0209bf28(void *a, void *b);
extern void func_0209bf80(void *a, void *b);

void func_0207d9d4(void *self, void *a)
{
    void *r5, *r6, *r7;
    int limit, val, d, loop;
    u32 local[2];

    r5 = func_0209b5ec((void *) func_0207f1c8(self));

    if (func_02003704(func_0208150c(self)) == 0) {
        return;
    }
    if (func_0209c370(r5) == 0) {
        return;
    }
    if (func_0209c380(r5) == 0) {
        return;
    }

    r6 = func_0209bfe8(r5);
    r7 = func_02080814(self);

    if (func_0209dffc(r6) != 0) {
        return;
    }
    if (r7 == 0) {
        return;
    }

    d = func_0209e350(r6, a);
    if (d < 0) {
        d = -d;
    }
    limit = d / 0x5a0;
    if (limit <= 0) {
        return;
    }

    if (func_0209c1c0(r5, a) != 0) {
        local[0] = 0;
        local[1] = 0;
        loop = limit;

        MI_CpuCopy8(func_0209bfec(r5), local, 8);

        d = func_0209e350(local, r6);
        if (d < 0) {
            d = -d;
        }
        val = d / 0x5a0;

        if (val < 7) {
            func_0209e29c(local, 6);
            d = func_0209e350(local, a);
            if (d < 0) {
                d = -d;
            }
            loop = d / 0x5a0;
        }

        while (loop > 0) {
            if (func_0209bf28(r5, r7) == 0) {
                break;
            }
            loop--;
        }

        func_0209bf80(r5, r7);
    }

    func_0209e29c(r6, limit);
}
