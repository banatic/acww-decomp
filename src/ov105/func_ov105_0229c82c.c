/* func_ov105_0229c82c @ 0x0229c82c, 0x5c bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_022088ac(int);
extern int func_ov002_0220889c(int);
extern int func_ov002_022088bc(int);

void func_ov105_0229c82c(unsigned char *p, int id)
{
    if (func_ov002_022088ac(id)) {
        if (p[0x2ba] > 0x3e) {
            p[0x2ba]--;
        }
    } else if (func_ov002_0220889c(id)) {
        if (p[0x2ba] < 0x3f) {
            p[0x2ba]++;
        }
    }
    if (func_ov002_022088bc(id)) {
        p[0x2ba] -= 0x1a;
    }
}
