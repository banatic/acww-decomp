/* func_ov096_0229f4f8 @ 0x0229f4f8, 0x40 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_0229bba4(void *, int unused1, int unused2);
extern int func_ov094_0229b30c(void *, int);
extern int func_ov096_0229f538(void *, int);

int func_ov096_0229f4f8(void *p1, int p2, int p3, int p4)
{
    int result = func_ov094_0229bba4((char *) p1 + 0xDB8, p2, p3);
    if (result != 0x37) {
        if (p4 != 0 && func_ov094_0229b30c((char *) p1 + 0xDB8, result) != 0) {
            return 38;
        }
        return func_ov096_0229f538(p1, result);
    } else {
        return 38;
    }
}
