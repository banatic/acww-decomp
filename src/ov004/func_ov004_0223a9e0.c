/* func_ov004_0223a9e0 @ 0x0223a9e0, 0x4e bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0223a968(void *);
extern int func_ov004_0223a87c(void *);
extern int func_ov004_0223a7d8(void *);
extern void func_ov004_0223aa30(void *, int, int);
extern void func_ov004_0223b274(void);
extern int func_ov004_0223a7f0(void *);
void func_ov004_0223a9e0(void *self)
{
    int v = func_ov004_0223a968(self);
    if (v == 0xff) {
        int w = func_ov004_0223a87c(self);
        if (w != func_ov004_0223a7d8(self)) {
            func_ov004_0223aa30(self, v, w);
            func_ov004_0223b274();
        }
    } else if (v != func_ov004_0223a7f0(self)) {
        func_ov004_0223aa30(self, v, 0xff);
        func_ov004_0223b274();
    }
}
