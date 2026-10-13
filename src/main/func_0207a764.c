/* func_0207a764 @ 0x0207a764, 0x94 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020951bc(int x);
extern int func_0208150c(char *p);
extern int func_02003704(int x);
extern int func_0207f150(char *p);
extern int func_020807a8(char *p, int x);
extern int func_02081d20(int x);
extern int func_0207cc54(int a, int b, int c);

int func_0207a764(char *p, int v)
{
    int best;
    int count;
    int i;
    unsigned char flags;
    int t;
    int r;

    if (func_020951bc(v) == 0) {
        goto fail;
    }

    best = -128;
    flags = 0;
    count = 0;

    for (i = 0; i < 8; i++) {
        if (func_02003704(func_0208150c(p)) && func_0207f150(p) == 3) {
            t = func_020807a8(p, v);
            if (t != 0) {
                r = func_02081d20(t);
                if (r == best) {
                    flags |= (1 << i);
                    count++;
                } else if (r > best) {
                    best = r;
                    flags = (1 << i);
                    count = 1;
                }
            }
        }
        p += 0x7ec;
    }

    return func_0207cc54(flags, count, 8);

fail:
    return -1;
}
