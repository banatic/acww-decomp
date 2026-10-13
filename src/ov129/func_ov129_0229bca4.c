/* func_ov129_0229bca4 @ 0x0229bca4, 0x4c bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov127_022996d8(void *obj);
extern int func_ov127_022996c8(void *obj);
extern int func_ov127_022996e4(unsigned short *buf, void *src, int param);

int func_ov129_0229bca4(unsigned char *base, void *obj)
{
    unsigned short arr[8];
    void *a;
    int b;
    int n;
    int i;
    unsigned char *p;

    a = func_ov127_022996d8(obj);
    b = func_ov127_022996c8(obj);
    n = func_ov127_022996e4(arr, a, b);

    for (i = 0; i < n; i++) {
        p = base + arr[i];
        if (p[0x2f98] == 2) {
            return 1;
        }
    }
    return 0;
}
