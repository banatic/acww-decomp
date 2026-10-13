/* func_ov106_0229d7ac @ 0x0229d7ac, 0x28 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_0229b19c(void *);
extern void func_ov106_0229d73c(void *);

void func_ov106_0229d7ac(void *self)
{
    if (func_ov094_0229b19c((char *) self + 0xb58)) {
        ((char *) self)[0xb4] = 0;
        func_ov106_0229d73c(self);
    }
}
