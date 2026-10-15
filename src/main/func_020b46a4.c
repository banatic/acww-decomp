/* func_020b46a4 @ 0x020b46a4, 0xb4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct Big {
    unsigned int w[0x18];
} Big;

extern const u8 data_020d20ac[];
extern const u8 data_020d2094[];
extern const u8 data_020d20a0[];
extern int data_020e5300;

extern void *func_020a8228(Big *s);
extern void *func_020a8210(Big *s);
extern int func_020b4a20(Big *s, u8 *v, void *p);
extern int func_020a89dc(void *ctx, Big *s);

int func_020b46a4(void *ctx, int n, int kind)
{
    u8 v;
    Big s;
    int r;
    int m;

    func_020a8228(&s);
    r = 0;
    m = n % 10;
    if (kind == 1) {
        r = 0;
    } else if (kind == 2) {
        r = 1;
    } else if (kind == 3) {
        r = data_020d20ac[m];
    } else if (kind == 4) {
        r = 5;
    } else if (kind == 5) {
        r = 6;
    } else if (kind == 6) {
        r = data_020d2094[m];
    } else if (kind == 7) {
        r = 10;
    } else if (kind == 8) {
        r = 11;
    } else if (kind == 9) {
        r = data_020d20a0[m];
    } else if (kind == 10) {
        r = 14;
    }
    v = r;
    r = func_020b4a20(&s, &v, &data_020e5300);
    if (r != 0) {
        r = (r & func_020a89dc(ctx, &s)) != 0;
    }
    func_020a8210(&s);
    return r;
}
