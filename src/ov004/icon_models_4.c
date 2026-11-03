/* icon_models_4: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02233f18 @ 0x02233f18, 0x34 bytes, Thumb
 * func_ov004_02233f00 @ 0x02233f00, 0x18 bytes, Thumb
 * func_ov004_02233eb8 @ 0x02233eb8, 0x46 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int m[12];
} Mtx;

extern int func_ov004_02233f4c(char *arg0);
extern int func_0204678c(void);
extern void func_ov004_0223380c(void *);
extern void *data_ov004_02258ae4;
extern char data_ov004_02258af4;
extern void func_ov004_022337ac(void *);
extern void func_02055e90(void *, int);
extern u16 func_02065604(void);
extern void NNS_G3dMdlSetMdlEmi(void *, int, u16);

int func_ov004_02233f18(void *a)
{
    int r = 0;
    if (func_ov004_02233f4c((char *) a) != 0) {
        func_0204678c();
        data_ov004_02258ae4 = a;
        func_ov004_0223380c(&data_ov004_02258af4);
        r = 1;
    }
    return r;
}

int func_ov004_02233f00(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_022337ac(((void * *) &data_ov004_02258af4));
    return 0x1;
}

void func_ov004_02233eb8(void *a, char *b, Mtx m)
{
    volatile u16 t, u;
    if (b != 0) {
        *(Mtx *) (b + 0x64) = m;
        func_02055e90(b, 0);
        t = func_02065604();
        u = t;
        NNS_G3dMdlSetMdlEmi(*(void **) (b + 0x5c), 0, u);
    }
}
