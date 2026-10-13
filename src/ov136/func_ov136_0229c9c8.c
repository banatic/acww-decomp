/* func_ov136_0229c9c8 @ 0x0229c9c8, 0x40 bytes, Thumb, module ov136
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov134_0229a24c(void *);
extern int func_ov134_0229a8a0(void *);
extern void func_ov136_0229c974(void *);

void func_ov136_0229c9c8(void *self)
{
    if (func_ov134_0229a24c((char *) self + 0x2c4)) {
        int v = func_ov134_0229a8a0((char *) self + 0x2c4);
        if (v == 6) {
            ((char *) self)[0x2b77] = 2;
        } else {
            ((char *) self)[0x2b77] = v - 3;
        }
        func_ov136_0229c974(self);
    }
}
