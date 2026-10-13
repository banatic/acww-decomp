/* func_ov112_0229f2bc @ 0x0229f2bc, 0x6c bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef void (*Fn)(void *);

extern int func_ov112_0229fe70(char *self, int a);
extern void func_ov002_0220a0b4(void *obj, int a, int b);
extern int func_ov095_02299b7c(char *p);
extern int func_ov095_02299b38(char *p);

void func_ov112_0229f2bc(char *self)
{
    int a;
    int b;
    void *obj;

    if (func_ov112_0229fe70(self, 0x800) != 0) {
        func_ov002_0220a0b4(self + 0x4448, *(int *) (self + 0x98), *(int *) (self + 0x9c) - *(u8 *) (self + 0xb7));
    } else {
        a = func_ov095_02299b7c(self + 0x384);
        b = func_ov095_02299b38(self + 0x384);
        func_ov002_0220a0b4(self + 0x4448, a, b);
    }
    obj = self + 0x4448;
    (*(Fn **) obj)[3](obj);
}
