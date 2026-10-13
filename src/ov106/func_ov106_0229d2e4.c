/* func_ov106_0229d2e4 @ 0x0229d2e4, 0x5c bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov106_0229d340(void *self, int a1);
extern int func_ov094_0229bba4(void *self);
extern int func_ov094_0229bb5c(void *self, int a1, int a2);
extern int func_ov094_0229b30c(void *self, int a1);

int func_ov106_0229d2e4(void *self, int a1, int a2, int a3)
{
    int r4;
    int r0;
    int r1;
    int r2;
    int r3;
    int r5 = (int) self;
    int r7 = a1;
    int r6 = a3;
    int sp0 = a2;

    r0 = func_ov094_0229bba4((void *) (r5 + 0xb58));
    r4 = r0;
    if (r4 == 0x37) {
        r0 = func_ov094_0229bb5c((void *) (r5 + 0xb58), r7, sp0);
        r4 = r0;
    }
    if (r4 != 0x37) {
        if (r6 != 0) {
            r0 = func_ov094_0229b30c((void *) (r5 + 0xb58), r4);
            if (r0 != 0) {
                return 0x20;
            }
        }
        r0 = func_ov106_0229d340((void *) r5, r4);
        return r0;
    }
    return 0x20;
}
