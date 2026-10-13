/* func_ov004_0221fa58 @ 0x0221fa58, 0x44 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int *func_02095794(int k);
extern int func_02014868(void *p);
extern int func_020b5e10(void);
extern void func_020b6098(int x, int k);
extern void func_ov004_0221fdf4(void *self, int k);

int func_ov004_0221fa58(void *self)
{
    volatile int t[3];
    int *p = func_02095794(4);
    t[0] = p[0];
    t[1] = p[1];
    t[2] = p[2];
    if (func_02014868((char *) self + 0x618) == 0) {
        func_020b6098(func_020b5e10(), 0);
        func_ov004_0221fdf4(self, 2);
    }
    return 1;
}
