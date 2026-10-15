/* func_ov106_0229d810 @ 0x0229d810, 0x4e bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov106_0229d454(void *);
extern void func_ov106_0229d73c(void *);
extern int func_ov106_0229d48c(void *);
extern void func_ov106_0229d414(void *, int);
extern void func_ov106_0229d4ac(void *, int, int);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov106_0229d810(void *self)
{
    int v;
    int w;

    v = func_ov106_0229d454(self);
    if (v == 0x20) {
        *((unsigned char *) self + 0xb8) = 0x1f;
        func_ov106_0229d73c(self);
    } else {
        w = func_ov106_0229d48c(self);
        if (w == 0x20) {
            func_ov106_0229d414(self, 6);
        } else {
            func_ov106_0229d4ac(self, v, w);
            func_ov002_02208098((void *) (self), 0x25);
        }
    }
}
