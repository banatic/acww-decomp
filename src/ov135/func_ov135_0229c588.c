/* func_ov135_0229c588 @ 0x0229c588, 0xa8 bytes, Thumb, module ov135
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_022088ac(void *p);
extern int func_ov002_0220889c(void *p);
extern int func_ov002_022088cc(void *p);
extern int func_ov002_022088bc(void *p);

extern const unsigned char data_ov135_0229d4fc[];
extern const unsigned char data_ov135_0229d504[];
extern const unsigned char data_ov135_0229d514[];
extern const unsigned char data_ov135_0229d50c[];

int func_ov135_0229c588(void *self, void *arg)
{
    unsigned char old;
    unsigned char *p;

    p = (unsigned char *) self + 0x95;
    old = *p;

    if (func_ov002_022088ac(arg) != 0) {
        p = (unsigned char *) self + 0x95;
        *p = data_ov135_0229d4fc[*p];
    } else if (func_ov002_0220889c(arg) != 0) {
        p = (unsigned char *) self + 0x95;
        *p = data_ov135_0229d504[*p];
    }

    p = (unsigned char *) self + 0x95;
    if (old != *p) {
        return 1;
    }

    if (func_ov002_022088cc(arg) != 0) {
        p = (unsigned char *) self + 0x95;
        *p = data_ov135_0229d514[*p];
    } else if (func_ov002_022088bc(arg) != 0) {
        p = (unsigned char *) self + 0x95;
        *p = data_ov135_0229d50c[*p];
    }

    p = (unsigned char *) self + 0x95;
    if (old != *p) {
        return 1;
    }

    return 0;
}
