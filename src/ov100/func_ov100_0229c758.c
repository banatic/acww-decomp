/* func_ov100_0229c758 @ 0x0229c758, 0xf4 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_022088ac(void *obj);
extern int func_ov002_022088cc(void *obj);
extern int func_ov002_0220889c(void *obj);
extern int func_ov002_022088bc(void *obj);
extern void func_ov100_0229c2b0(void *s, int v);

void func_ov100_0229c758(unsigned char *s, void *obj, int mode)
{
    int r4;
    int r6;

    r4 = s[0x2921] - 15;
    r6 = 0;
    while (r4 >= 5) {
        r4 -= 5;
        r6++;
    }

    if (func_ov002_022088ac(obj)) {
        if (func_ov002_022088cc(obj) == 0 || r6 == 0) {
            if (r4 == 0) {
                if (mode == 1) {
                    s[0x2921] += 4;
                } else {
                    s[0x2921] = 0x1e;
                }
                func_ov100_0229c2b0(s, 0x10);
                return;
            } else {
                s[0x2921] -= 1;
                r4--;
            }
        }
    } else {
        if (func_ov002_0220889c(obj) != 0 && func_ov002_022088bc(obj) == 0) {
            if (r4 == 4) {
                if (mode == 1) {
                    s[0x2921] -= 4;
                    func_ov100_0229c2b0(s, 0x20);
                    return;
                } else {
                    s[0x2921] = 0x1e;
                    return;
                }
            } else {
                s[0x2921] += 1;
                r4++;
            }
        }
    }

    if (func_ov002_022088cc(obj)) {
        if (r6 > 0) {
            s[0x2921] -= 5;
            return;
        }
    } else {
        if (func_ov002_022088bc(obj)) {
            if (r6 < 2) {
                s[0x2921] += 5;
            } else {
                s[0x2921] = r4;
            }
        }
    }
}
