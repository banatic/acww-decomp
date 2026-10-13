/* func_ov004_022249f8 @ 0x022249f8, 0xc4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_022249f8;
typedef int (UnkStruct_022249f8::*PMF)(void);
struct UnkStruct_022249f8_2 {
    int a;
    int b;
    PMF fn;
};
extern UnkStruct_022249f8_2 data_ov004_022580e0[];

extern "C" {

extern int func_020355e0(void);
extern int func_020e8b0c(int a, int b, int c);
extern void func_02056e60(char *p, int n);
extern char *func_0200420c(void);
extern void func_020542e0(char *p);

int func_ov004_022249f8(UnkStruct_022249f8 *self)
{
    // DECLS
    char *b;
    int r;
    char *p;
    // ENDDECLS

    b = (char *) self;
    r = 0;
    if (data_ov004_022580e0[*(int *) (b + 0x654)].fn != 0) {
        r = (self->*data_ov004_022580e0[*(int *) (b + 0x654)].fn)();
    }
    if (func_020e8b0c(func_020355e0(), 0x63, 0xab) != 0) {
        if (*(unsigned char *) (b + 0x77e) == 0) {
            if ((u16) (*(int *) (b + 0x190) >> 12) != 0) {
                func_02056e60(b + 0x1a4, 0xa);
            }
            b[0x77e] = 1;
        }
        p = func_0200420c();
        if (p != 0 && ((signed char *) p)[3] != 1) {
            *(int *) (b + 0x190) = 0;
            *(int *) (b + 0x198) = *(int *) (p + 0x10);
            func_020542e0(b + 0xec);
            *(int *) (b + 0x198) = 0;
        }
    } else {
        b[0x77e] = 0;
    }
    return r;
}
}
