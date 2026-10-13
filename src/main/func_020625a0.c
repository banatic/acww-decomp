/* func_020625a0 @ 0x020625a0, 0xcc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0206e6ec(void *tbl);
extern unsigned char *func_0206e7bc(void *h, unsigned int idx);

extern int data_021cb5e0;

int func_020625a0(unsigned short *p)
{
    unsigned short v;
    int cond;
    int d;
    volatile unsigned short t;
    unsigned int idx;
    unsigned char *e;

    cond = 0;
    v = *p;
    if (v >= 0x1000 && v <= 0x10ff) {
        cond = 1;
    }

    if (cond != 0) {
        if (v >= 0x1000 && v <= 0x10ff) {
            d = v - 0x1000;
        } else {
            d = -1;
        }
        d |= 3;
        t = ((unsigned int) d < 0x100) ? (unsigned short) (d + 0x1000) : 0x1000;
        idx = t & 0xfff;
        if (idx >= 0x56e) {
            idx = 0x56d;
        }
        e = func_0206e7bc(func_0206e6ec(&data_021cb5e0), idx);
        if (e != 0) {
            if (((e[9] >> 1) & 1) != 0) {
                return 1;
            }
            return 0;
        }
        return 0;
    } else {
        idx = v & 0xfff;
        if (idx >= 0x56e) {
            idx = 0x56d;
        }
        e = func_0206e7bc(func_0206e6ec(&data_021cb5e0), idx);
        if (e != 0) {
            if (((e[9] >> 1) & 1) != 0) {
                return 1;
            }
            return 0;
        }
        return 0;
    }
}
