/* func_ov110_0229c6ec @ 0x0229c6ec, 0x104 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_022088ac(void *p);
extern int func_ov002_022088cc(void *p);
extern int func_ov002_0220889c(void *p);
extern int func_ov002_022088bc(void *p);
extern void func_ov110_0229c2b8(void *p, int n);

void func_ov110_0229c6ec(unsigned char *a, void *b, int c)
{
    int r4, r6;

    r4 = a[0xf5] - 15;
    r6 = 0;
    while (r4 >= 5) {
        r4 -= 5;
        r6++;
    }

    if (func_ov002_022088ac(b) != 0) {
        if (func_ov002_022088cc(b) != 0) {
            if (r6 != 0) {
                goto L7ac;
            }
        }
        // func2 == 0 or (func2 != 0 && r6 == 0)
        if (r4 == 0) {
            if (c == 1) {
                a[0xf5] = a[0xf5] + 4;
            } else {
                a[0xf5] = 30;
            }
            func_ov110_0229c2b8(a, 16);
            goto end;
        } else {
            a[0xf5] = a[0xf5] - 1;
            r4--;
            goto L7ac;
        }
    } else {
        if (func_ov002_0220889c(b) == 0) {
            goto L7ac;
        }
        if (func_ov002_022088bc(b) != 0) {
            goto L7ac;
        }
        if (r4 == 4) {
            if (c == 1) {
                a[0xf5] = a[0xf5] - 4;
                func_ov110_0229c2b8(a, 32);
                goto end;
            } else {
                a[0xf5] = 30;
                goto end;
            }
        } else {
            a[0xf5] = a[0xf5] + 1;
            r4++;
            goto L7ac;
        }
    }

L7ac:
    if (func_ov002_022088cc(b) != 0) {
        if (r6 > 0) {
            a[0xf5] = a[0xf5] - 5;
        }
    } else {
        if (func_ov002_022088bc(b) != 0) {
            if (r6 < 2) {
                a[0xf5] = a[0xf5] + 5;
            } else {
                a[0xf5] = r4;
            }
        }
    }

end:
    return;
}
