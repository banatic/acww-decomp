/* func_ov003_02219a64 @ 0x02219a64, 0x6c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02096718(int);
extern int func_0200fc90(void *);
extern unsigned int *func_0200f27c(void *, int);
extern int func_ov003_02217c5c(void *, int, unsigned int, int, int, int, int, int);
extern int func_ov003_022186cc(void *, unsigned int, int, int, int, int, int);

int func_ov003_02219a64(unsigned int a, int *b, int *c, int d)
{
    void *p = func_02096718(4);
    if (p != 0) {
        if (func_0200fc90(p)) {
            return func_ov003_02217c5c(p, 0x39, (a << 26) >> 24, *b, *c, d, 6, -1);
        } else {
            func_0200f27c(p, 1);
            return func_ov003_022186cc(p, a, *b, *c, d, 6, -1);
        }
    }
    return 0;
}
