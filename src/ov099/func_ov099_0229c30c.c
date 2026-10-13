/* func_ov099_0229c30c @ 0x0229c30c, 0xd4 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov099_0229c2ac(unsigned char *obj, int param);
extern void func_ov099_0229c29c(unsigned char *obj, int param);
extern int func_ov002_022088ac(void *arg);
extern int func_ov002_022088cc(void *arg);
extern int func_ov002_0220889c(void *arg);
extern int func_ov002_022088bc(void *arg);

void func_ov099_0229c30c(unsigned char *obj, void *arg)
{
    int b;
    int q;

    b = obj[0x2907];
    q = 0;
    while (b >= 5) {
        b -= 5;
        q++;
    }

    if (func_ov002_022088ac(arg)) {
        if (func_ov002_022088cc(arg) && q != 0) {
            goto exit;
        }
        if (b == 0) {
            obj[0x2907] += 4;
            func_ov099_0229c29c(obj, 0x10);
        } else {
            obj[0x2907] -= 1;
        }
    } else {
        if (func_ov002_0220889c(arg)) {
            if (func_ov002_022088bc(arg) == 0) {
                if (b == 4) {
                    obj[0x2907] -= 4;
                    func_ov099_0229c29c(obj, 0x20);
                } else {
                    obj[0x2907] += 1;
                }
            }
        }
    }

exit:
    if (func_ov099_0229c2ac(obj, 0x30) == 0) {
        if (func_ov002_022088cc(arg) != 0) {
            if (q > 0) {
                obj[0x2907] -= 5;
            }
        } else {
            if (func_ov002_022088bc(arg) != 0 && q < 2) {
                obj[0x2907] += 5;
            }
        }
    }
}
