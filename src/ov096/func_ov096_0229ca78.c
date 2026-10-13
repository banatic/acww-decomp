/* func_ov096_0229ca78 @ 0x0229ca78, 0x144 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_022088ac(void *p);
extern int func_ov002_022088cc(void *p);
extern int func_ov002_0220889c(void *p);
extern int func_ov002_022088bc(void *p);
extern int func_ov096_0229c310(void *self);
extern void func_ov096_0229c2ec(void *self, int value);
extern int func_ov096_0229c2fc(void *self, int value);
extern int func_ov096_0229f830(void *self, unsigned char value);
extern int func_ov096_0229ee10(void *self, unsigned int value);
extern int func_ov096_0229ee38(void *self, unsigned int value);
extern int func_ov096_0229ee50(void *self, unsigned int value);

void func_ov096_0229ca78(unsigned char *self, void *other, unsigned int arg2)
{
    int v = self[0xb5];
    int n = 0;

    while (v >= 5) {
        v -= 5;
        n++;
    }

    if (func_ov002_022088ac(other) != 0) {
        if (func_ov002_022088cc(other) != 0 && n != 0) {
            goto tail;
        }
        if (v == 0) {
            if (n == 2) {
                if (func_ov096_0229c310(self) != 0) {
                    self[0xb5] = 0x21;
                    return;
                }
            }
            self[0xb5] = (n + 2) * 2 + 0x10;
            func_ov096_0229c2ec(self, 0x10);
        } else {
            self[0xb5] = self[0xb5] - 1;
            v--;
        }
    } else {
        if (func_ov002_0220889c(other) == 0) {
            goto tail;
        }
        if (func_ov002_022088bc(other) != 0) {
            goto tail;
        }
        if (v == 4) {
            self[0xb5] = (n + 2) * 2 + 0xf;
        } else {
            self[0xb5] = self[0xb5] + 1;
            v++;
        }
    }

tail:
    if (func_ov096_0229f830(self, self[0xb5]) == 0) {
        return;
    }
    if (func_ov096_0229c2fc(self, 0x30) != 0) {
        return;
    }

    if (func_ov002_022088cc(other) != 0) {
        if (n > 0) {
            self[0xb5] -= 5;
            return;
        }
        if (v <= 2) {
            if (func_ov096_0229ee10(self, arg2) != 0) {
                self[0xb5] = 0x25;
                return;
            }
        }
        if (func_ov096_0229ee38(self, arg2) != 0) {
            self[0xb5] = 0x22;
            return;
        }
        if (func_ov096_0229ee50(self, arg2) != 0) {
            self[0xb5] = 0x24;
        }
    } else {
        if (func_ov002_022088bc(other) != 0 && n < 2) {
            self[0xb5] += 5;
        }
    }
    return;
}
