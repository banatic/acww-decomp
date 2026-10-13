/* func_ov100_0229c84c @ 0x0229c84c, 0xf4 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov100_0229c2b0(void *self, int arg);
extern int func_ov002_0220889c(void *self);
extern int func_ov002_022088bc(void *self);
extern int func_ov002_022088ac(void *self);
extern int func_ov002_022088cc(void *self);

void func_ov100_0229c84c(void *self, void *other, int arg)
{
    unsigned char *p = (unsigned char *) self;
    unsigned char *q = (unsigned char *) other;
    int r4 = p[0x2921];
    int r6 = 0;
    int r7 = (int) q;

    while (r4 >= 5) {
        r4 -= 5;
        r6++;
    }

    if (func_ov002_022088ac(q) != 0) {
        if (func_ov002_022088cc(q) != 0) {
            if (r6 != 0) {
                goto label_8f8;
            }
        }
        if (r4 == 0) {
            if (arg == 1) {
                p[0x2921] = p[0x2921] + 4;
            } else {
                p[0x2921] = 0x1f;
            }
            func_ov100_0229c2b0(self, 0x10);
            return;
        } else {
            p[0x2921] = p[0x2921] - 1;
            r4--;
            goto label_8f8;
        }
    } else {
        if (func_ov002_0220889c(q) != 0) {
            if (func_ov002_022088bc(q) == 0) {
                if (r4 == 4) {
                    if (arg == 1) {
                        p[0x2921] = p[0x2921] - 4;
                        func_ov100_0229c2b0(self, 0x20);
                        return;
                    } else {
                        p[0x2921] = 0x1f;
                        return;
                    }
                } else {
                    p[0x2921] = p[0x2921] + 1;
                    r4++;
                }
            }
        }
    }

label_8f8:
    if (func_ov002_022088cc(q) != 0) {
        if (r6 > 0) {
            p[0x2921] = p[0x2921] - 5;
            return;
        } else {
            p[0x2921] = r4 + 0x19;
            return;
        }
    } else {
        if (func_ov002_022088bc(q) != 0) {
            if (r6 < 2) {
                p[0x2921] = p[0x2921] + 5;
            }
        }
    }
}
