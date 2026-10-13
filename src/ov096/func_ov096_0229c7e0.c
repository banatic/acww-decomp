/* func_ov096_0229c7e0 @ 0x0229c7e0, 0xa8 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_022088ac(int);
extern int func_ov002_0220889c(int);
extern int func_ov002_022088bc(int);
extern void func_ov002_0220a2b4(unsigned char *);

void func_ov096_0229c7e0(volatile unsigned char *self, int param)
{
    if (func_ov002_022088ac(param)) {
        if (self[0xb5] > 0x19) {
            self[0xb5] = self[0xb5] - 1;
        }
    } else {
        if (func_ov002_0220889c(param)) {
            if (self[0xb5] < 0x20) {
                self[0xb5] = self[0xb5] + 1;
            }
        }
    }

    if (func_ov002_022088bc(param)) {
        int d = self[0xb5] - 0x19;
        if (d == 7) {
            self[0xb5] = 0x10;
        } else if (d == 6) {
            self[0xb5] = 0x0f;
        } else if (d == 0) {
            self[0xb5] = 0x25;
        } else {
            self[0xb5] = 0x24;
        }

        func_ov002_0220a2b4((unsigned char *) (self + 0x2500));
    }
}
