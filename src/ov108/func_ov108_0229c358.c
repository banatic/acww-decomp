/* func_ov108_0229c358 @ 0x0229c358, 0xac bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_022088ac(void *arg);
extern int func_ov002_0220889c(void *arg);
extern int func_ov002_022088cc(void *arg);
extern int func_ov002_022088bc(void *arg);
extern int func_ov108_0229cd70(void *self, int val);
extern int func_ov108_0229c2dc(void *self, int val);

void func_ov108_0229c358(unsigned char *self, void *arg, int flag)
{
    int r4;
    int r6;

    r4 = self[0x2b0] - 11;
    r6 = r4 >> 1;

    if (func_ov002_022088ac(arg) != 0) {
        if ((r4 & 1) > 0) {
            self[0x2b0]--;
        }
    } else {
        if (func_ov002_0220889c(arg) != 0) {
            if ((r4 & 1) < 1) {
                self[0x2b0]++;
            }
        }
    }

    if (func_ov108_0229cd70(self, self[0x2b0]) != 0) {
        if (func_ov108_0229c2dc(self, 0x30) == 0) {
            if (func_ov002_022088cc(arg) != 0) {
                if (r6 > 0) {
                    self[0x2b0] -= 2;
                }
            } else {
                if (func_ov002_022088bc(arg) != 0) {
                    if (r6 < 4) {
                        self[0x2b0] += 2;
                    } else {
                        self[0x2b0] = 0x15;
                    }
                }
            }
        }
    }
}
