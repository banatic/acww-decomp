/* func_ov004_0222c348 @ 0x0222c348, 0x4c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02064b2c(void *a, int b, int c, int d);
extern int func_021077e8(void *h);
extern int func_02056064(int t, int k);
extern int func_020561cc(int t, int p);
extern void func_020e9898(void *h);
extern int data_021fbe94;
extern int data_021c9b24;
int func_ov004_0222c348(int *out, void *a)
{
    void *h;
    int t;
    h = func_02064b2c(a, data_021fbe94, -4, 0);
    if (h != 0) {
        t = func_021077e8(h);
        func_02056064(t, 0);
        *out = func_020561cc(t, data_021c9b24);
        func_020e9898(h);
        return 1;
    }
    return 0;
}
