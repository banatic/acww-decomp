/* func_ov004_0223a704 @ 0x0223a704, 0x2a bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov004_0223cd50(void *self);
extern void *func_ov004_0223cbe8(void *x, void *self, int k);
extern int func_ov004_0220e5b0(void *p);
extern void func_ov004_0221078c(void *p);

void func_ov004_0223a704(void *self)
{
    void *p = func_ov004_0223cbe8(func_ov004_0223cd50(self), self, 0);
    if (p != 0 && func_ov004_0220e5b0(p) != 0) {
        func_ov004_0221078c(p);
    }
}
