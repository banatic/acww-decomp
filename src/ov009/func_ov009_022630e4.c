/* func_ov009_022630e4 @ 0x022630e4, 0x58 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov009_02264e30(void *p);
extern int func_ov009_02264d60(void *p);
extern int func_ov009_02264dc8(void *p);
extern int data_021c67d0[];

extern int data_021c67a4;

int func_ov009_022630e4(void *self)
{
    int dx, dy, *g2;
    if (data_021c67a4 == 0) {
        goto r1b;
    }
    g2 = data_021c67d0;
    dx = *(int *) ((char *) self + 0x5c) - g2[0];
    if (dx < 0) {
        dx = -dx;
    }
    dy = *(int *) ((char *) self + 0x64) - g2[2];
    if (dx > func_ov009_02264e30(self)) {
        goto r1;
    }
    if (dy > func_ov009_02264d60(self)) {
        goto r1;
    }
    if (dy >= -func_ov009_02264dc8(self)) {
        goto r0;
    }
r1:
    return 1;
r0:
    return 0;
r1b:
    return 1;
}
