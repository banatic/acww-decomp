/* func_ov004_0223896c @ 0x0223896c, 0x88 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_02238804(void *self, int a, int b);
extern void func_ov004_02239768(void *self);
extern void func_ov004_022395d0(void *self, int a, int b);

void func_ov004_0223896c(void *self)
{
    int v;
    int *p;

    v = *(int *) ((char *) self + 0x15c);
    if ((unsigned int) (v - 0x35) <= 1) {
        func_ov004_02238804(self, 2, 0x20);
    } else if (v == 0x34) {
        func_ov004_02238804(self, ~3, 0x26);
    }
    if (*((unsigned char *) self + 0x1ee) != 2 && *((unsigned char *) self + 0x1ee) != 6) {
        func_ov004_02239768(self);
        v = *(int *) ((char *) self + 0x15c);
        if ((unsigned int) (v - 0x35) <= 1) {
            func_ov004_022395d0(self, 0x924, 0x28a);
        } else if (v == 0x34) {
            func_ov004_022395d0(self, 0x71c, 0x28a);
        }
    }
    p = (int *) ((char *) self + 0x158);
    *p = *p + 1;
}
