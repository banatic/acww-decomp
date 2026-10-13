/* func_0207ba3c @ 0x0207ba3c, 0xac bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(int b);
extern int func_0207cf14(void *a, int x);
extern int func_02003704(int x);
extern int func_0207cf74(int x);
extern int func_0207cee4(void *a, int i);
extern int func_02079924(void *p, int count, int i);
extern int func_0207cec0(void *a, int i);
extern int func_020644cc(int x);

int func_0207ba3c(unsigned char *a, int b, int (**cb)(int, int), int d)
{
    int count;
    int p;
    int i;
    int ret;

    count = func_0207cf14(a, func_0208150c(b));
    ret = 0;
    if (func_02003704(func_0208150c(b)) == 0) {
        goto end;
    }
    if (func_0207cf74(count) == 0) {
        goto end;
    }
    for (i = ret; i < 8; i++) {
        if (i == count) {
            continue;
        }
        if (func_0207cee4(a, i) == 0) {
            continue;
        }
        p = func_02079924(a + 0x3f60, count, i);
        if ((*cb)(d, p) != 0) {
            ret = func_0207cec0(a, i);
            d = p;
        } else {
            if (d != p) {
                continue;
            }
            if (ret == 0 || (func_020644cc(4) & 1) == 1) {
                ret = func_0207cec0(a, i);
            }
        }
    }
end:
    return ret;
}
