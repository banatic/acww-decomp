/* field_actor_39: 4 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02216410 @ 0x02216410, 0x4e bytes, Thumb
 * func_ov003_02216404 @ 0x02216404, 0xc bytes, Thumb
 * func_ov003_02216400 @ 0x02216400, 0x4 bytes, Thumb
 * func_ov003_022163f8 @ 0x022163f8, 0x6 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int a;
    int b;
} Pair;

extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, short);
extern void func_ov003_02216460(void *, int, void *);
extern int func_0200e894(int, void *);
extern int func_0200e91c(void *);

int func_ov003_02216410(int a, int b, Pair *c, int d, short e)
{
    Pair pair;
    char obj[12];
    char out[16];
    int result;

    func_0200e92c(&obj);
    func_0200e90c(&obj, 0x4b, d, e);
    pair.a = c->a;
    pair.b = c->b;
    func_ov003_02216460(&out, b, &pair);
    result = func_0200e894(a, &obj);
    func_0200e91c(&obj);
    return result;
}

void func_ov003_02216404(unsigned char *r0, unsigned char r1, unsigned int *r2)
{
    r0[2] = r1;
    r0[0] = (unsigned char) r2[0];
    r0[1] = (unsigned char) r2[1];
}

void func_ov003_02216400(unsigned char *p0, int p1)
{
    p0[0] = p1;
}

void func_ov003_022163f8(u8 *src, u8 *dst)
{
    *dst = *src;
}
