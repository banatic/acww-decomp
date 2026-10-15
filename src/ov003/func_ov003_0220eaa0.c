/* func_ov003_0220eaa0 @ 0x0220eaa0, 0xec bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_0201107c(void *self, u32 *out);
extern u32 func_020113a4(void *str, int a, int b);
extern int func_02056f94(void *x);
extern void func_0205eae0(void *a, int b, int c, int d);
extern void func_020109a0(void *a, int b, int c, unsigned short d);
extern void *data_020ccf94;
extern int func_02073908(void *a, u32 b);
extern void *func_020984e8(void);
extern int func_02099020(void *a, int b);
extern void func_02098ff8(void *a, int b);

typedef struct {
    u32 kind;
    u8 flag;
} S7D4;

void func_ov003_0220eaa0(u8 *self)
{
    S7D4 *p;
    u32 local;
    void *s;

    p = (S7D4 *) (self + 0x7d4);
    if (p->flag) {
        return;
    }

    local = func_020113a4(*(void **) (self + 0x98), 0, 0x7b);
    func_0201107c(self, &local);
    if (*(void **) (self + 0x98) != 0) {
        return;
    }

    if (!func_02056f94(self + 0x2d0)) {
        return;
    }

    switch (p->kind) {
        case 4:
            func_0205eae0(self + 0x5a0, 8, 3, 0);
            func_020109a0(self, 0x8e, 3, 0);
            break;
        case 3:
            func_0205eae0(self + 0x5a0, 0x1e, 3, 0);
            func_020109a0(self, 0x8e, 3, 0);
            break;
        case 10:
            func_020109a0(self, 0x8e, 3, 0);
            break;
        default:
            func_020109a0(self, 0x8c, 3, 0);
            break;
    }

    p->flag = 1;
    if (!func_02073908(data_020ccf94, *(u32 *) (self + 0x800))) {
        return;
    }

    s = func_020984e8();
    if (s == 0) {
        return;
    }
    if (!func_02099020(s, 0x17)) {
        return;
    }
    func_02098ff8(s, 0x1a);
}
