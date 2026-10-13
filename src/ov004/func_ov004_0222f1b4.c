/* func_ov004_0222f1b4 @ 0x0222f1b4, 0x80 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef u16 (*Fn)(int);
extern void *func_ov004_0222f320(void *);
extern void *func_020e9948(void *, int);
extern void *data_021c9b24;
extern int func_02071298(void *, u16 *);
extern void func_02064328(void *, void *, int, int);
extern u8 func_0205790c(int, void *);
extern int data_021f38f8;
extern int data_ov004_02258460;
extern int data_ov004_02255268;

void func_ov004_0222f1b4(char *self)
{
    int flag = 0;
    u16 t;
    unsigned i;
    char *m = (char *) func_ov004_0222f320(*(void **) (self + 8));
    *(void **) (self + 0x290) = func_020e9948(data_021c9b24, *(int *) (m + 4));
    for (i = 0; i < *(unsigned *) (m + 4); i++) {
        int f;
        t = (*(Fn *) m)(i);
        f = flag;
        if (func_02071298(&data_021f38f8, &t) != 0) {
            f = 1;
        }
        func_02064328(&data_ov004_02258460, &data_ov004_02255268, i, f);
        *(*(u8 **) (self + 0x290) + i) = func_0205790c(*(int *) (self + 0x148), &data_ov004_02258460);
    }
}
