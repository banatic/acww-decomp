/* func_ov109_0229c9f0 @ 0x0229c9f0, 0x40 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov109_0229ccb4(void *a, void *b);
extern int func_ov109_0229cc98(void *a, void *b);
extern void func_ov094_0229ab1c(void *p, int x);
extern int func_ov094_0229b98c(void *p);
extern int func_ov109_0229ca30(void *p);

int func_ov109_0229c9f0(void *a, void *b)
{
    if (func_ov109_0229ccb4(a, b)) {
        func_ov094_0229ab1c((char *) a + 0xcc, func_ov109_0229cc98(a, b));
        return func_ov094_0229b98c((char *) a + 0xb2c);
    } else {
        return func_ov109_0229ca30(a);
    }
}
