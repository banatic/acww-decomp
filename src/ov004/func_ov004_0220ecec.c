/* func_ov004_0220ecec @ 0x0220ecec, 0x54 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0220e5c0(void *arg0);
extern int func_ov004_0220ee74(void);
extern int func_ov004_0220d2b8(void *p);
extern int func_ov004_0223c264(void *fn);
extern int func_ov004_0221134c(void *arg0);
extern void func_02064da0(int a, int b);
extern int func_ov004_0220cdf8(void *self);
extern int func_020b65c4(void);
extern void func_02052038(int a, int b);

void func_ov004_0220ecec(char *self)
{
    if (func_ov004_0220e5c0((void *) self) && func_ov004_0220ee74() && func_ov004_0220d2b8(self + 0x740) &&
        func_ov004_0223c264((void *) func_ov004_0221134c) == 1) {
        func_02064da0(0, 1);
        if (func_ov004_0220cdf8(self)) {
            func_02052038(func_020b65c4(), 0);
        }
    }
}
