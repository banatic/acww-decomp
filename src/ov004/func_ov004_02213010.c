/* func_ov004_02213010 @ 0x02213010, 0x64 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_0221078c(void *self);
extern int data_020ccf94;
extern void *func_020984e8(void);
extern void *func_02099734(void *s);
extern int func_02098cf8(void *p, int a);
extern void func_02098aa0(void *p, int a, int b);

int func_ov004_02213010(char *self)
{
    void *s;

    func_ov004_0221078c(self);
    if (*(u8 *) (self + 0x77c) == *(int *) ((char *) *(void **) &data_020ccf94 + 0x68)) {
        s = func_020984e8();
        if (s != 0) {
            if (func_02098cf8(func_02099734(s), 0) > 0) {
                func_02098aa0(func_02099734(s), func_02098cf8(func_02099734(s), 0) - 1, 0);
            }
        }
    }
    return 1;
}
