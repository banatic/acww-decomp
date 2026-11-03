/* villager_pairs_2: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0207bb30 @ 0x0207bb30, 0x52 bytes, Thumb
 * func_0207bae8 @ 0x0207bae8, 0x48 bytes, Thumb
 * func_0207ba3c @ 0x0207ba3c, 0xac bytes, Thumb
 */

extern int func_0208150c(int);
extern int func_0207cf14(int, int);
extern int func_0207cf74(int);
extern int func_0207bb84(int, int, int);
extern unsigned int data_020ccf94;
extern int func_02073d90(unsigned int);
extern void func_02079bc4(int, int, int, int);
extern int func_02003704(int x);
extern int func_0207cee4(void *a, int i);
extern int func_02079924(void *p, int count, int i);
extern int func_0207cec0(void *a, int i);
extern int func_020644cc(int x);

int func_0207bb30(int a, int b, int c)
{
    int x = func_0207cf14(a, func_0208150c(b));
    int y = func_0207cf14(a, func_0208150c(c));
    if (x != y) {
        if (func_0207cf74(x) != 0) {
            if (func_0207cf74(y) != 0) {
                return func_0207bb84(a, x, y);
            }
        }
    }
    return 4;
}

void func_0207bae8(int p1, int p2, int p3, int p4)
{
    int v1, v2;
    if (func_02073d90(data_020ccf94)) {
        return;
    }
    v1 = func_0207cf14(p1, p2);
    v2 = func_0207cf14(p1, p3);
    func_02079bc4(p1 + 0x3f60, v1, v2, p4);
}

int func_0207ba3c(unsigned char *a, int b, int (**cb)(int, int), int d)
{
    int count;
    int p;
    int i;
    int ret;

    count = func_0207cf14((int) a, func_0208150c(b));
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
