/* func_ov003_02235518 @ 0x02235518, 0xbc bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02049d78(void *o);
extern int func_02049ec4(void *o);

int func_ov003_02235518(int a, void *o)
{
    int c;
    int b;

    c = func_02049d78(o);
    b = func_02049ec4(o);
    if (a == 0xf) {
        if (b == 0 || b == 3) {
            if (c == 2) {
                return 1;
            }
        } else if (b != 5) {
            if (b == 4 || c == 1) {
                return 1;
            }
        }
    } else if (a == 3) {
        if (b == 0) {
            if (c == 5 || c == 6) {
                return 1;
            }
        } else if (b == 1) {
            if (c == 4 || c == 6) {
                return 1;
            }
        } else if (b == 2) {
            if (c == 6) {
                return 1;
            }
        } else if (b == 3) {
            if (c == 6 || c == 7 || c == 8) {
                return 1;
            }
        }
    } else if (a == 2) {
        if (b == 0) {
            if (c == 1 || c == 4) {
                return 1;
            }
        } else if (b == 1) {
            if (c == 3) {
                return 1;
            }
        } else if (b == 2) {
            if (c == 2 || c == 4) {
                return 1;
            }
        } else if (b == 3) {
            if (c == 1 || c == 4) {
                return 1;
            }
        }
    }
    return 0;
}
