/* func_ov094_0229b5e8 @ 0x0229b5e8, 0xa8 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_0229a50c(void);
extern int func_ov094_0229b5c8(void *a, void *b);
extern void func_ov094_0229b550(void *a, void *b, void *c, int d, void *e, void *f);
extern void func_ov094_0229b4f0(void *a, void *b, void *c, int d, void *e);
extern void func_ov094_0229b4c0(void *a, void *b, void *c, int d);

void func_ov094_0229b5e8(void *a, void *b, void *c, void *d)
{
    int x;
    if (((unsigned char *) a)[0x27] == 0) {
        return;
    }
    x = func_ov094_0229a50c();
    if (x == 0x1000) {
        func_ov094_0229b550(a, b, c, func_ov094_0229b5c8(a, d), d, 0);
        func_ov094_0229b4f0(a, b, c, func_ov094_0229b5c8(a, d), 0);
        func_ov094_0229b4c0(a, b, c, 0);
    } else {
        unsigned int local[4];
        local[0] = x;
        local[1] = 0;
        local[2] = 0;
        local[3] = x;
        func_ov094_0229b550(a, b, c, func_ov094_0229b5c8(a, d), d, local);
        func_ov094_0229b4f0(a, b, c, func_ov094_0229b5c8(a, d), local);
    }
}
