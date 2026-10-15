/* func_020b2f38 @ 0x020b2f38, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short *func_020b3038(int *a, int *b);
extern int func_0204bcdc(void *);
extern int func_0204bc64(const unsigned short *ptr);
extern int func_0204e414(void);
extern int func_0204e3f4(int a, int b, int c, int d);

int func_020b2f38(int input)
{
    unsigned short arr[2];
    int out1, out2;
    int cond, res, r;
    int ret = 0;
    unsigned short *p;

    arr[0] = (unsigned short) input;
    cond = 0;
    if (arr[0] >= 0x5000u && arr[0] <= 0x5021u) {
        cond = 1;
    }
    if (cond == 0) {
        goto fail;
    }

    p = func_020b3038(&out1, &out2);
    if (p == 0) {
        goto fail;
    }

    if (func_0204bcdc(p) != 0) {
        arr[1] = (unsigned short) input;
        if (func_0204bc64(p) == func_0204bc64(&arr[1])) {
            res = 1;
        } else {
            res = 0;
        }
    } else {
        if (*p == input) {
            res = 1;
        } else {
            res = 0;
        }
    }
    if (res == 0) {
        goto fail;
    }

    r = func_0204e414();
    if (r == 0) {
        goto fail;
    }

    ret = func_0204e3f4(r, out1, out2, 0);
    goto end;

fail:
    ret = 0;
end:
    return ret;
}
