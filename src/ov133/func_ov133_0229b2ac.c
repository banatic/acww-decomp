/* func_ov133_0229b2ac @ 0x0229b2ac, 0x36 bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov133_0229b714(void);
extern void *func_02077c3c(void *p);
extern int func_02077d84(void *p, char *q);
extern void func_ov133_0229b320(char *self, int v);
extern void func_ov133_0229ad78(char *self, int v);
extern void func_ov133_0229b280(char *self);

void func_ov133_0229b2ac(char *self)
{
    if (func_02077d84(func_02077c3c(func_ov133_0229b714()), self + 0xa4)) {
        func_ov133_0229b320(self, 0);
        func_ov133_0229ad78(self, 8);
    } else {
        func_ov133_0229b280(self);
    }
}
