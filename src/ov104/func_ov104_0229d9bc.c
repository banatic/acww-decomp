/* func_ov104_0229d9bc @ 0x0229d9bc, 0x5c bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_0229bba4(void *, int unused1, int unused2);
extern int func_ov094_0229bb84(void *, int, int);
extern int func_ov094_0229b30c(void *, int);
extern int func_ov104_0229da18(void *, int);

int func_ov104_0229d9bc(void *self, int a, int b, int c)
{
    int r4;
    int r6 = c;
    int r7 = a;
    int r5 = (int) self;
    int r0;
    int r2 = b;

    r0 = func_ov094_0229bba4((void *) (r5 + 0xd58), a, b);
    r4 = r0;
    if (r4 == 0x37) {
        r0 = func_ov094_0229bb84((void *) (r5 + 0xd58), r7, r2);
        r4 = r0;
    }
    if (r4 != 0x37) {
        if (r6 != 0) {
            r0 = func_ov094_0229b30c((void *) (r5 + 0xd58), r4);
            if (r0 != 0) {
                return 0x21;
            }
        }
        r0 = func_ov104_0229da18((void *) r5, r4);
    } else {
        return 0x21;
    }
    return r0;
}
