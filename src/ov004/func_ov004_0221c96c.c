/* func_ov004_0221c96c @ 0x0221c96c, 0x98 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0206837c(int h);
extern int func_020ab504(int q);
extern unsigned short func_0206f9d8(int (*predicate)(unsigned short *, int));
extern int func_020644cc(int);
extern void func_0206844c(int h, u8 *p, int k);
extern int func_ov004_0221d468(void *arg0, int arg1);
#define TilePredicate_func_ov004_0221d468 ((int (*)(unsigned short *, int)) func_ov004_0221d468)

void func_ov004_0221c96c(char *s)
{
    u8 buf[4];
    int r = func_020ab504(func_0206837c(*(int *) (*(int *) (s + 0x1a4) + 0x8e0)));
    switch (*(u8 *) (s + 0x1e)) {
        case 4:
        case 5:
            if (r == 0) {
                if (func_0206f9d8(TilePredicate_func_ov004_0221d468) != 0) {
                    buf[0] = (u8) (func_020644cc(2) + 9);
                    func_0206844c(*(int *) (*(int *) (s + 0x1a4) + 0x8e0), &buf[0], 0);
                } else {
                    buf[1] = 6;
                    func_0206844c(*(int *) (*(int *) (s + 0x1a4) + 0x8e0), &buf[1], 0);
                }
            } else {
                buf[2] = (u8) (func_020644cc(2) + 7);
                func_0206844c(*(int *) (*(int *) (s + 0x1a4) + 0x8e0), &buf[2], 0);
            }
            break;
    }
}

#undef TilePredicate_func_ov004_0221d468
