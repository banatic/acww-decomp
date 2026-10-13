/* func_ov141_0229a2c4 @ 0x0229a2c4, 0x94 bytes, Thumb, module ov141
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_022088cc(int);
extern int sub_22088bc(int);
extern int func_ov002_022088bc(int);
extern int func_ov002_022088ac(int);
extern int func_ov002_0220889c(int);

int func_ov141_0229a2c4(unsigned char *p, int arg)
{
    unsigned char orig;
    orig = p[0x1a8c];
    if (orig <= 5) {
        if (func_ov002_022088cc(arg)) {
            if (p[0x1a8c] != 0) {
                p[0x1a8c]--;
            }
        } else {
            if (func_ov002_022088bc(arg)) {
                if (p[0x1a8c] < 5) {
                    p[0x1a8c]++;
                } else {
                    p[0x1a8c] = 6;
                }
            }
        }
    } else {
        if (func_ov002_022088cc(arg)) {
            p[0x1a8c] = 5;
        } else if (func_ov002_022088ac(arg)) {
            p[0x1a8c] = 6;
        } else if (func_ov002_0220889c(arg)) {
            p[0x1a8c] = 7;
        }
    }
    if (orig != p[0x1a8c]) {
        return 1;
    } else {
        return 0;
    }
}
