/* fish_shadow_state_3: 4 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02228a20 @ 0x02228a20, 0x78 bytes, Thumb
 * func_ov003_02228a1c @ 0x02228a1c, 0x2 bytes, Thumb
 * func_ov003_022289b4 @ 0x022289b4, 0x68 bytes, Thumb
 * func_ov003_022289b0 @ 0x022289b0, 0x2 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

extern int func_ov003_02227e94(char *self, char *b, int k);
extern void func_ov003_02228a9c(char *self, int k, char *b, void *c);
extern void *data_021c67a4;
extern Vec3 data_021c67d0;
extern int func_ov003_0222799c(void *p, Vec3 *v, int a, int b, int c);
extern int func_ov003_02228dfc(void *a0, void *c);
extern int func_ov003_02228d1c(void *a0);

void func_ov003_02228a20(char *self, char *b, void *c)
{
    if (*(u8 *) (self + 0x84) == 0) {
        u8 st = *(u8 *) (b + 0x1fc);
        if (st == 3) {
            if (*(u8 *) (b + 0x23c) == 0) {
                if (func_ov003_02227e94(self, b, 0)) {
                    func_ov003_02228a9c(self, 1, b, c);
                }
                *(u8 *) (self + 0x84) = 1;
            }
        } else if (st == 4) {
            if (*(u8 *) (b + 0x23c) == 0) {
                if (func_ov003_02227e94(self, b, 1)) {
                    func_ov003_02228a9c(self, 1, b, c);
                }
                *(u8 *) (self + 0x84) = 1;
            }
        }
    }
}

void func_ov003_02228a1c(void) {}

void func_ov003_022289b4(void *a0, char *b, void *c)
{
    Vec3 v;
    if (data_021c67a4 != 0) {
        v.x = data_021c67d0.x;
        v.y = data_021c67d0.y;
        v.z = data_021c67d0.z;
        if (func_ov003_0222799c(b + 0x12c, &v, 0xa000, 0x10000, 0xa000)) {
            func_ov003_02228dfc(a0, c);
            if (*(u8 *) (b + 0x7f)) {
                func_ov003_02228d1c(a0);
            }
        }
    }
}

void func_ov003_022289b0(void) {}
