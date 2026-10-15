/* func_0202f520 @ 0x0202f520, 0x7a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202f660(void *a, void *b);
extern int FX_MulFunc(int a, int b);
extern void *func_0202f740(void *buf, void *a2, void *a3);
extern void func_0202f6e8(void *buf);
extern int func_0202f59c(void *a0, void *a1, void *a2, void *a3);

int func_0202f520(void *a0, void *a1, void *a2, void *a3)
{
    unsigned char buf[32];
    int tmp1, tmp2, tmp3, tmp4, ret;

    tmp1 = func_0202f660(a0, a2);
    tmp2 = func_0202f660(a0, a3);

    if (FX_MulFunc(tmp1, tmp2) < 0) {
        func_0202f740(buf, a2, a3);
        tmp3 = func_0202f660(buf, (char *) a0 + 4);
        tmp4 = func_0202f660(buf, (char *) a0 + 12);

        if (FX_MulFunc(tmp3, tmp4) < 0) {
            ret = func_0202f59c(a0, a1, a2, a3);
            func_0202f6e8(buf);
            return ret;
        }
        func_0202f6e8(buf);
    }
    return 0;
}
