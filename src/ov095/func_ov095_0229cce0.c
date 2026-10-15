/* func_ov095_0229cce0 @ 0x0229cce0, 0x4e bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov095_0229c8f0(void *, int, int);
extern int func_ov095_0229cf64(void *, int);
extern void func_ov095_0229cef4(void *, int);
extern void func_ov095_0229cc9c(void *);
extern void func_ov095_022999a8(void *, int);

void func_ov095_0229cce0(void *p)
{
    int i;
    if (((int *) p)[0x9] != -1) {
        func_ov095_0229c8f0(p, ((int *) p)[0x9], 0xc);
        ((int *) p)[0x9] = -1;
    }
    for (i = 0; i < 0xe; i++) {
        if (func_ov095_0229cf64(p, i)) {
            func_ov095_0229cef4(p, i);
        }
    }
    func_ov095_0229cc9c(p);
    func_ov095_022999a8(p, 1);
}
