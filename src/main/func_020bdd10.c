/* func_020bdd10 @ 0x020bdd10, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020d266c[];
extern int func_020bdd9c(void);
extern int func_020644cc(int param);

int func_020bdd10(int arg0, int index, int flags)
{
    int ret = data_020d266c[index];
    if (index == 4) {
        ret = func_020bdd9c();
    } else if (index == 7) {
        if (func_020644cc(2) != 0) {
            ret = 40;
        }
    } else if (index == 5) {
        if (flags & 1) {
            ret = 33;
        }
    } else if (index == 9) {
        unsigned t = (flags & 0xF) + 0x1D;
        if ((t - 0x1D) <= 1) {
            ret = 45;
        } else if (t == 0x21 || t == 0x24 || t == 0x27 || t == 0x2A) {
            ret = 43;
        } else {
            ret = 44;
        }
    } else if (index == 2) {
        unsigned mask = flags & 0xF;
        if (mask == 0) {
            ret = 47;
        } else if (mask == 1) {
            ret = 49;
        } else {
            ret = 48;
        }
    }
    return ret;
}
