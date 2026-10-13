/* func_ov100_0229da40 @ 0x0229da40, 0x3c bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209d8c(void *p);
extern void func_ov100_0229cd4c(void *p, unsigned char c);
extern void func_ov100_0229d8b0(void *p);
extern void func_ov094_022999d8(void);
extern void func_ov100_0229cdf4(void *p);

void func_ov100_0229da40(void *self)
{
    if (func_ov002_02209d8c((char *) self + 0x225c)) {
        func_ov100_0229cd4c(self, *(unsigned char *) ((char *) self + 0x2920));
        func_ov100_0229d8b0(self);
        func_ov094_022999d8();
    } else {
        func_ov100_0229cdf4(self);
    }
}
