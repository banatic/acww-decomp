/* check_in_gate_5: 6 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222d5c0 @ 0x0222d5c0, 0x64 bytes, Thumb
 * func_ov004_0222d548 @ 0x0222d548, 0x78 bytes, Thumb
 * func_ov004_0222d53c @ 0x0222d53c, 0xc bytes, Thumb
 * func_ov004_0222d518 @ 0x0222d518, 0x24 bytes, Thumb
 * func_ov004_0222d4f4 @ 0x0222d4f4, 0x24 bytes, Thumb
 * func_ov004_0222d4d4 @ 0x0222d4d4, 0x20 bytes, Thumb
 */

#include "types.h"

typedef int (*Fn)(void *self, int k);

extern int func_ov004_0222c3c4(void *, int);
extern int func_02055140(void *, void *);
extern void func_02055060(void *, int, int, int, int, int);
extern void func_02055050(void *);
extern void *data_021c9b24;
extern int func_ov004_0222c3b4(void *, int);
extern int func_0205650c(void *, int, void *);
extern void func_02056478(void *, int, int, int, int);
extern void *func_02055e00(void *);
extern void func_020563dc(void *, void *);
extern void *data_ov004_0225827c;

int func_ov004_0222d5c0(char *self)
{
    if (func_ov004_0222c3c4(self + 0x1a4, 0) != 0) {
        if (func_02055140(self + 0xec, data_021c9b24) != 0) {
            func_02055060(self + 0xec, func_ov004_0222c3c4(self + 0x1a4, 0), 0, 0x1000, 0, 0);
            func_02055050(self + 0xec);
            return 1;
        }
    }
    return 0;
}

int func_ov004_0222d548(char *self)
{
    if (func_ov004_0222c3b4(self + 0x1a4, 0) != 0) {
        if (func_0205650c(self + 0x290, *(int *) (self + 0x148), data_021c9b24) != 0) {
            func_02056478(self + 0x290, func_ov004_0222c3b4(self + 0x1a4, 0), 0, 0x1000, 0);
            func_020563dc(self + 0x290, func_02055e00(self + 0xec));
            return 1;
        }
    }
    return 0;
}

void func_ov004_0222d53c(int value)
{
    (*(int *) &data_ov004_0225827c) = value;
}

int func_ov004_0222d518(void)
{
    void *p = data_ov004_0225827c;
    if (p != 0) {
        return (*(Fn **) p)[24](p, 1);
    }
    return 0;
}

int func_ov004_0222d4f4(void)
{
    void *p = data_ov004_0225827c;
    if (p != 0) {
        return (*(Fn **) p)[24](p, 3);
    }
    return 0;
}

int func_ov004_0222d4d4(void)
{
    // DECLS
    // ENDDECLS
    if (*(int *) ((char *) &data_ov004_0225827c) != 0x0 &&
        *(u8 *) ((char *) *(int *) ((char *) &data_ov004_0225827c) + 0x24c) == 0x2) {
        return 0x1;
    }
    return 0x0;
}
