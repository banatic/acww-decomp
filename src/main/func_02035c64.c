/* func_02035c64 @ 0x02035c64, 0x128 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b6660(void);
extern void *func_020351c4(void);

void func_02035c64(char *dst, int x, int y)
{
    int flag = 0;
    int r4 = 0;
    int a, b, c, d, e;
    int v;
    unsigned short hval;
    int f, g, h;
    void *p;

    if (func_020b6660() == 0) {
        goto zero_case;
    }

    a = (x == 0);
    b = (x == 1);
    c = (x == 2);
    d = (y == 9);
    e = (y == 6);

    p = func_020351c4();
    if (p) {
        hval = *(unsigned short *) ((char *) p + 4);
    } else {
        hval = 0xFFFF;
    }
    if (p) {
        v = *(int *) p;
    } else {
        v = 0x25;
    }

    f = (hval == 0xFFFF);
    g = (v == 0x24);
    h = (v == 0x1A);

    if (b) {
        if (e) {
            r4 = 1;
        } else if (d) {
            if (h || f) {
                r4 = 1;
            } else if (g && ((unsigned short) (hval + 0xFFD4) <= 1)) {
                r4 = 1;
            }
        } else {
            if (h || f) {
                r4 = 1;
            }
        }
    } else if (c) {
        if (e) {
            r4 = 1;
            flag = 1;
        } else if (d) {
            // empty
        } else {
            if (h || f) {
                r4 = 1;
            }
        }
    } else {
        if (a) {
            if (h || f) {
                r4 = 1;
            }
        }
    }
    goto done;

zero_case:
    r4 = 1;
    flag = 1;

done:
    if (r4 == 0) {
        dst[8] = 1;
    }
    if (flag != 0) {
        dst[0xb] = 1;
    }
}
